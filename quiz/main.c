// Compile: gcc helper.c test.c main.c ../common_linux.c -o quiz

#include "../common_linux.h"
#include "test.h"
#include "helper.h"
#include <time.h>
#include <stdlib.h>

int main(void)
{
    setup();
    srand(time(NULL));
    welcome();

    test_hex();
    test_int_uint();
    test_unsigned_underflow();
    //test_c();
    test_assembly();

    reward();

    return 0;
}
