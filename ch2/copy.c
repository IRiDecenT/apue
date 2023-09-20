#include "apue.h"

// usage : ./copy < infile > outfile 在终端重定向标准输入和标准输出

#define BUFFSIZE 4096

int main()
{
    int n;
    char buf[BUFFSIZE];

    while((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
    {
        if(write(STDOUT_FILENO, buf, n) != n)
            err_sys("write error");
    }

    if( n < 0 )
        err_sys("read error");

    exit(0);
}