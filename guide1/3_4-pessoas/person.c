#include "person.h"
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>  /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <string.h>

#define output_file "pessoas.bin"



int add_person(char* name, int age) {
    int o;

    if ((o = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0640)) == -1) {
        perror("erro na abertura do ficheiro de saida");
        return 1;
    }
    Pessoa pessoa;
    strcpy(pessoa.name, name);
    pessoa.age= age;

    write(o, &pessoa, sizeof(Pessoa));

    // memset(&pessoa, 0, sizeof(Pessoa)); 

    int seek_res = lseek(o,-sizeof(Pessoa), SEEK_CUR);
    if (seek_res == -1) {
        perror("erro no lseek");
        return 1;
    }

    close(o);
    return seek_res/sizeof(Pessoa);
}

