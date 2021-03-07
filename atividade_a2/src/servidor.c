#include "../templates/servidor.h"

#define IP "127.0.0.1"
#define PORT 8089
#define BACKLOG 256
#define BUFFER_LENGTH 100

int operate(struct operation* operation) {
	switch (operation->op) {
		case '+':
			return operation->a + operation->b;
		case '-':
			return operation->a - operation->b;
		case '*':
			return operation->a * operation->b;
		case '/':
			return operation->a / operation->b;
	}
	return -1;
}

void* resolve_request(void* arg) {
	// printf("THREAD START\n");
	struct thread_par* parameters = (struct thread_par*) arg;
	int client_sockfd = parameters->client_sockfd;
	int buffer_length = parameters->buffer_length;
	char buffer[buffer_length];
	int pointer;
	while (1) {
		pointer = 0;
		read(client_sockfd, buffer, buffer_length);
		if (!strcmp(buffer, "sair")) {
			break;
		}
		struct operation operation;
		sscanf(buffer, "%c#%d#%d", &operation.op, &operation.a, &operation.b);
		int res = operate(&operation);
		sprintf(buffer, "%d", res);
		write(client_sockfd, buffer, buffer_length);
	}
	close(client_sockfd);
	free(parameters);
	// printf("THREAD END\n");
}

int main(int argc, char**arcv) {
	printf("Server waiting...\n");
	int server_sockfd;
	int* client_sockfd;
	int server_len, client_len;
	struct sockaddr_in server_sockaddr;
	struct sockaddr_in client_sockaddr;
	char buffer[BUFFER_LENGTH+1];
	char ch;

	// Inicializar servidor
	struct in_addr addr;
	inet_aton(IP, &addr);

	server_sockfd = (int) socket(AF_INET, SOCK_STREAM, 0);
	server_sockaddr.sin_family = AF_INET;
	server_sockaddr.sin_port = PORT;
	server_sockaddr.sin_addr = addr;

	int optval = 1;
	setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));

	server_len = sizeof(server_sockaddr);
	bind(server_sockfd, (struct sockaddr *) &server_sockaddr, server_len);
	listen(server_sockfd, BACKLOG);

	struct c_queue thread_queue;
	pthread_t threads[BACKLOG];
	queue_init(&thread_queue, BACKLOG);
	for (int i = 0; i < BACKLOG; i++) {
		push(&thread_queue, &threads[i]);
	}

	pthread_t* thread;
	struct thread_par* parameters;
	int i = 0;
	while (1) {
		client_len = sizeof(client_sockaddr);
		parameters = (struct thread_par*) malloc(sizeof(struct thread_par));

		thread = pop(&thread_queue);
		parameters->client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_sockaddr, &client_len);
		parameters->self_address = thread;
		parameters->buffer_length = BUFFER_LENGTH;
		if (i++ >= BACKLOG) {
			pthread_join(*thread, NULL);
		}
		pthread_create(thread, NULL, resolve_request, parameters);
	}
	printf("Server done\n");
	return 0;
}
