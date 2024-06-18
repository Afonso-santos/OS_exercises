#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"
#include "vector.h"

//FIFO criado pelo servidor
//Cliente pode receber um sigpipe (concorrência!)

int main(int argc, char* argv[]) {

	init_vector();
	print_vector();

	//TODO

	if (mkfifo(SERVER, 0644) < 0) {
		perror("Error creating fifo");
		return 1;
	}

	int fd = open(SERVER, O_RDONLY);
	printf("Server_fifo opened\n");
	Msg msg;

	
	while (1) {
		int bytes_read=0;
		while ((bytes_read = read(fd, &msg, sizeof(msg))) > 0) {
			printf("Received needle %d from client %d\n", msg.needle, msg.pid);
			msg.occurrences = count_needle(msg.needle);
			printf("Occurrences_server: %d\n", msg.occurrences);

			char fifo_name[50];
			sprintf(fifo_name, CLIENT"_%d", msg.pid);

			int fd_client = open(fifo_name, O_WRONLY);
			write(fd_client, &msg, sizeof(msg));

			close(fd_client);
		}
	}


	return 0;
}
