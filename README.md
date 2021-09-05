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

### $Deletion$ $of$ $the$ $Linkedlist$
如果要刪除LinkedList中的某個節點，須將前一個節點中的指標換成下下一個節點的指標，並將此節點空間釋放。

如果是要刪掉一個給定的值($key$)，就要確認$struct$中的數值是否與$key$相等

#### Iterative Method
```c=
#include<stdio.h>
#include<stdlib.h>

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

```

#### Recursive Method
```c=
#include<stdio.h>
#include<stdlib.h>

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
```

如果是要刪掉某個$index$內的值，那就用for迴圈跑到那個節點。
```c=
#include<stdio.h>
#include<stdlib.h>

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
```

### $Get$ $the$ $length$ $of$ $the$ $list$
```c=
#include<stdio.h>
#include<stdlib.h>

int count_list_length(Node* head, int num){
    if(head == NULL)return num;
    count_list_length(head->next, num+1);
}
```

### $Search$ $an$ $element$ $in$ $a$ $Linked$ $List$

要判斷LinkedList當中有沒有我們指定的數字，如果有，回傳True，反之，回傳False。
#### Recursion Ｍethod
```c=
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool find_element(Node* head, int target){
    if(head == NULL)return false;
    if(head->data == target)return true;
    
    find_element(head->next, target);
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
    append(first, 7);
    
    if(find_element(first, 7))
        printf("The element exists in the list.\n");
    else printf("Does not exist.\n");


    return 0;
}
```
### $Print$ $the$ $Middle$ $Element$
紀錄一下，取中間值可能會用在已排列好的序列取中位數。
如果要取中間數，可以直接跑for迴圈就能找到。
不過有更快的方法是設定兩個pointer，一個紀錄中間數，一個紀錄終點數
>當跑得比較快的那一個等於NULL，跑得比較慢的那個POINTER就會剛好只在中間的位置


![img](https://i.imgur.com/x3mLKDu.png)
```c=
#include <stdio.h>
#include <stdlib.h>

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
3.                                  *s                          *f     */
```

所以是不是該來寫Sorting了呢XD
### $Quick$ $Sort$ $with$ $LinkedList$

|<font color="#D86DA9">16</font> |<font color="4a94ff">1</font>|20|26|14|7|9|4|8|18|11|17
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

我們以序列第一個數為 **<font color="#D86DA9">pivot</font>** ，設定兩個變數 $NewHead$，$NewEnd$用來記錄最後排序的頭跟尾的指標。

輸入$Head$和$Tail$為此序列的頭尾，並以 **<font color="#4a94ff">cur</font>** 作為移動的指標。

當 **<font color="#4a94ff">cur</font>** < **<font color="#D86DA9">pivot</font>**，將此Node->next換成 **<font color="#D86DA9">pivot</font>**，並將其設為 <font color="00c49f">$NewHead$</font>

|<font color="00c49f">1</font>|<font color="#D86DA9">16</font> |<font color="4a94ff">20</font>|26|14|7|9|4|8|18|11|17
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

當 **<font color="#4a94ff">cur</font>** > **<font color="#D86DA9">pivot</font>**，將其設為 <font color="#e89538">$NewEnd$</font>。

|<font color="00c49f">1</font>|<font color="#D86DA9">16</font> |<font color="e89538">20</font>|<font color="4a94ff">26</font>|14|7|9|4|8|18|11|17
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

|<font color="00c49f">1</font>|<font color="#D86DA9">16</font> |20|<font color="e89538">26</font>|<font color="4a94ff">14</font>|7|9|4|8|18|11|17
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

|<font color="00c49f">14</font>|1|<font color="#D86DA9">16</font> |20|<font color="e89538">26</font>|<font color="4a94ff">7</font>|9|4|8|18|11|17
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

|<font color="00c49f">7</font>|14|1|<font color="#D86DA9">16</font> |20|<font color="e89538">26</font>|<font color="4a94ff">9</font>|4|8|18|11|17
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

|<font color="00c49f">9</font>|7|14|1|<font color="#D86DA9">16</font> |20|<font color="e89538">26</font>|<font color="4a94ff">4</font>|8|18|11|17
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

|<font color="00c49f">4</font>|9|7|14|1|<font color="#D86DA9">16</font> |20|<font color="e89538">26</font>|<font color="4a94ff">8</font>|18|11|17
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

|<font color="00c49f">8</font>|4|9|7|14|1|<font color="#D86DA9">16</font> |20|<font color="e89538">26</font>|<font color="4a94ff">18</font>|11|17
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

|<font color="00c49f">8</font>|4|9|7|14|1|<font color="#D86DA9">16</font> |20|26|<font color="e89538">18</font>|<font color="4a94ff">11</font>|17
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

|<font color="00c49f">11</font>|8|4|9|7|14|1|<font color="#D86DA9">16</font> |20|26|<font color="e89538">18</font>|<font color="4a94ff">17</font>
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

|<font color="00c49f">11</font>|8|4|9|7|14|1|<font color="#D86DA9">16</font> |20|26|18|<font color="e89538">17</font>
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

這樣就做完一次partition()了















