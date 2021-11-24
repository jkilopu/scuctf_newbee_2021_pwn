#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void alarm_handler(int sig)
{
    puts("Timeout!");
    puts("See you next time~");
    kill(0, SIGKILL);
}

static void setup_iobuf(void)
{
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
}

#define TIMEOUT 3600
static void setup_timeout(void)
{
    signal(SIGALRM, alarm_handler);
    alarm(TIMEOUT);
}

void setup(void)
{
    setup_iobuf();
    setup_timeout();
}

int read_int(void)
{
    char buf[0x10];
    read(0, buf, 0x10);
    return atoi(buf);
}
