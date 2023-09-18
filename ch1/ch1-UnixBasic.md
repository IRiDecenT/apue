# chapter1 UNIX基础

1. 工作目录（working direction）
    每一个进程都有工作目录（当前工作目录），相对路径均从工作目录开始解释，函数`chdir`可以更改工作目录。
    eg： `doc/memo/joe` 相对   `/usr/lib/init`绝对（从根目录/开始）

2. 文件描述符（file descriptor）
    小的非负整数，kernel用以标识特定进程正在访问的文件，syscall open()的描述`If successful, open() returns a non-negative integer, termed a file descriptor.  It returns -1 on failure.  The file pointer (used to
     mark the current position within the file) is set to the beginning of the file.`，在C程序中，fd即为一个int值
     每当运行一个新程序时，shell为其打开三个文件描述符(都链接向终端)
     - 标准输入（standard input） fd = 0
     - 标准输出（standard output）fd = 1
     - 标准错误（standard error） fd = 2
    理解重定向与文件描述符

3. 程序和进程
    程序（program）是存储在磁盘某个目录上的可执行文件，kernel使用`exec`一族函数将程序读入内存。
    程序的执行实例称为进程（process），在某些操作系统中用任务（task）表示正在被执行的程序。
    **进程 = 内核维护进程的数据结构（进程pcd，linux中具体为结构体task_struct） + 进程的代码和数据**
    Unix系统保证每一个进程都有唯一的数字标志符，称为进程ID（process ID， pid），非负整数，标准保证其能保存在一个长整型中,`getpid()`获取当前进程的pid，返回pid_t类型

4. 进程控制 `fork exec waitpid` —— 实现minishell

5. 线程（thread） 在linux中为“轻量化进程”，多个控制线程充分利用多处理器的并行能力（线程模型是在进程模型建立很久之后才被 引入到UNIX系统中）

6. 出错处理  
   errno，以前定义为`extern int errno`
   但是在支持线程的环境中，多个线程共享进程地址空间，每一个线程都有属于它自己局部的errno，以避免一个线程干扰另一个线程，linux下支持多线程存取errno，其定义为：
   ```c
   extern int *__errno_location(void);
   #define errno (*__errno_location());
   ```
   errno两条规则：
   - 如果没有出错，其值不会被例程清除，仅函数返回值明确指出出错，才去检验其值
   - 任何函数都不会将errno值设置为0，而且在`<errno.h>`中定义的所有常量都不为0
   打印出错信息：
   ```c
   #include <string.h>
   char* strerror(int errnum);// errno映射为一个出错消息字符串，返回指向该字符串的指针
   
   #include <stdio.h>
   void perror(const char *msg);//首先输出msg指向的字符串，冒号空格，对应errno的出错消息(一般把程序名作为参数传递给perror，此时程序作为管道的一部分执行时就能知道谁出错了 prog1 < inputfile | prog2 | prog3 > outputfile) 
   ```

7. 用户ID 组ID 附属组ID

8. 信号（signal） 用于通知进程发生某种情况，三种处理信号方式：  
    - 忽略 硬件异常对于除0或者访问进程地址空间以外的存储单元，其后果不确定，不推荐
    - 按照系统默认方式，例如除0，系统默认终止该进程
    - 提供一个函数，信号发生时调用该函数，这样的做法称为捕捉信号，自编函数我们能知道什么时候产生什么信号，并按期望的方式处理

9. 系统调用和库函数
    系统调用（system call），OS的服务入口点，由此程序向kernel请求服务，各版本的UNIX实现都提供良好定义，数量有限，直接进入kernel的入口
    库函数可能调用一个或者多个系统调用，但其不是kernel的入口点
    system call 提供最小接口，库函数提供较为复杂的功能（malloc内存管理的机制，IO缓冲等）
    