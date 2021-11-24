// gcc test_your_nc.c ../common_linux.c -o test_your_nc
#include "../common_linux.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    setup();

    puts("Welcome to SCUCTF 2021 Nov.!");
    puts("Your nc works fine.");
    puts("Here is a shell for you.");

    system("/bin/sh");

    return 0;
}
