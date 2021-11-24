// Compile: gcc ../common_linux.c got_it.c -o got_it -Wl,-z,norelro
#include "../common_linux.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char scuctf[] = "www.scuctf.com";
char ctfwiki[] = "ctf-wiki.org";
char pwn_college[] = "pwn.college";
char pwnable_kr[] = "pwnable.kr";
char pwnable_tw[] = "pwnable.tw";

#define SITE_NUM 5
char *site_strings[SITE_NUM] = {
    scuctf,
    ctfwiki,
    pwn_college,
    pwnable_kr,
    pwnable_tw,
};

void welcome(void);
void menu(void);
void show(void);
void edit(void);

int main(void)
{
    setup();
    welcome();

    while (1)
    {
        menu();
        int choice = read_int();
        switch (choice)
        {
            case 1:
                show();
                break;
            case 2:
                edit();
                break;
            case 3:
                goto end;
            default:
                puts("Invalid choice.");
                break;
        }
    }

end:
    puts("Goodbye~");

    return 0;
}

void welcome(void)
{
    puts("Welcome!");
    puts("I've got some pwn websites for you.");
    puts("If you don't like them, feel free to change them.");
    puts("");
}

void menu(void)
{
    puts("1. show");
    puts("2. edit");
    puts("3. exit");
    printf("> ");
}

static void check_boundary(int idx)
{
    if (idx < 0 || idx >= SITE_NUM)
    {
        puts("Invalid index detected.");
        puts("You are hacker!");
        exit(1);
    }
}

void show(void)
{
    printf("which? ");
    int idx = read_int();
    check_boundary(idx);
    printf("website: ");
    puts(site_strings[idx]);
}

void edit(void)
{
    printf("which? ");
    int idx = read_int();
    check_boundary(idx);
    printf("your new website: ");
    read(0, site_strings[idx], 0x12);
}
