// Compile: gcc stackoverflow.c ../common_linux.c -o stackoverflow -no-pie -fno-stack-protector
#include "../common_linux.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void welcome(void);
void vuln_echo(void);

int main(void)
{
    setup();
    welcome();

    vuln_echo();

    return 0;
}

void welcome(void)
{
    puts("Do you know stack overflow and ret2text?");
}

void vuln_echo(void)
{
    char buf[0x30];
    gets(buf);
    puts(buf);
    puts("Goodbye~");
}

void backdoor(void)
{
    puts("What's this?");
    system("/bin/sh");
}

void alarm_handler(int sig)
{
    puts("Timeout!");
    exit(0);
}
