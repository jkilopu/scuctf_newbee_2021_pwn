from pwn import *
from unicorn import *
from unicorn.x86_const import *

# code to be emulated
X86_CODE32 = asm('''
    mov ecx, 0x3
    mov eax, 0x4
    test ecx, ecx
    jle end
    mov esi, 0x4
    xor edx, edx
    mov ebx, 0x6
loop:
    imul eax, esi
    add edx, 1
    add eax, ebx
    cmp edx, ecx
    jnz loop
end:
    xor edx, edx
''')

# memory address where emulation starts
ADDRESS = 0x1000000

print("Emulate i386 code")
try:
    # Initialize emulator in X86-32bit mode
    mu = Uc(UC_ARCH_X86, UC_MODE_32)

    # map 2MB memory for this emulation
    mu.mem_map(ADDRESS, 2 * 1024 * 1024)

    # write machine code to be emulated to memory
    mu.mem_write(ADDRESS, X86_CODE32)

    # initialize machine registers
    #mu.reg_write(UC_X86_REG_ECX, 0x1234)
    #mu.reg_write(UC_X86_REG_EDX, 0x7890)

    # emulate code in infinite time & unlimited instructions
    mu.emu_start(ADDRESS, ADDRESS + len(X86_CODE32))

    # now print out some registers
    print("Emulation done. Below is the CPU context")

    r_eax = mu.reg_read(UC_X86_REG_EAX)
    print(">>> EAX = 0x%x" %r_eax)

except UcError as e:
    print("ERROR: %s" % e)
