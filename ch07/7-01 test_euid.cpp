// 测试进程的 UID 和 EUID 的区别
#include <stdio.h>
#include <unistd.h>

int main()
{
    uid_t uid = getuid();
    uid_t euid = geteuid();
    printf("userid is %d, effective userid is: %d\n", uid, euid);
    return 0;
}
