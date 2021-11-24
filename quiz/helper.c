#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void welcome(void)
{
    puts("Welcome! You need to do 4 tests to get the shell.");
    puts("Let's begin!");
}

void reward(void)
{
    puts("\nCongratulations! You passed all the test!");
    puts("Here is your shell:");
    system("/bin/sh");
}
