#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

void printlist(Node* n);

void insertion_from_head(Node** head_ref, int new_data){
    /*allocate the node*/
    Node* head = (Node*) malloc(sizeof(Node));
    /*add new data*/
    head->data = new_data;
    /*connect the original head to the new node by the pointer*/
    head->next = *head_ref;
    /*change the record of the head_ref*/
    *head_ref = head;
}

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
            continue;
        }
        if(cur->data >= pivot->data){
            (*NewEnd) = cur;
            prev = cur;
            cur = cur->next;
            continue;
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
    if(head == NULL | head == end)return head;
    Node* NewHead;
    Node* NewEnd;
    Node* pivot = partition(head, end, &NewHead, &NewEnd);
    Node* tmp = NewHead;
    while( tmp != pivot && tmp->next != pivot){
        tmp = tmp->next;
    }
    if(tmp != pivot){
        tmp->next = NULL;
        NewHead= quicksortRecur(NewHead, tmp);
        tmp = Get_tail(&NewHead);
        tmp->next = pivot;
    }
    
    pivot->next = quicksortRecur(pivot->next, NewEnd);

    return NewHead;
}

void QuickSort(Node** Head_ref){
    (*Head_ref) = quicksortRecur(*Head_ref, Get_tail(Head_ref));
    return;
}

void printlist(Node* n){
    while(n != NULL){
        printf("%d%c", n->data, ','*(n->next != NULL)+' '*(n->next == NULL));
        n = n->next;
    }
    printf("\n");
    
}


int main(){
    Node* head = NULL;
    insertion_from_head(&head, 16);
    insertion_from_head(&head, 20);
    insertion_from_head(&head, 1);
    insertion_from_head(&head, 26);
    insertion_from_head(&head, 14);
    insertion_from_head(&head, 7);
    insertion_from_head(&head, 9);
    insertion_from_head(&head, 8);
    insertion_from_head(&head, 18);
    insertion_from_head(&head, 11);
    insertion_from_head(&head, 17);
    
    QuickSort(&head);
    printlist(head);
    return 0;    
}

