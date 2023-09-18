#include "apue.h"
#include <sys/wait.h>

// mini shell 不能接收参数
static void sig_int(int); // signal catching function

int main()
{
    char buf[MAXLINE];
    pid_t pid;
    int status;

    printf("%% ");

    if(signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("signal error");
    while(fgets(buf,MAXLINE,stdin)!=NULL)
    {
        if(buf[strlen(buf) - 1] == '\n')
        {
            buf[strlen(buf) - 1] = 0; 
        }
        if( (pid = fork()) < 0)
        {
            err_sys("fork error");
        }
        else if(pid == 0) //child process
        {
            execlp(buf, buf, (char*)0);
            err_ret("couldn't execute: %s", buf);
            exit(127);
        }

        if((pid = waitpid(pid, &status, 0)) < 0)
            err_sys("waitpid error");
        printf("%% ");
    }
    exit(0);
}

void sig_int(int signo)
{
    printf("interrupt\n%% ");
}