# Data Structure Note

## $Linear$ $Data$ $Structure$ (線性資料結構)
線性資料結構，顧名思義就是直線型的排列儲存資料。一般跟指標有關的資料結構都屬於線性資料結構。

## $Linked$ $List$
Linked list 是一種線性資料結構，以資料和指標(用來連接下一個element)所構成。

Linked List的優點就在於其可以更有效率的插入一筆資料(如果是Array，必須要把所有的資料都向後移之後在插入)，所以LinkedList的大小也是可以隨著資料量的增加去做彈性調整。

壞處是，我們沒有辦法直接呼叫中間的element，必須要從頭搜尋(以初始的指標去一個一個呼叫接下來的指標)。並且我們需要額外開空間來儲存指標，造成額外的空間占用。

```c=
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
```
### $Insertion$ $of$ $the$ $Linkedlist$
有分成3種：
* 從頭插入
* 從尾插入
* 從中插入
#### Insertion from head
![insertion head](https://i.imgur.com/0o4P6HT.png)
```c=
#include<stdio.h>
#include<stdlib.h>

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

```

#### Insertion from tail
![insertion from tail](https://i.imgur.com/cjkPxVw.png)
```c=
#include<stdio.h>
#include<stdlib.h>

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
```
#### Add a node between the list
![append](https://i.imgur.com/0erROTB.png)
```c=
#include<stdio.h>
#include<stdlib.h>

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

```


