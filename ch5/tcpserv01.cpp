//
// Created by 小尹 on 2021-05-16.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void str_echo(int socktf) {
    char buf[1024];
    int n;
    while ((n=read(socktf, buf, sizeof(buf))) > 0) {
        printf(buf);
        write(socktf, buf, n);
        memset(buf, 0, sizeof(buf));
    }
}

int main(int argc, char* argv[]) {

    pid_t pid;

    int listenfd, clientfd;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servaddr, clientaddr;
    socklen_t clientaddr_len = sizeof(clientaddr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(5005);

    if ((bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) !=0) {
        perror("bind");
        return 0;
    }

    listen(listenfd, 5);

    for (; ;) {
        clientfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientaddr_len);
        printf("client fd is %d\n", clientfd);
        if ((pid = fork()) == 0) {
            close(listenfd);
            str_echo(clientfd);
            exit(0);
        }
        close(clientfd);
    }



    return 0;
}
