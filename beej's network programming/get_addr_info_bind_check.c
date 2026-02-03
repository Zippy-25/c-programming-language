/*
 * Experimental function that iterates over all addresses returned by
 * getaddrinfo() (e.g., 0.0.0.0 and ::) and attempts to create, bind, and
 * listen on a socket for each one. Some bind() calls may fail due to
 * IPv4/IPv6 wildcard address overlap in dual-stack configurations.
 * Not intended for production use.
 */

void get_listener_socket(void)
{
    int listener;
    int yes = 1;
    int rv;
    struct addrinfo hints, *ai, *p;
    char buf[BUF_SIZE];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0) {
        fprintf(stderr, "pollserver: %s\n", gai_strerror(rv));
        exit(1);
    }
    
    int i;
    for (p = ai, i = 0; p != NULL; p = p->ai_next, ++i);
    printf("length of linked list: %d\n", i);

    for (p = ai; p != NULL; p = p->ai_next) {
    
    	printf("Possible ip address: %s\n", inet_ntop2(p->ai_addr, buf, p->ai_addrlen));
    	
        listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (listener < 0) {
            continue;
        }
        
 	printf("completed socket creation\n");
 	
        //setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    
	printf("start bind\n");
	
        if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
            perror("bind failed");
            close(listener);
            continue;
        }
        
            if (listen(listener, 10) == -1) {
		return -1;
	    }
    
        printf("completed bind and break\n");
        //break;
    }

    freeaddrinfo(ai);

    if (p == NULL) {
        return -1;
    }
}
