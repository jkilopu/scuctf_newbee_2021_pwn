#include "user.h"
#include "password.h"
#include "helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool has_login_as_root;
static struct User *user_list[MAX_USER_NUM];

void add_user(void)
{
    puts("Add user...");

    unsigned int idx;
    printf("Input user index: ");
    scanf("%u", &idx);
    if (idx >= MAX_USER_NUM)
    {
        puts("User index out of bound!");
        exit(1);
    }
    if (user_list[idx] != NULL)
    {
        puts("There is already a user here!");
        exit(1);
    }

    struct User *new_user = malloc(sizeof(struct User));
    
    printf("Input id: ");
    scanf("%u", &new_user->id);
    if (new_user->id == 0)
    {
        puts("You can't be root!");
        exit(1);
    }

    printf("Input password len: ");
    scanf("%u", &new_user->password.len);
    if (new_user->password.len > MAX_PASSWORD_LEN)
    {
        puts("The password is too long!");
        exit(1);
    }

    printf("Input password: ");
    if (Read(new_user->password.buf, new_user->password.len) < new_user->password.len)
    {
        puts("The password is not long enough!");
        exit(1);
    }

    user_list[idx] = new_user;

    puts("Add user done!");
}

static void delete_victim(void)
{
    puts("Delete victim...");

    unsigned int idx;
    printf("Input victim index: ");
    scanf("%u", &idx);
    if (idx >= MAX_USER_NUM)
    {
        puts("Victim index out of bound!");
        exit(1);
    }

    if (user_list[idx] == NULL)
    {
        puts("No user here!");
        exit(1);
    }

    free(user_list[idx]);

    puts("Delete victim done!");
}

void login_user(void)
{
    puts("Log in...");

    unsigned int idx;
    printf("Input user index: ");
    scanf("%u", &idx);
    if (idx >= MAX_USER_NUM)
    {
        puts("User index out of bound!");
        exit(1);
    }

    if (user_list[idx] == NULL)
    {
        puts("No user here!");
        exit(1);
    }

    if (verify(&user_list[idx]->password))
    {
        puts("Login success!");
        if (user_list[idx]->id == 0)
        {
            if (has_login_as_root)
            {
                puts("No more tricks!");
            }
            else
            {
                puts("As root, you can delete any user!");
                puts("After deleting, when the victim tries to log in, "
                     "he'll find that he can't log into his account!");
                delete_victim();
                puts("Haha. Let's see what will happen.");
                has_login_as_root = true;
            }
        }
        else
        {
            printf("Hello user %u.\n", user_list[idx]->id);
            puts("So?");
        }
    }
    else
    {
        puts("Login failed!");
    }
}

void delete_user(void)
{
    puts("Delete user...");

    unsigned int idx;
    printf("Input user index: ");
    scanf("%u", &idx);
    if (idx >= MAX_USER_NUM)
    {
        puts("User index out of bound!");
        exit(1);
    }

    if (user_list[idx] == NULL)
    {
        puts("No user here!");
        exit(1);
    }

    free(user_list[idx]);
    user_list[idx] = NULL;

    puts("Delete user done!");
}

void add_root(void)
{
    puts("Add root...");

    struct User *root = malloc(sizeof(struct User));

    root->id = 0;
    printf("The index of root is %u\n", root->id);
    root->password.len = ROOT_PASSWORD_LEN;
    get_random_password(root->password.buf, root->password.len);

    user_list[0] = root;

    puts("Add root done!");
}
