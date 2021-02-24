#include "../templates/servidor.h"

#define IP "127.0.0.1"
#define PORT 8080
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

void resolve_request(int client_sockfd, char * buffer, int buffer_length) {
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
		sprintf(buffer, "%d\n", res);
		write(client_sockfd, buffer, buffer_length);
	}
}

int main(int argc, char**arcv) {
	int server_sockfd, client_sockfd;
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

	server_len = sizeof(server_sockaddr);
	bind(server_sockfd, (struct sockaddr *) &server_sockaddr, server_len);
	listen(server_sockfd, BACKLOG);

	printf("Server waiting...\n");

	while (1) {
		client_len = sizeof(client_sockaddr);
		client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_sockaddr, &client_len);
		resolve_request(client_sockfd, buffer, BUFFER_LENGTH);
		close(client_sockfd);
	}
	printf("Server done\n");
	return 0;
}