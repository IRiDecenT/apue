#include "apue.h"

#define BUFFSIZE 4096

int main()
{
    int n;
    char buf[BUFFSIZE];

    while((n = read(STDIN_FILENO, (char*)buf, BUFFSIZE)) > 0)
    {
        if((write(STDOUT_FILENO, (char*)buf, n)) != n)
        {
            err_sys("write err");
        }
        if(n < 0)
            err_sys("read err");
    }
    return 0;
}