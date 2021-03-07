#include "../templates/calculadora.h"

int main(int argc, char **argv) {
	int sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	char * string = argv[1];
	char buffer[BUFFER_LENGTH];

	struct in_addr addr;
	inet_aton(IP, &addr);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_port = PORT;
	address.sin_addr = addr;

	len = sizeof(address);
	result = connect(sockfd, (struct sockaddr *) &address, len);
	if (result == -1) {
		printf("oops: erro ao estabelecer a conexão (%d)", result);
		return -1;
	}

	int value1, value2;
	char op;
	while (1) {
		scanf(" %s", buffer);
		if (!strcmp(buffer, "sair")) {
			write(sockfd, buffer, BUFFER_LENGTH);
			break;
		}
		sscanf(buffer, " %d%c%d", &value1, &op, &value2);
		sprintf(buffer, "%c#%d#%d", op, value1, value2);
		write(sockfd, buffer, BUFFER_LENGTH);
		read(sockfd, buffer, BUFFER_LENGTH);
		printf("r: %s\n", buffer);
	}
	close(sockfd);
	return 0;
}