#include "apue.h"

int main()
{
    struct stat statbuf;

    // 获取foo文件的文件当前信息，主要为了拿到文件当前权限信息
    if(stat("foo", &statbuf))
        err_sys("stat error for foo");
    
    // foo文件相对于其当前权限来设定权限
    if(chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
        err_sys("chmod error for foo");

    // bar文件直接设定权限的绝对值
    if(chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
        err_sys("chmod error for bar");

    exit(0);
}
