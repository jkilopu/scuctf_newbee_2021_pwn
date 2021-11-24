// Compile: gcc ret2libc.c ../common_linux.c -o ret2libc -fno-stack-protector

#include "../common_linux.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void welcome(void);
void menu(void);
void show_addresses(void);
void return_to_somewhere(void);

int main(void)
{
    setup();
    welcome();
    menu();

    int choice;
    do
    {
        printf("Your choice: ");
        choice = read_int();
        if (choice == 1)
            show_addresses();
        else if (choice == 2)
            return_to_somewhere();
        else if (choice == 3)
            puts("Exit...");
        else
            puts("Invalid choice.");
    } while (choice != 3);

}

void welcome(void)
{
    puts("I've heard the old legend that libc is a treasure-house.");
    printf("But no one know exactly where it is");
    sleep(1);
    putchar('.');
    sleep(1);
    putchar('.');
    sleep(1);
    putchar('.');
    sleep(1);
    putchar('\n');
    sleep(1);
    putchar('\n');
    puts("You, young pwner, are the chosen one.");
    puts("I will try my best to help you find libc.");
    puts("Just go for it!");
}

void menu(void)
{
    puts("");
    puts("1. Show addresses");
    puts("2. Return to somewhere");
}

void show_addresses(void)
{
    puts("\nI have some addresses for you.");
    puts("But I don't know which one of them is in libc...");
    puts("You need to figure it out:");

    unsigned long long val = 0xdeadbeef;
    printf("%p %p %p %p %p\n\n", (void *)val, &show_addresses, &puts, &val, &stdin);
}

void return_to_somewhere(void)
{
    char buf[0x10];
    puts("\nThe stackoverflow vulnerability will help you...");
    puts("You also need an exploit technique called \"ROP\", to set arguments of \"system\" function.");
    puts("Moreover, you can find the string \"/bin/sh\" in libc");
    printf("input: ");
    gets(buf);
    printf("result: %s\n", buf);
    puts("Hope to see you in libc.\n");
}
