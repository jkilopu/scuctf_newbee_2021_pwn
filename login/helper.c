#include "helper.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void welcome(void)
{
    puts("\nWelcome to user management system!");
}

void menu(void)
{
    puts("1. add user");
    puts("2. log in");
    puts("3. delete user");
    puts("4. exit");
}

unsigned int Read(char *buf, unsigned int count)
{
    unsigned int actual_len = 0;

    while (actual_len < count)
    {
        int ret = read(0, buf + actual_len, 1);
        if (ret < 0)
        {
            perror("read");
            exit(1);
        }
        else if (ret == 0)
            break;

        if (buf[actual_len] == '\n')
        {
            buf[actual_len] = '\0';
            break;
        }

        actual_len++;
    }

    return actual_len;
}

void get_random_password(char *password, unsigned int len)
{
    int fd = open("/dev/urandom", O_RDONLY);

    unsigned int seed;

    for (unsigned int i = 0; i < len; i++)
    {
        if (read(fd, &seed, sizeof(seed)) != sizeof(seed))
        {
            puts("What happened?");
            exit(1);
        }

        srand(seed);
        password[i] = rand() % 79 + 48;
    }

    if (close(fd) < 0)
    {
        perror("close");
        exit(1);
    }
}
