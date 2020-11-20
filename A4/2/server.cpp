#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
using namespace std;
#define MAXQUEUE 10
//mutex streammutex;

void serve(int consockfd, int i)
{
    char buffer[1024];
    while (1)
    {
        int x = read(consockfd, buffer, 5);
	if (x<5)
	{
		cout << "No input from client " << i << ". Closing connection\n";
		close(consockfd);
		break;
	}
        string input = string(buffer);
        // cout << input << " " << input.size() << "\n";
	if (input == "FILE")
	{
		int n=read(consockfd, buffer, 1000);
		if (n<=0)
		{
			continue;
		}
		string fname = string(buffer);
		cout << "Client " << i << " requested file " << fname << "\n";
		FILE * f = fopen(fname.c_str(), "r");
		if (f==NULL)
		{
			cout << "File not found\n";
			strcpy(buffer, "NOTFOUND");
			write(consockfd, buffer, 9);
		}
		else
		{
			cout << "Sending file " << fname << "\n";
			strcpy(buffer, "FOUND");
			write(consockfd, buffer, 9);
			while(fgets(buffer, 1000 , f) != NULL) {
				write(consockfd, buffer, 1000);
			}
		}

	}
        if (input == "EXIT")
        {
            cout << "Client exited\n";
            return;
        }
    }
}

int main()
{
    int lstnsockfd, consockfd, portno = 3000;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;

    memset((char *) &serv_addr,0, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port        = htons(portno);

    // Server protocol
    /* Create Socket to receive requests*/
    lstnsockfd = socket(AF_INET, SOCK_STREAM, 0);

    /* Bind socket to port */
    bind(lstnsockfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr));
    printf("Bounded to port\n");
    vector <thread> threads;
    int i=0;
    while (1)
    {
        printf("Listening for incoming connections\n");

        /* Listen for incoming connections */
        listen(lstnsockfd, MAXQUEUE); 

        /* Accept incoming connection, obtaining a new socket for it */
        consockfd = accept(lstnsockfd, (struct sockaddr *) &cli_addr, &clilen);
        
        printf("Accepted connection from client no %d\n", i);
        threads.push_back(thread(serve, consockfd, i));
        ++i;
    }
    close(lstnsockfd);
}
