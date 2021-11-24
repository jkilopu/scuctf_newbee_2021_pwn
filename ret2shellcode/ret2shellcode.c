// Compile: gcc ret2shellcode.c ../common_linux.c -o ret2shellcode -fno-stack-protector -z execstack
#include "../common_linux.h"
#include <stdio.h>
#include <unistd.h>

void welcome(void)
{
    puts("\"Shellcoding is the art of injecting code into a program, usually during exploitation,\n"
            "to get it to carry out actions desired by the attacker\"\n\t-- By pwn.college");
    puts("Try to inject your own shellcode!\n");
}

int main(void)
{
    setup();
    welcome();

    char buf[0x80];
    printf("Your input will be saved at %p\n", buf);
    printf("Input: ");
    read(0, buf, 0x90);
    printf("Result: %s\n", buf);

    return 0;
}
