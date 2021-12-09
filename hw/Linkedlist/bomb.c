#include <stdio.h>
#include<stdlib.h>
long long int n;
typedef struct person{
    long long int indice;
    struct person *next;
}Person;

void add_person(Person **nowperson, long long int indice){
    //the first person
    if(*nowperson == NULL){
        *nowperson = (Person*)malloc(sizeof(Person));
        (*nowperson)->indice = indice;
        (*nowperson)->next = (*nowperson);
        return;
    }
    Person * addperson = (Person*)malloc(sizeof(Person*));
    addperson->indice = indice;
    addperson->next = (*nowperson)->next;
    (*nowperson)->next = addperson;
    return;

}

Person *pass_bomb(Person * nowperson, unsigned long long int steps){
    if(n == 1)return nowperson;
    unsigned long long int run = steps % (unsigned long long int)n;
    //printf("%lld\n", run);
    Person *preexplode_person;
    if(run == 0)run = steps;/*if the mod is 0, we have to run the whole steps to find the pre node*/
    if(steps == 0) run = n;/*if the step is 0, we have to run the whole circle of people to the end of the round*/
    for(long long int i = 1; i < run; ++i){
        nowperson = nowperson->next;
        //printf("reun\n");
    }
    preexplode_person = nowperson;
    //printf("%lld\n",preexplode_person->indice);
    return preexplode_person;
}

Person *explode(Person *preexplode_person){
    if(preexplode_person->next == preexplode_person){
        --n;
        free(preexplode_person);
        return NULL;
    } 
    Person *explode_person = preexplode_person->next;
    preexplode_person->next = explode_person->next;
    free(explode_person);
    --n;
    return preexplode_person->next;// return the person now holding the bomb
}


void print_solution(Person *first_person){
    //printf("------------------------------------\n");
    //printf("i = %d j = %d\n", i, j);
    if(first_person == NULL){
        printf("NULL\n");
        return;
    }
    Person *nowperson = first_person;
    //printf("n = %lld\n", n);
    while(nowperson->next != first_person){
        printf("%lld ", nowperson->indice);
        nowperson = nowperson->next;
    }
    printf("%lld\n", nowperson->indice);
    //printf("------------------------------------\n");
    return;
}

int main(){
    long long int indice;
    long long int i;
    unsigned long long int j;/*0 <= j <= 2^64 -1*/
    Person *first_person = NULL;
    Person *nowperson;
    Person *prebomb_person;
    Person *holdbomb_person;
    scanf("%lld", &n); // how many people init
    for(long long int i = 0; i < n;++i){
        scanf("%lld", &indice);
        if(i == 0){
            add_person(&first_person, indice);
            nowperson = first_person;
        }
        else{
            add_person(&nowperson, indice);
            nowperson = nowperson->next;
        }
    }
    //print_solution(first_person);
    nowperson = first_person;
    while(scanf("%lld %llu", &i,&j) != EOF){
        if(i == -1 && j == -1)break;
        if(i == 1){
            prebomb_person = pass_bomb(nowperson, j);
            holdbomb_person = explode(prebomb_person);
            nowperson = holdbomb_person;
            //print_solution(nowperson);
        }
        if(i == 2){
            add_person(&nowperson, j);
            ++n;
            //print_solution(nowperson);
        }
        if(n == 1)break;/*if there is only one node left*/ 
    }
    
    print_solution(nowperson);   
    return 0;
}