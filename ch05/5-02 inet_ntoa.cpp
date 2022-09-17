// 不可重入的 inet_ntoa 函数
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    char ip1[] = "1.2.3.4";
    in_addr address;
    inet_aton(ip1, &address);

    char ip2[] = "10.194.71.60";
    in_addr address2;
    inet_aton(ip2, &address2);

    char *szValue1 = inet_ntoa(address);
    char *szValue2 = inet_ntoa(address2);

    printf("address 1:%s\n", szValue1);
    printf("address 2:%s\n", szValue2);

    return 0;
}
