#include "../templates/cliente.h"

void read_number(char * string, char * buffer, int * pointer) {
	int bpointer = *pointer;
	while (string[*pointer] >= '0' && string[*pointer] <= '9') {
		buffer[*pointer - bpointer] = string[*pointer];
		*pointer = *pointer + 1;
	}
	buffer[*pointer - bpointer] = '\0';
}

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Quantidade de argumentos errado\n");
		return -1;
	}
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
		printf("oops: erro ao estabelecer a conexão (%d)\n", result);
		return -1;
	}

	char value1[BUFFER_LENGTH];
	char value2[BUFFER_LENGTH];
	int pointer = 0;
	read_number(string, value1, &pointer);
	int slen = strlen(string);
	
	while (pointer < slen) {
		char op = string[pointer++];
		read_number(string, value2, &pointer);
		sprintf(buffer, "%c#%s#%s", op, value1, value2);
		write(sockfd, buffer, BUFFER_LENGTH);
		read(sockfd, value1, BUFFER_LENGTH);
	}

	strcpy(buffer, "sair");
	write(sockfd, buffer, BUFFER_LENGTH);

	printf("resultado = %s\n", value1);
	close(sockfd);
	return 0;
}