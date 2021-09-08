#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#define MAX_NAME 256
#define TABLE_SIZE 10


typedef struct person{
    char name[MAX_NAME];
    int age;
    struct person *next;
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
        hash_value =(hash_value * name[i]) % TABLE_SIZE;
    }
    return hash_value;
}

//make sure the table is empty
void init_hash_table(){
    for(int i = 0; i < TABLE_SIZE; ++i)
        hash_table[i] = NULL;
}

void print_table(){
    printf("Start!!\n");
    for(int i = 0; i < TABLE_SIZE; ++i){
        if(hash_table[i] == NULL)
            printf("\t%i\t---\n", i);
        else{
            printf("\t%i\t", i);
            person *tmp = hash_table[i];
            while(tmp != NULL){
                if(tmp->next == NULL)
                    printf("%s\n", tmp->name);
                else
                    printf("%s - ", tmp->name);
                tmp = tmp->next;
            }
        }       
    }
    printf("End\n");
}

bool hash_table_insert(person *p){
    if(p == NULL) return false;
    int index = hash(p->name);
    //add the person to the front of the list
    p->next = hash_table[index];
    hash_table[index] = p;
    return true;
}

void hash_table_deletion(char *name){
    int index = hash(name);
    person *prev = NULL;
    person *tmp = hash_table[index];
    while(tmp!=NULL && strncmp(tmp->name, name, MAX_NAME) != 0){
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return;
    if(prev == NULL)
        hash_table[index] = NULL;
    else
        prev->next = tmp->next;
    return;
}

person *hash_table_lookup(char *name){
    if (name == NULL)
        return NULL;
    int index = hash(name);
    person *tmp = hash_table[index];
    while (tmp != NULL && strncmp(tmp->name, name, MAX_NAME) != 0){
        //printf("lookup:%s\n", tmp->name);
        tmp = tmp->next;
    }    
    return tmp;
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
    person Sanny = {.name = "Sanny", .age = 19};
    person Jenny = {.name = "Jenny", .age = 13};
    person Athina = {.name = "Athina", .age = 3};

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

    //hash_table_deletion("Kitty");
    //hash_table_deletion("Sanny");

    person *tmp = hash_table_lookup("Stefano");
    if(tmp == NULL)
        printf("Stefano IS NOT FOUND!!\n");
    else
        printf("Found : %s\n", tmp->name);

    person *temp = hash_table_lookup("Harry");
    if(temp == NULL)
        printf("Harry IS NOT FOUND!!\n");
    else
        printf("Found : %s\n", temp->name);

    print_table();
    return 0;
}
