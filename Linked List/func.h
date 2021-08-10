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

void insertion_from_head(Node** head_ref, int new_data){
    /*allocate the node*/
    Node* head = (Node*) malloc(sizeof(Node));
    /*add new data*/
    head->data = new_data;
    /*connect the original head to the new node by the pointer*/
    head->next = *head_ref;
    /*change the record of the head_ref*/
    head_ref = &head;
}

void insertion_from_tail(Node** head_ref, int new_data){
    Node* n = *head_ref;
    /*allocate the node*/
    Node* node = (Node*) malloc(sizeof(Node));
    /*add new data*/
    node->data = new_data;
    node->next = NULL;
    /*if the head_ref is NULL, name the node as the head*/
    if(head_ref == NULL){
        *head_ref = node;
        return;
    }
    /*transfer to the end of the list*/
    while(n->next != NULL){
        n = n->next;
    }
    /*connect the new node the the end*/
    n->next = node;

}


#endif
