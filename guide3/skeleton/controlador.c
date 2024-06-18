#include <stdio.h>
#include "mysystem.h"

void controller(int N, char** commands) {
	int count = -1;
	int ret = 1;
	for (int i = 0;i < N;i++) {
		printf("\nCOMANDO %d: a executar mysystem para %s\n", i, commands[i]);
		
		if (fork() == 0) {
			while (ret != 0) {
				count++;
				ret = mysystem(commands[i]);

			}
		
			_exit(count);
		}
	}

	for(int i = 0;i < N;i++) {
		int status = 0;
		pid_t wait_pid = wait(&status);
		if (WIFEXITED(status)) {
			printf("child process terminated normally\n");
		}
	}
}

int main(int argc, char* argv[]) {

	char* commands[argc - 1];
	int N = 0;
	for (int i = 1; i < argc; i++) {
		commands[N] = strdup(argv[i]);
		printf("command[%d] = %s\n", N, commands[N]);
		N++;
	}

	controller(N, commands);

	return 0;
}