#include <stdlib.h>
#include <stdio.h>
#include "../templates/multi_cliente.h"

void * start_cliente(void * arg) {
	char * expression = (char*) arg;
	char command[100];
	sprintf(command, "./cliente %s", expression);
	system(command);
}

int main(int argc, char** argv) {
	int thread_cnt = argc - 1;
	pthread_t threads[thread_cnt];
	for (int i = 0; i < thread_cnt; i++) {
		pthread_create(&threads[i], NULL, start_cliente, argv[i+1]);
	}
	for (int i = 0; i < thread_cnt; i++) {
		pthread_join(threads[i], NULL);
	}
	return 0;
}