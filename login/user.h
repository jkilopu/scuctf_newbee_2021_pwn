#ifndef __USER_H
#define __USER_H

#include "password.h"

#define MAX_USER_NUM 0x10

struct User {
    struct Password password;
    unsigned int id;
};

void add_user(void);
void login_user(void);
void delete_user(void);
void add_root(void);

#endif
