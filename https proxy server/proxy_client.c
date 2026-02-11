#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

#define PORT "8080"
#define BUF_SIZE 4096

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s proxy_hostname\n", argv[0]);
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

    printf("Connected to proxy.\n");

    while (1)
    {
        char website[256];
        char request[BUF_SIZE];
        char response[BUF_SIZE];

        printf("\nEnter website (example.com) or type exit: ");
        fflush(stdout);

        if (fgets(website, sizeof website, stdin) == NULL)
            break;

        if (strncmp(website, "exit", 4) == 0)
            break;

        website[strcspn(website, "\n")] = 0;  // remove newline

        // Build HTTP GET request for proxy
        snprintf(request, sizeof(request),
                 "GET http://%s/ HTTP/1.1\r\n"
                 "Host: %s\r\n"
                 "Connection: close\r\n\r\n",
                 website, website);

        printf("\nSending request:\n%s\n", request);

        send(sockfd, request, strlen(request), 0);

        printf("\n---- Response ----\n");

        int numbytes;
        while ((numbytes = recv(sockfd, response, sizeof(response)-1, 0)) > 0) {
            response[numbytes] = '\0';
            printf("%s", response);
        }

        printf("\n------------------\n");

        break; // since Connection: close
    }

    close(sockfd);
    printf("Connection closed.\n");

    return 0;
}

