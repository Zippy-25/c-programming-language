#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>

#define PORT "8080"   // Port we're listening on
#define BUF_SIZE 50

//int message_count = 0;    //global counter

struct client {
    int fd;
    int message_count;
};


/*
 * Convert socket to IP address string.
 * addr: struct sockaddr_in or struct sockaddr_in6
 */
const char *inet_ntop2(void *addr, char *buf, size_t size)
{
    struct sockaddr_storage *sas = addr;
    struct sockaddr_in *sa4;
    struct sockaddr_in6 *sa6;
    void *src;

    switch (sas->ss_family) {
    case AF_INET:
        sa4 = addr;
        src = &(sa4->sin_addr);
        break;
    case AF_INET6:
        sa6 = addr;
        src = &(sa6->sin6_addr);
        break;
    default:
        return NULL;
    }

    return inet_ntop(sas->ss_family, src, buf, size);
}

/*
 * Return a listening socket.
 */
int get_listener_socket(void)
{
    int listener;              
    int yes = 1;              
    int rv;
    struct addrinfo hints, *ai, *p;

    memset(&hints, 0, sizeof hints);
    hints.ai_family   = AF_INET6;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_PASSIVE;

    if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0) {
        fprintf(stderr, "pollserver: %s\n", gai_strerror(rv));
        exit(1);
    }

    for (p = ai; p != NULL; p = p->ai_next) {
        listener = socket(p->ai_family,
                          p->ai_socktype,
                          p->ai_protocol);

        if (listener < 0) {
            continue;
        }

        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR,
                   &yes, sizeof(int));

        if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
            close(listener);
            continue;
        }
	
	char buf[BUF_SIZE];
	printf("Binded IP address: %s\n", inet_ntop2(p->ai_addr, buf, p->ai_addrlen));
        break;
    }

    if (p == NULL) {
        return -1;
    }

    freeaddrinfo(ai); 

    if (listen(listener, 10) == -1) {
        return -1;
    }

    return listener;
}


/*
 * Add a new file descriptor to the set.
 */
void add_to_pfds(struct pollfd **pfds, struct client **clients, int newfd,
                 int *fd_count, int *fd_size)
{
    if (*fd_count == *fd_size) {
        *fd_size *= 2;
        *pfds = realloc(*pfds, sizeof(**pfds) * (*fd_size));
        *clients = realloc(*clients, sizeof(**clients) * (*fd_size));
    }

    (*pfds)[*fd_count].fd = newfd;
    (*pfds)[*fd_count].events = POLLIN;
    (*pfds)[*fd_count].revents = 0;
    
    (*clients)[*fd_count].fd = newfd;
    (*clients)[*fd_count].message_count = 0;
    (*fd_count)++;
}

/*
 * Remove a file descriptor from the set.
 */
void del_from_pfds(struct pollfd pfds[], int i, int *fd_count)
{
    pfds[i] = pfds[*fd_count - 1];
    (*fd_count)--;
}

/*
 * Handle new incoming connections.
 */
void handle_new_connection(int listener, int *fd_count,
                           int *fd_size, struct pollfd **pfds, struct client **clients)
{
    struct sockaddr_storage remoteaddr;
    socklen_t addrlen;
    int newfd;
    char remoteIP[INET6_ADDRSTRLEN];

    addrlen = sizeof remoteaddr;
    newfd = accept(listener, (struct sockaddr *)&remoteaddr, &addrlen);

    if (newfd == -1) {
        perror("accept");
    } else {
        add_to_pfds(pfds, clients, newfd, fd_count, fd_size);
        printf("pollserver: new connection from %s on socket %d\n",
               inet_ntop2(&remoteaddr, remoteIP, sizeof remoteIP),
               newfd);
    }
}

/*
 * Handle data from a client.
 */
void handle_client_data(int listener, int *fd_count,
                        struct pollfd *pfds, struct client *clients, int *pfd_i)
{
    char buffer[BUF_SIZE];
    int nbytes = recv(pfds[*pfd_i].fd, buffer, sizeof buffer, 0);
    int sender_fd = pfds[*pfd_i].fd;

    if (nbytes <= 0) {
        if (nbytes == 0) {
            printf("pollserver: socket %d hung up\n", sender_fd);
        } else {
            perror("recv");
        }

        close(sender_fd);
        del_from_pfds(pfds, *pfd_i, fd_count);
        clients[*pfd_i] = clients[*fd_count - 1];
        (*pfd_i)--;
    } else {
    	buffer[nbytes] = '\0';

	printf("\nClient data: %s\n", buffer);	
	
        clients[*pfd_i].message_count++;

        char response[BUF_SIZE+16];
        snprintf(response, sizeof response, "%sCount: %d", buffer, clients[*pfd_i].message_count);
        
        printf("message sent by the server: %s\n", response);

        send(sender_fd, response, strlen(response), 0);       
    }
}

/*
 * Process all connections.
 */
void process_connections(int listener, int *fd_count,
                         int *fd_size, struct pollfd **pfds, struct client **clients)
{
    for (int i = 0; i < *fd_count; i++) {
        if ((*pfds)[i].revents & (POLLIN | POLLHUP)) {
            if ((*pfds)[i].fd == listener) {
                handle_new_connection(listener, fd_count,
                                      fd_size, pfds, clients);
            } else {
                handle_client_data(listener, fd_count,
                                   *pfds, *clients, &i);
            }
        }
    }
}

int main(void)
{
    int listener;
    int fd_size = 5;
    int fd_count = 0;
    struct pollfd *pfds = malloc(sizeof *pfds * fd_size);
    struct client *clients = malloc(sizeof *clients * fd_size);

    listener = get_listener_socket();
    if (listener == -1) {
        fprintf(stderr, "error getting listening socket\n");
        exit(1);
    }

    pfds[0].fd = listener;
    pfds[0].events = POLLIN;
    fd_count = 1;

    puts("pollserver: waiting for connections...");

    for (;;) {
        int poll_count = poll(pfds, fd_count, -1);

        if (poll_count == -1) {
            perror("poll");
            exit(1);
        }

        process_connections(listener, &fd_count,
                            &fd_size, &pfds, &clients);
    }

    free(pfds);
}

