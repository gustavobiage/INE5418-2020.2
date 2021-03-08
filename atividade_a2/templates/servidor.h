#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "concurrent_queue.h"

struct thread_par {
	pthread_t* self_pointer;
	struct c_queue* thread_queue;
	int client_sockfd;
	int buffer_length;
};

struct operation {
	int a;
	int b;
	char op;
};