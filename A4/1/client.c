#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <netinet/in.h>

#define MAX 1024
#define PORT 8080 
#define SA struct sockaddr 

void func(int sockfd, int argc, char* argv[]) 
{
    if (argc == 4) {
        freopen(argv[2],"r",stdin);
        freopen(argv[3],"w",stdout);
    }
    char buff[MAX]; 
    int n; 
    for (;;) { 
        bzero(buff, sizeof(buff)); 
        if (argc != 4){
            printf("Enter the string : "); 
        }
        n = 0; 
        while ((buff[n++] = getchar()) != '\n'); 
        write(sockfd, buff, sizeof(buff)); 
        bzero(buff, sizeof(buff)); 
        read(sockfd, buff, sizeof(buff)); 
        if (argc != 4) {
            printf("From Server : "); 
        }
        printf("%s", buff);
        if ((strncmp(buff, "EXIT", 4)) == 0) { 
            if (argc !=4) {
                printf("Client Exit...\n"); 
            }
            break; 
        } 
    } 
} 
  
int main(int argc, char* argv[]) 
{ 
    if (argc<2){
        printf("Give IP Address of server as argument.\n");
        exit(1);
    }
    int sockfd, connfd; 
    struct sockaddr_in servaddr, cli; 
  
    // socket create and varification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
  
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    
    // Replace Server IP Address here.
    struct hostent *ptrh = gethostbyname(argv[1]);
    memcpy(&servaddr.sin_addr,ptrh->h_addr,ptrh->h_length);

    // connect the client socket to server socket 
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
        printf("connected to the server..\n"); 
  
    // function for chat 
    func(sockfd, argc, argv); 
  
    // close the socket 
    close(sockfd); 
} 