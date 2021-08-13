#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

Node* partition(Node* head, Node* end, Node** NewHead, Node** NewEnd){
    Node* pivot = head;
    Node* cur = head->next;
    Node* prev = head;
    Node* tmp;
    (*NewHead) = pivot;
    (*NewEnd) = pivot;
    while(cur != NULL){
        if(cur->data < pivot->data){
            tmp = cur->next;
            prev->next = cur->next;
            cur->next = *NewHead;
            (*NewHead) = cur;
            cur = tmp;
        }
        if(cur->data >= pivot->data){
            (*NewEnd) = cur;
            cur = cur->next;
        }
    }
    return pivot;
}

Node* Get_tail(Node**NewHead){
    Node* cur = *NewHead;
    while(cur != NULL && cur->next != NULL){
        cur = cur->next;
    }
    return cur;
}

Node* quicksortRecur(Node* head, Node* end){
    Node* NewHead;
    Node* NewEnd;
    Node* pivot = partition(head, end, &NewHead, &NewEnd);
}