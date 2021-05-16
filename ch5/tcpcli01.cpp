//
// Created by 小尹 on 2021-05-16.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


void str_cli(int sockfd) {
    char buf[1024];
    int n;
    while( (n = read(0, buf, sizeof(buf))) > 0) {
        write(sockfd, buf, n);
    }
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("usage error : tcpcli <ip>");
        return 0;
    }


    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi("5005"));

    int serverfd = socket(AF_INET, SOCK_STREAM, 0);

    if (connect(serverfd, (struct sockaddr *)&server_addr, sizeof(server_addr))!=0) {
        perror("connect");
        return 0;
    }
    else {
        printf("ok\n");
    }

    str_cli(serverfd);

    return 0;
}
