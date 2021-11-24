#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "password.h"
#include "helper.h"

bool verify(const struct Password *password)
{
    struct Password tmp;

    if (password->len > MAX_PASSWORD_LEN)
    {
        puts("This is impossible!");
        exit(1);
    }

    printf("Input password: ");
    Read(tmp.buf, MAX_PASSWORD_LEN);

    for (tmp.len = 0; tmp.len < password->len; tmp.len++)
    {
        if (tmp.buf[tmp.len] != password->buf[tmp.len])
        {
            printf("Wrong password: %s\n", tmp.buf);
            break;
        }
    }

    return tmp.len == password->len;
}
