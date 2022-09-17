// 接受一个异常的连接
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc <= 2) {
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);

    // 创建一个 IPv4 socket 地址
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);  // 字符串表示的 IP 地址转换成网络字节序整数表示的 IP 地址
    address.sin_port = htons(port);             // 将主机字节序数据转化为网络字节序

    // 创建 socket
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    // 命名 socket
    int ret =
        bind(sock, (struct sockaddr *)&address, sizeof(address));  // 专用 socket 地址类型强制转换为通用 socket 地址类型
    assert(ret != -1);

    // 监听 socket
    ret = listen(sock, 5);
    assert(ret != -1);

    // 暂停 20 秒以等待客户端连接和相关操作（掉线或者退出）完成
    sleep(20);

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);
    int connfd = accept(sock, (struct sockaddr *)&client, &client_addrlength);  // 接受连接
    if (connfd < 0) {
        printf("errno is: %d\n", errno);
    } else {
        // 接受连接成功则打印出客户端的 IP 地址和端口号
        char remote[INET_ADDRSTRLEN];
        printf("connected with ip: %s and port: %d\n",
               inet_ntop(AF_INET, &client.sin_addr, remote,
                         INET_ADDRSTRLEN),  // 将网络字节序整数表示的 IP 地址转化为字符串表示的 IP 地址
               ntohs(client.sin_port));  // 将网络字节序数据转化为主机字节序
        close(connfd);
    }

    close(sock);
    return 0;
}
