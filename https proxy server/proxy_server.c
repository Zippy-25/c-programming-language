// proxy_server.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#define PORT "8080"
#define MAX_EVENTS 64
#define BUF_SIZE 4096

int set_nonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

int create_listener() {
    struct addrinfo hints, *res;
    int listener;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, PORT, &hints, &res);

    listener = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    bind(listener, res->ai_addr, res->ai_addrlen);
    listen(listener, 10);

    set_nonblocking(listener);

    freeaddrinfo(res);
    return listener;
}

int connect_to_host(char *host) {
    struct addrinfo hints, *res;
    int server_fd;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(host, "80", &hints, &res);

    server_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    connect(server_fd, res->ai_addr, res->ai_addrlen);

    set_nonblocking(server_fd);

    freeaddrinfo(res);
    return server_fd;
}

int main() {
    int listener = create_listener();
    int epfd = epoll_create1(0);

    struct epoll_event ev, events[MAX_EVENTS];

    ev.events = EPOLLIN;
    ev.data.fd = listener;
    epoll_ctl(epfd, EPOLL_CTL_ADD, listener, &ev);

    printf("Proxy running on port 8080...\n");

    while (1) {
        int n = epoll_wait(epfd, events, MAX_EVENTS, -1);

        for (int i = 0; i < n; i++) {

            int fd = events[i].data.fd;

            // New client connection
            if (fd == listener) {
                int client_fd = accept(listener, NULL, NULL);
                set_nonblocking(client_fd);

                ev.events = EPOLLIN;
                ev.data.fd = client_fd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd, &ev);

                printf("New client connected: %d\n", client_fd);
            }

            // Client sent data
            else if (events[i].events & EPOLLIN) {
                char buffer[BUF_SIZE];
                int bytes = recv(fd, buffer, sizeof(buffer), 0);

                if (bytes <= 0) {
                    close(fd);
                    continue;
                }

                buffer[bytes] = '\0';

                printf("Received request:\n%s\n", buffer);

                // Extract host (very naive parsing)
                char host[256];
                sscanf(buffer, "GET http://%255[^/]", host);

                printf("Connecting to host: %s\n", host);

                int server_fd = connect_to_host(host);

                send(server_fd, buffer, bytes, 0);

                // Now relay response
                while (1) {
                    int r = recv(server_fd, buffer, sizeof(buffer), 0);
                    if (r <= 0) break;
                    send(fd, buffer, r, 0);
                }

                close(server_fd);
                close(fd);
            }
        }
    }

    close(listener);
}

