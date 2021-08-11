#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
    insertion_from_tail(&first, 3);
    append(first, 7);

    printlist(first);
    int i = count_list_length(first, 0);
    printf("The list length is %d\n", i);
    if(find_element(first, 7)){
        printf("The element exists in the list.\n");
    }
    else printf("Does not exist.\n");
    Node* middle = find_middle_element(first);
    printf("middle element is %d\n", middle->data);


    return 0;
}