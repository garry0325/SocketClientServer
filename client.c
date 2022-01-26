#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    int sockfd = 0;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd == -1) {
        printf("Fail to create a socket");
        return -1;
    }

    struct sockaddr_in serverInfo;
    bzero(&serverInfo,sizeof(serverInfo));
    serverInfo.sin_family = PF_INET;
    serverInfo.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverInfo.sin_port = htons(8700);
    
    int err = connect(sockfd, (struct sockaddr *) &serverInfo, sizeof(serverInfo));
    if(err == -1){
        printf("Connection error");
    }

    char message[] = "Hello Sockets";
    char buffer[100] = {};
    send(sockfd, message, sizeof(message), 0);
    printf("sent\n");
    printf("close socket\n");
    close(sockfd);
    
    return 0;
}