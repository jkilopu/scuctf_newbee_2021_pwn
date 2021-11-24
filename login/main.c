// Compile: gcc helper.c password.c user.c main.c ../common_linux.c -o login -O2
#include "user.h"
#include "helper.h"
#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    setup();
    add_root();
    welcome();
    menu();

    unsigned int choice;
    while (true)
    {
        printf("\n>> ");
        scanf("%u", &choice);

        switch (choice)
        {
            case 1: 
                add_user();
                break;
            case 2:
                login_user();
                break;
            case 3:
                delete_user();
                break;
            case 4:
                puts("Goodbye.");
                goto MAIN_END;
            default:
                puts("Invalid choice!");
                break;
        }
    }

MAIN_END:

    return 0;
}
