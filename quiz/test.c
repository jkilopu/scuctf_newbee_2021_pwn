#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void test_hex(void)
{
    unsigned int val = rand() % 0xff + 1;
    printf("\n1. What is 0x%x (base 16) in decimal (base 10)?\n", val);
    printf(">> ");

    unsigned int ans = 0;
    if (scanf("%u", &ans) != 1)
    {
        puts("Invalid input!");
        exit(1);
    }
    if (ans != val)
    {
        puts("Wrong answer!");
        puts("See you next time~");
        exit(1);
    }
    puts("Easy, right?");
    puts("Now go to the next test.");
}

void test_int_uint(void)
{
    int val = (rand() % 0x1000000) * (-1);
    printf("\n2. A signed 32bit integer %d is converted to an unsigned 32bit integer.\n"
           "Assume integer is represented in 2's complement, what is the result value?\n"
           "(Answer in decimal)\n", val);
    printf(">> ");
    long long ans = 0;
    if (scanf("%lld", &ans) != 1 || ans < 0)
    {
        puts("Invalid input!");
        exit(1);
    }
    if ((unsigned) ans != (unsigned) val)
    {
        puts("Wrong answer!");
        puts("See you next time~");
        exit(1);
    }
    puts("Well done!");
    puts("Go on.");
}

void test_unsigned_underflow(void)
{
    unsigned int val = rand() % 30;
    unsigned int sub = val + rand() % 15 + 1;
    printf("\n3. Consider the following C code:\n"
            "\n// start\n"
            "unsigned int val = %d;\n"
            "unsigned int sub = %d;\n"
            "unsigned int result = val - sub;\n"
            "// end\n"
            "\nWhat is the value of the variable result?\n"
            "(Answer in hexadecimal, for example 0xdead)\n", val, sub);
    printf(">> ");
    unsigned int ans = 0;
    if (scanf("%x", &ans) != 1)
    {
        puts("Invalid input!");
        exit(1);
    }
    if (ans != (unsigned int) (val - sub))
    {
        puts("Wrong answer!");
        puts("See you next time~");
        exit(1);
    }
    puts("Nice!");
}

void test_c(void)
{
}

void test_assembly(void)
{
    unsigned int loop_time   = rand() % 6 + 1;
    unsigned int initial_val = rand() % 6;
    unsigned int mul_val     = rand() % 6 + 1;
    unsigned int add_val     = rand() % 6 + 1;
    printf("\n4. Read the following x86 assembly code:\n"
           "\n"
           "    mov ecx, 0x%hhx\n"
           "    mov eax, 0x%hhx\n"
           "    test ecx, ecx\n"
           "    jle end\n"
           "    mov esi, 0x%hhx\n"
           "    xor edx, edx\n"
           "    mov ebx, 0x%hhx\n"
           "loop:\n"
           "    imul eax, esi\n"
           "    add edx, 0x1\n"
           "    add eax, ebx\n"
           "    cmp edx, ecx\n"
           "    jnz loop\n"
           "end:\n"
           "    xor edx, edx\n"
           "\n", loop_time, initial_val, mul_val, add_val);

    puts("What value is in eax register when the control flow reaches the end label?\n(Answer in decimal)");
    printf(">> ");
    for (unsigned int i = 0; i < loop_time; i++)
        initial_val = initial_val * mul_val + add_val;

    unsigned int ans = 0;
    if (scanf("%u", &ans) != 1)
    {
        puts("Invalid input!");
        exit(1);
    }
    if (ans != initial_val)
    {
        puts("Wrong answer!");
        puts("See you next time~");
        exit(1);
    }
    puts("Good job!");
}

