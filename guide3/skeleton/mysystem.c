#include "mysystem.h"


// recebe um comando por argumento
// returna -1 se o fork falhar
// caso contrario retorna o valor do comando executado
int mysystem (const char* command) {
	int res =-1;
	char *exec_args[20];

	char *string, *cmd,*tofree;
	int i=0;
	tofree=cmd = strdup(command);
	while((string = strsep(&cmd, " ")) != NULL){
		exec_args[i] = string;
		i++;
	}
	exec_args[i] = NULL;

	if((res = fork()) == 0) {
		execvp(exec_args[0], exec_args);
		_exit(-1);
	} else {
		int status;
		wait(&status);
		if (WIFEXITED(status)) {
			res = WEXITSTATUS(status);
		}
	}

	return res;
}