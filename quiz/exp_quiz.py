from pwn import *

io = process("./quiz")
#io = remote("xxx.xxx.xxx.xx", xxxx)

context.log_level = "debug"

# test 1
io.recvuntil(b"What is ")
v1 = int(io.recv(4), 16)
io.sendline(str(v1).encode())

# test 2
io.recvuntil(b"A signed 32bit interger ")
v2 = int(io.recvuntil(b' ', drop=True))
io.sendline(str(v2 + 2**32).encode())

# test 3
io.recvuntil(b"unsigned int val = ")
v3_1 = int(io.recvuntil(b';', drop=True))
io.recvuntil(b"unsigned int sub = ")
v3_2 = int(io.recvuntil(b';', drop=True))
io.sendline(hex((v3_1 - v3_2) + 2**32).encode())

# test4
io.recvuntil(b"mov ecx, ")
n = int(io.recvuntil(b'\n', drop=True), 16)
io.recvuntil(b"mov eax, ")
initial = int(io.recvuntil(b'\n', drop=True), 16)
io.recvuntil(b"mov esi, ")
mul = int(io.recvuntil(b'\n', drop=True), 16)
io.recvuntil(b"mov ebx, ")
add = int(io.recvuntil(b'\n', drop=True), 16)
for i in range(n):
    initial = mul * initial + add
io.sendline(str(initial).encode())

io.interactive()
