// SIGCHILD 信号的典型处理函数
#include <sys/types.h>
#include <sys/wait.h>

static void handle_child(int sig)
{
    pid_t pid;
    int stat;
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0) {
        // 对结束的子进程进行善后处理
    }
}
