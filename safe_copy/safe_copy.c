// Compile: gcc safe_copy.c ../common_linux.c -o safe_copy
#include "../common_linux.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_SIZE 0x100

void welcome(void);
int safe_copy(char dst_buf[], const char src_buf[],
        int start, int max_len, int boundary);

int main(void)
{
    setup();
    welcome();

    char input_buf[BUF_SIZE];
    int start = 0;
    int max_len = 0;
    int boundary = 0;

    char output_buf[BUF_SIZE];

    do
    {
        printf("Your input: ");
        read(0, input_buf, BUF_SIZE);
        printf("Start offset: ");
        if (scanf("%d", &start) != 1)
        {
            puts("Invaliad input!");
            exit(1);
        }
        printf("Max copy len: ");
        if (scanf("%d", &max_len) < 0)
        {
            puts("Invaliad input!");
            exit(1);
        }
        printf("Copy boundary: ");
        if (scanf("%d", &boundary) < 0)
        {
            puts("Invaliad input!");
            exit(1);
        }

        puts("\nOk...Let's see.");
        memset(output_buf, '#', BUF_SIZE);

        int ret;
        if ((ret = safe_copy(output_buf, input_buf, start, max_len, boundary)) < 0)
        {
            puts("Unsafe operation!\n");
        }
        else
        {
            puts("Result:");
            puts(output_buf);
            puts("");
        }

    } while (strcmp(input_buf, "exit\n") != 0);

    puts("Goodbye~");

    return 0;
}

void welcome(void)
{
    puts("Welcome to safe copy and show!");
    puts("I can copy bytes from your input array to specific position in output array and show it.");
    puts("Try it out!\n");
}

int safe_copy(char dst_buf[], const char src_buf[],
        int start, int max_len, int boundary)
{
    if (boundary < 0 || boundary > BUF_SIZE || start < 0 || max_len <= 0 || start + max_len < 0 || start + max_len >= boundary)
        return -1;

    int len;
    printf("Copy len: ");
    if (scanf("%d", &len) != 1)
    {
        puts("Invaliad input!");
        exit(1);
    }

    if (len < 0 || len > max_len)
        return -1;

    for (int i = 0; i < len; i++)
        dst_buf[start + i] = src_buf[i];

    return 0;
}
