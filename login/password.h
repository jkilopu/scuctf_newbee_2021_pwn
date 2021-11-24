#ifndef __PASSWORD_H
#define __PASSWORD_H

#define MAX_PASSWORD_LEN 0x98
#define ROOT_PASSWORD_LEN 0x30

#include <stdbool.h>

struct Password {
    char buf[MAX_PASSWORD_LEN];
    unsigned int len;
};

bool verify(const struct Password *password);

#endif
