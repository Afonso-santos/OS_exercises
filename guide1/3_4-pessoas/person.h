#ifndef PERSON_H
#define PERSON_H
typedef struct Person Pessoa;

struct Person {
    char name[60];
    int age;
 
};

/**
 * Adiciona uma pessoa ao ficheiro de pessoas
 * @param name nome da pessoa
 * @param age idade da pessoa
 * @return 0 em caso de sucesso, -1 em caso de erroclea
 * 
*/
int add_person(char* name, int age);
#endif