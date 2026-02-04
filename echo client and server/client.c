#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define PORT "8080"
#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s hostname\n", argv[0]);
        exit(1);
    }

    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    for (p = servinfo; p != NULL; p = p->ai_next) {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd == -1) continue;

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            continue;
        }
        break;
    }

    freeaddrinfo(servinfo);

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        exit(1);
    }

    while(1)
    {
    	    char buffer[BUF_SIZE - 35];
    	    char sendbuf[BUF_SIZE];
            printf("\nInput - type exit to close connection: ");
            fflush(stdout);
            
            if(fgets(buffer, sizeof buffer, stdin) == NULL)	break;
            
            if(strncmp(buffer, "exit", 4) == 0){
            	send(sockfd, NULL, 0, 0);
            	break;
            }
            
	    time_t now = time(NULL);
	    char *timestamp = ctime(&now);
	    
	    sprintf(sendbuf, "%sTimestamp: %s", buffer, timestamp);
	    
	    printf("message sent by the client: %s\n", sendbuf);
	    send(sockfd, sendbuf, strlen(sendbuf), 0);

	    
	    int numbytes = recv(sockfd, sendbuf, BUF_SIZE - 1, 0);
	    sendbuf[numbytes] = '\0';

	    printf("Server reply:%s\n", sendbuf);

    }
    printf("Connection closed\n");
    close(sockfd);
    return 0;
}

