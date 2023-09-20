#include "apue.h"
#include <fcntl.h>

//第一个参数指定文件描述符，打印该文件描述符所选择的文件标志说明

int main(int argc, char* argv[])
{
    int val;

    if(argc != 2)
        err_quit("usage: ./pfileinfo <fd#>");
    
    if((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0)
    {
        err_sys("fcntl err for fd %d", atoi(argv[1]));
    }

    // val 此时为状态， 与上屏蔽字 O_ACCMODE获取方式位
    switch (val & O_ACCMODE)
    {
    case O_RDONLY:
        printf("read only");
        break;
    case O_WRONLY:
        printf("write only");
        break;
    case O_RDWR:
        printf("read and write");
        break;
    
    default:
        err_dump("unknow access mode");
        break;
    }
    
    //上面几个状态说明其文件状态标志使用的位是相关联的，所以要与上一个屏蔽位
    // 下面代码可以说明下面几个文件状态标志是二进制串中的不同的位 

    if( val & O_APPEND)
        printf(", append");
    if(val & O_NONBLOCK)
        printf(", nonblocking");
    if(val & O_SYNC)
        printf(", synchronous writes");
    
    #if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
        if(val & O_FSYNC)
            printf(", synchronous writes");
    #endif

    putchar('\n');
    exit(0);
}
