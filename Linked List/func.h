#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
    *head_ref = head;
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

void append(Node* previous_node, int new_data){
    /*allocate the node*/
    Node* node = (Node*) malloc(sizeof(Node));

    /*add new data*/
    node->data = new_data;

    /*check if previous_node is NULL*/
    if(previous_node == NULL)return;

    /*connect new node and the next node*/
    node->next = previous_node->next;

    /*connect previous node and new node*/
    previous_node->next = node;
}

void deletion_key(Node**head_ref, int key){
    Node* tmp = *head_ref; 
    Node* prev = NULL;
    /*if the head equals to the key*/
    if(tmp == *head_ref && tmp->data == key){
        *head_ref = tmp->next;
        free(tmp);
        return;
    }

    /*Find the previous node of the node to be deleted*/
    while(tmp != NULL && tmp->data != key){
        /*Change the next of the previous node*/
        prev = tmp;
        tmp = tmp->next;
    }
    
    /*Delete the key node*/
    prev->next = tmp->next;
    free(tmp);
}

void deletion_key_RECURS(Node**head, int key){
    Node* n = *head;
    if(n->data == key){
        Node* tmp = n;
        *head = n->next;
        free(tmp);
        return;
    }
    deletion_key_RECURS(&((*head)->next), key);
}

void deletion_index(Node**head, int index){
    Node* prev;
    Node* tmp = *head;
    /*if the index is 0，we have to change the head_ref*/
    if(index == 0){
        tmp = *head;
        *head = tmp->next;
        free(tmp);
        return;
    }
    /*find the previous node of the target node*/
    for(int i = 0; i < index; ++i){
        prev = tmp;
        tmp = tmp->next;
    }
    /*connect the previous node and the next node*/
    prev->next = tmp->next;
    free(tmp);
}

int count_list_length(Node* head, int num){
    if(head == NULL)return num;
    count_list_length(head->next, num+1);
}

bool find_element(Node* head, int target){
    /*if the node is NULL means there is no same element in whole linkedlist*/
    if(head == NULL)return false;
    /*find if the target is same as the data*/
    if(head->data == target)return true;
    
    find_element(head->next, target);
}

Node* find_middle_element(Node* head){
    Node* fast_ptr = head;
    Node* slow_ptr = head;
    if(head != NULL){
        while(fast_ptr != NULL && fast_ptr->next != NULL){
            fast_ptr = fast_ptr->next->next;
            slow_ptr = slow_ptr->next;
        }
    }
    return slow_ptr;
}

/*
       HEAD
        |             |             |              |             |       
        |             |             |              |             |
    +---+---+     +---+---+     +----+----+    +---+---+     +---+---+ 
    | 1  | o----->| 2 | o-----> |  3 |  o-----> 4  | o----->| 5 |NULL|
    +---+---+     +---+---+     +----+----+    +---+---+     +---+---+ 
1.    *s  *f
2.                   *s             *f
3.                                  *s                          *f  
*/
/* The idea is to first search x and y in the given linked list.
 If any of them is not present, then return. While searching for x and y,
  keep track of current and previous pointers. First change next of previous pointers,
   then change next of current pointers.
 */

void swap(Node*head, int x, int y){
    Node* n = head;
    Node* prev_x ;
    Node* prev_y;
    Node* cur_x;
    Node* cur_y;
    if(x == y)return;
    while(n != NULL){
        if(n->next->data == x){
            prev_x = n;
            cur_x = n->next;
        }
        if(n->next->data == y){
            prev_y = n;
            cur_y = n->next;
        }
        n = n->next;
    }



}
 
#endif
