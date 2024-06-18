#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"

int main(int argc, char* argv[]) {

	if (argc < 2) {
		printf("Missing argument.\n");
		_exit(1);
	}
	//TODO
	pid_t pid = getpid();

	char fifo_name[50];
	sprintf(fifo_name, CLIENT"_%d", pid);

	if (mkfifo(fifo_name, 0644) < 0) {
		perror("Error creating fifo");
		_exit(1);
	}

	int needle = atoi(argv[1]);
	Msg msg;
	msg.pid = pid;
	msg.needle = needle;
	msg.occurrences = 0;

	int fd = open(SERVER, O_WRONLY);

	write(fd, &msg, sizeof(Msg));

	int fd_client = open(fifo_name, O_RDONLY);
	int bytes_read = read(fd_client, &msg, sizeof(msg));

	return 0;
}

