// backlog 参数
#include <arpa/inet.h>
#include <assert.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

static bool stop = false;
// SIGTERM 信号的处理函数，触发时结束主程序中的循环
static void handle_term(int sig)
{
    stop = true;
}

int main(int argc, char *argv[])
{
    signal(SIGTERM, handle_term);

    if (argc <= 3) {
        printf("usage: %s ip_address port_number backlog\n", basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);
    int backlog = atoi(argv[3]);

    // 创建 socket
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    // 创建一个 IPv4 socket 地址
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);  // 字符串表示的 IP 地址转换成网络字节序整数表示的 IP 地址
    address.sin_port = htons(port);             // 将主机字节序数据转化为网络字节序

    // 命名 socket
    int ret =
        bind(sock, (struct sockaddr *)&address, sizeof(address));  // 专用 socket 地址类型强制转换为通用 socket 地址类型
    assert(ret != -1);

    // 监听 socket
    ret = listen(sock, backlog);
    assert(ret != -1);

    // 循环等待连接，直到有 SIGTERM 信号将它中断
    while (!stop) {
        sleep(1);
    }

    // 关闭 socket
    close(sock);
    return 0;
}
