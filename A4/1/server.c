#include <stdio.h>
#include <unistd.h>
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <arpa/inet.h>

#define MAX 1024
#define PORT 8080 
#define SA struct sockaddr

void toggleCase(char * str)
{
    int i = 0;
    while(str[i] != '\0')
    {
        if (str[i]>='a' && str[i]<='z') {
            str[i] = str[i] - ('a' - 'A');
        }
        else if(str[i]>='A' && str[i]<='Z') {
            str[i] = str[i] + ('a' - 'A');
        }
        i++;
    }
}

void func(int sockfd, struct sockaddr_in cli) {
    int n;
    char buff[MAX];
    for (;;) {
        bzero(buff, MAX);
        read(sockfd, buff, sizeof(buff));
        toggleCase(buff);
        write(sockfd, buff, sizeof(buff));
        if (strncmp("EXIT", buff, 4) == 0) {
            printf("Client exited. %s:%d\n\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));
            close(sockfd);
            exit(1);
        }
    }
}

int main() {
    int sockfd, connfd, len;           
    struct sockaddr_in servaddr, cli;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed.\n");
        exit(0);
    } else {
        printf("Socket created successfully.\n");
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0){
        printf("Socket bind failed.\n");
        exit(0);
    } else {
        printf("Socker successfully binded.\n");
    }
    if ((listen(sockfd, 10)) != 0) { 
        printf("Listen failed.\n"); 
        exit(0); 
    } else {
        printf("Server listening.\n"); 
    }
    while (1) {
        len = sizeof(cli);
        connfd = accept(sockfd, (SA*)&cli, (socklen_t*)&len);
        if (connfd < 0) { 
            printf("Server acccept failed...\n"); 
            exit(0); 
        } else {
            printf("Connection accepted from %s:%d\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));
        }
        pid_t childpid;
        if ((childpid = fork()) == 0) {
            close(sockfd);
            func(connfd, cli);
        }
    }
    return 0;
}