#include "func.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    Node* first = NULL;
    Node* second = NULL;
    Node* third = NULL;

    first = (Node*) malloc(sizeof(Node));
    second = (Node*) malloc(sizeof(Node));
    third = (Node*) malloc(sizeof(Node));

    first->data = 0;
    first->next = second;
    second->data = 1;
    second->next = third;
    third->data = 2;
    third->next = NULL;

    printlist(first);


    return 0;
}