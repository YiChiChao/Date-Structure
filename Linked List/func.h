#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

void printlist(Node* n){
    while(n != NULL){
        printf("%d\n", n->data);
        n = n->next;
    }
}



#endif
