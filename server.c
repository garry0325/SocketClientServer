#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    char buffer[256] = {};
    char message[] = "This is server.\n";
    int sockfd = 0, clientSockfd = 0;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd == -1) {
        printf("Fail to create a socket");
        return -1;
    }

    struct sockaddr_in serverInfo, clientInfo;
    socklen_t addrlen = sizeof(clientInfo);
    bzero(&serverInfo, sizeof(serverInfo));

    serverInfo.sin_family = PF_INET;
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(8700);
    bind(sockfd, (struct sockaddr *) &serverInfo, sizeof(serverInfo));
    listen(sockfd, 5);

    while(1) {
        clientSockfd = accept(sockfd, (struct sockaddr *) &clientInfo, &addrlen);
        recv(clientSockfd, buffer, sizeof(buffer), 0);
        printf("Get: %s\n", buffer);
    }

    return 0;
}