#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct{
    char name[MAX_NAME];
    int age;
}person;

//reason of creating the array in pointer type
//no need the space for the struct
//easy to tell when the spot of the table is empty (NULL)
person * hash_table[TABLE_SIZE];

//to get a random number from the name
//has to be always the same output with the same input
unsigned int hash(char *name){
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0;
    for(int i = 0; i < length; ++i){
        hash_value += name[i];
        hash_value =( hash_value * name[i]) % TABLE_SIZE;
    }
    return hash_value;
}

//make sure the table is empty
void init_hash_table(){
    for(int i = 0; i < TABLE_SIZE; ++i){
        hash_table[i] = NULL;
    }
}

void print_table(){
    printf("Start!!\n");
    for(int i = 0; i < TABLE_SIZE; ++i){
        if(hash_table[i] == NULL) printf("\t%i\t---\n", i);
        else printf("\t%i\t%s\n", i, hash_table[i]->name);   
    }
    printf("End\n");
}

bool hash_table_insert(person *p){
    if(p == NULL) return false;
    int index = hash(p->name);

    if(hash_table[index] != NULL){
        //collision
        return false;
    }
    hash_table[index] = p;
    return true;
}

void hash_table_deletion(char *name){
    int index = hash(name);
    if(hash_table[index] != NULL && 
    strncmp(hash_table[index]->name, name, MAX_NAME) == 0){
        hash_table[index] = NULL;
    }
}



person *hash_table_lookup(char *name){
    if(name == NULL) return NULL;
    int index = hash(name);
    if(hash_table[index] != NULL && strncmp(hash_table[index]->name, name, MAX_NAME) == 0){
        return hash_table[index];
    }
}
int main(){
    init_hash_table();
    print_table();

    person Stefano = {.name = "Stefano", .age = 4};
    person Georgio = {.name = "Georgio", .age = 2};
    person Ida = {.name = "Ida", .age = 1};
    person Leo = {.name = "Leo", .age = 1};
    person Harry = {.name = "Harry", .age = 20};
    person Kitty = {.name = "Kitty", .age = 19};
    person Teresa = {.name = "Teresa", .age = 19};
    person Sanny = {.name = "Leo", .age = 19};
    person Jenny = {.name = "Leo", .age = 13};
    person Athina = {.name = "Leo", .age = 3};

    hash_table_insert(&Stefano);
    hash_table_insert(&Georgio);
    hash_table_insert(&Ida);
    hash_table_insert(&Leo);
    hash_table_insert(&Harry);
    hash_table_insert(&Kitty);
    hash_table_insert(&Teresa);
    hash_table_insert(&Sanny);
    hash_table_insert(&Jenny);
    hash_table_insert(&Athina);


    print_table();
    hash_table_deletion("Stefano");
    person *tmp = hash_table_lookup("Stefano");
    if(tmp == NULL){
        printf("Stefano IS NOT FOUND!!\n");
    }
    else printf("Found : %s\n", tmp->name);

    person *temp = hash_table_lookup("Harry");
    if(temp == NULL){
        printf("Harry IS NOT FOUND!!\n");
    }
    else printf("Found : %s\n", temp->name);



    /*printf("Stefano => %u\n", hash("Stefano"));
    printf("Georgio => %u\n", hash("Georgio"));
    printf("Ida => %u\n", hash("Ida"));
    printf("Leo => %u\n", hash("Leo"));
    printf("Hernan => %u\n", hash("Hernan"));
    printf("Cody => %u\n", hash("Cody"));
    printf("Athina => %u\n", hash("Athina"));
    printf("Denzel => %u\n", hash("Denzel"));
    */

    return 0;
}
