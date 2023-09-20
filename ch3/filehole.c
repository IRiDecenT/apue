#include "apue.h"
#include <fcntl.h>

// 利用lseek设置offset产生一个具有空洞的文件

// FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
//  read/write for user   read for group and other
char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main()
{
    int fd;

    if ((fd = creat("file.hole", FILE_MODE)) < 0)
        err_sys("creat err");

    if ((write(fd, buf1, 10)) != 10)
        err_sys("buf1 w err");

    if ((lseek(fd, (off_t)16384, SEEK_SET)) == -1)
        err_sys("lseek err");

    if ((write(fd, buf2, 10)) != 10)
        err_sys("buf2 w err");

    return 0;
}