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
    *head_ref = head;
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

## $Hash$ $Table$ (雜湊表)
雜湊表是一種根據鍵直接去查找記憶體位址的一種資料結構。透過一種夠隨機、每次input進去都得到同一個鍵值，的雜湊函數(沒有絕對是怎麼樣的行式)，讓人可以將搜尋的時間複雜度從$O(n)$縮減到$O(1)$。

先建一個結構，裡頭可以包含很多個資料 (今天舉例先有兩個：名字和年齡)
```c=
#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct{
    char name[MAX_NAME];
    int age;
}person;
```
當我們要把每一筆資料都產生一個隨機的鍵值，有三個要點：
第一，要確保同一個input永遠都是產生同一個output，第二，hash function應該要很快(不然就失去我們用hash table的本意了)，第三，產生的鍵值應該要非常隨機(不然即使之後解決collision，還是會有很多記憶體空間是被閒置的)

下面是一個hash function，hash function有很多種寫法，追求著上面的三個要點，這邊只是其中一個簡單示範。
```c=
//to get a random number from the name
//has to be always the same output with the same input
unsigned int hash(char *name){
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0;
    for(int i = 0; i < length; ++i){
        hash_value += name[i];
        hash_value =( hash_value * name[i]) % TABLE_SIZE;
    }
    return hash_value;
}
```

建一個指標陣列來存放建好的person資料。值得提的是，為甚麼是指標陣列呢？

因為我們不確定我們所建立的struct person當中會存放多少資料，如果資料很多，這個陣列所需要的空間將會變得很巨大，但如果只存放其person的指標，將能夠避免這個問題。

另外，利用指標我們就可以很容易的判斷陣列中某處是否為空的(NULL)
```c=
//reason of creating the array in pointer type
//no need the space for the struct
//easy to tell when the spot of the table is empty (NULL)
person * hash_table[TABLE_SIZE];
```
其他部分就是讓這個hash table be usable
```c=
//make sure the table is empty
void init_hash_table(){
    for(int i = 0; i < TABLE_SIZE; ++i){
        hash_table[i] = NULL;
    }
}

void print_table(){
    printf("Start!!\n");
    for(int i = 0; i < TABLE_SIZE; ++i){
        if(hash_table[i] == NULL) printf("\t%i\t---\n", i);
        else printf("\t%i\t%s\n", i, hash_table[i]->name);   
    }
    printf("End\n");
}

bool hash_table_insert(person *p){
    if(p == NULL) return false;
    int index = hash(p->name);

    if(hash_table[index] != NULL){
        //collision
        return false;
    }
    hash_table[index] = p;
    return true;
}

void hash_table_deletion(char *name){
    int index = hash(name);
    if(hash_table[index] != NULL && 
    strncmp(hash_table[index]->name, name, MAX_NAME) == 0){
        hash_table[index] = NULL;
    }
}



person *hash_table_lookup(char *name){
    if(name == NULL) return NULL;
    int index = hash(name);
    if(hash_table[index] != NULL && strncmp(hash_table[index]->name, name, MAX_NAME) == 0){
        return hash_table[index];
    }
}

int main(){
    init_hash_table();
    print_table();

    person Stefano = {.name = "Stefano", .age = 4};
    person Georgio = {.name = "Georgio", .age = 2};
    person Ida = {.name = "Ida", .age = 1};
    person Leo = {.name = "Leo", .age = 1};
    person Harry = {.name = "Harry", .age = 20};
    person Kitty = {.name = "Kitty", .age = 19};
    person Teresa = {.name = "Teresa", .age = 19};
    person Sanny = {.name = "Leo", .age = 19};
    person Jenny = {.name = "Leo", .age = 13};
    person Athina = {.name = "Leo", .age = 3};

    hash_table_insert(&Stefano);
    hash_table_insert(&Georgio);
    hash_table_insert(&Ida);
    hash_table_insert(&Leo);
    hash_table_insert(&Harry);
    hash_table_insert(&Kitty);
    hash_table_insert(&Teresa);
    hash_table_insert(&Sanny);
    hash_table_insert(&Jenny);
    hash_table_insert(&Athina);


    print_table();
    
    
    hash_table_deletion("Stefano");
    person *tmp = hash_table_lookup("Stefano");
    if(tmp == NULL){
        printf("Stefano IS NOT FOUND!!\n");
    }
    else printf("Found : %s\n", tmp->name);

    person *temp = hash_table_lookup("Harry");
    if(temp == NULL){
        printf("Harry IS NOT FOUND!!\n");
    }
    else printf("Found : %s\n", temp->name);

    return 0;
}
```
```c=
/*OUTPUT*/
Start!!
        0       ---
        1       ---
        2       ---
        3       ---
        4       ---
        5       ---
        6       ---
        7       ---
        8       ---
        9       ---
End
Start!!
        0       ---
        1       Stefano
        2       ---
        3       Harry
        4       ---
        5       ---
        6       ---
        7       ---
        8       Leo
        9       Ida
End
Stefano IS NOT FOUND!!
Found : Harry
```
從OUTPUT可以看到，明明insert了10個人，卻只有4個人真正進到表裡面。要處理collision的問題，有很多種方法：一種是$Linear$ $Probing$，還有一種是$External$ $Chain$
>其實還有quadratic probing和double hashing，之後再補

### $Linear$ $Probing$ (線性探測)
簡單來說，就是當hash的位置已經有存放東西，就把index放進for迴圈找接續的位置是否為空。為了不要浪費hash之前的位子，我們會讓try 變數後面加一個 %TABLE_SIZE，就能繞回表的前面去查找。
```c=
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#define MAX_NAME 256
#define TABLE_SIZE 10
#define DELETED_NODE (person*)(0xFFFFFFFFFFFUL)


bool hash_table_insert(person *p){
    if(p == NULL) return false;
    int index = hash(p->name);
    //add a loop to find if there is a space for the person
    for(int i = 0; i < TABLE_SIZE; ++i){
        int try = (i + index) % TABLE_SIZE;
        if(hash_table[try] == NULL){
            hash_table[try] = p;
            return true;
        }
    }
    return false;
}

void hash_table_deletion(char *name){
    int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; ++i){
        int try = (i + index) % TABLE_SIZE;
        if(hash_table[try]==NULL)
            return;
        if(hash_table[try] == DELETED_NODE)
            continue;
        if(strncmp(hash_table[try]->name, name, MAX_NAME) == 0){
            hash_table[try] = DELETED_NODE;
            return;
        }   
    }       
}

person *hash_table_lookup(char *name){
    if(name == NULL) return NULL;
    int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; ++i){
        int try = i + index;
        if(hash_table[try] == NULL)
            return NULL;//the person is not here
        if(hash_table[try] == DELETED_NODE)
            continue;
        if(strncmp(hash_table[try]->name, name,MAX_NAME) == 0)
            return hash_table[try];
    }
    return NULL;
}

int main(){
    init_hash_table();
    print_table();

    person Stefano = {.name = "Stefano", .age = 4};
    person Georgio = {.name = "Georgio", .age = 2};
    person Ida = {.name = "Ida", .age = 1};
    person Leo = {.name = "Leo", .age = 1};
    person Harry = {.name = "Harry", .age = 20};
    person Kitty = {.name = "Kitty", .age = 19};
    person Teresa = {.name = "Teresa", .age = 19};
    person Sanny = {.name = "Sanny", .age = 19};
    person Jenny = {.name = "Jenny", .age = 13};
    person Athina = {.name = "Athina", .age = 3};

    hash_table_insert(&Stefano);
    hash_table_insert(&Georgio);
    hash_table_insert(&Ida);
    hash_table_insert(&Leo);
    hash_table_insert(&Harry);
    hash_table_insert(&Kitty);
    hash_table_insert(&Teresa);
    hash_table_insert(&Sanny);
    hash_table_insert(&Jenny);
    hash_table_insert(&Athina);

    print_table();

    hash_table_deletion("Kitty");
    hash_table_deletion("Sanny");

    person *tmp = hash_table_lookup("Stefano");
    if(tmp == NULL)
        printf("Stefano IS NOT FOUND!!\n");
    else
        printf("Found : %s\n", tmp->name);

    person *temp = hash_table_lookup("Harry");
    if(temp == NULL)
        printf("Harry IS NOT FOUND!!\n");
    else
        printf("Found : %s\n", temp->name);

    print_table();
    return 0;
}

```
```c=
Start!!
        0       ---
        1       ---
        2       ---
        3       ---
        4       ---
        5       ---
        6       ---
        7       ---
        8       ---
        9       ---
End
Start!!
        0       Teresa
        1       Stefano
        2       Georgio
        3       Harry
        4       Kitty
        5       Sanny
        6       Jenny
        7       Athina
        8       Leo
        9       Ida
End
Found : Stefano
Found : Harry
Start!!
        0       Teresa
        1       Stefano
        2       Georgio
        3       Harry
        4       ----<deleted>
        5       ----<deleted>
        6       Jenny
        7       Athina
        8       Leo
        9       Ida
End

```
值得一提的是，hash table的最終目的是為了讓速度變快。但linear probing會讓整個速度變慢。

所以在deletion之後，如果要判斷某人是否還在表中，當遇到DELETED_NODE(自己額外設立的，絕對不會存在的位址)時，表示這個位子可能是曾經放過別人然後被刪掉(可能某人在其他位子)，但當遇到NULL時，就表示某人絕對不在這個表中。
```c=
        target: d
        0       a
        1       b
        2       ----DELETED_NODE(used to put c)
        3       d
        4       NULL
       
```
但是當deletion做太多次之後，DELETED_NODE的功能也會越來越沒辦法加快速度。最後hash table會淪為$O(n)$的奇怪狀態。

但是透過linked list 來建立external chain就能夠在同一個位子放入不只一個東西(但應該算是以空間換取時間啦)

### $External$ $Chain$

```c=
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
//quadratic probing
//double hashing

#define MAX_NAME 256
#define TABLE_SIZE 10
#define DELETED_NODE (person*)(0xFFFFFFFFFFFUL)

typedef struct{
    char name[MAX_NAME];
    int age;
}person;

//reason of creating the array in pointer type
//no need the space for the struct
//easy to tell when the spot of the table is empty (NULL)
person * hash_table[TABLE_SIZE];

//to get a random number from the name
//has to be always the same output with the same input
unsigned int hash(char *name){
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0;
    for(int i = 0; i < length; ++i){
        hash_value += name[i];
        hash_value =(hash_value * name[i]) % TABLE_SIZE;
    }
    return hash_value;
}

//make sure the table is empty
void init_hash_table(){
    for(int i = 0; i < TABLE_SIZE; ++i)
        hash_table[i] = NULL;
}

void print_table(){
    printf("Start!!\n");
    for(int i = 0; i < TABLE_SIZE; ++i){
        if(hash_table[i] == NULL)
            printf("\t%i\t---\n", i);
        else if(hash_table[i] == DELETED_NODE)
            printf("\t%i\t----<deleted> \n", i);
        else
            printf("\t%i\t%s\n", i, hash_table[i]->name);
    }
    printf("End\n");
}

bool hash_table_insert(person *p){
    if(p == NULL) return false;
    int index = hash(p->name);
    //add a loop to find if there is a space for the person
    for(int i = 0; i < TABLE_SIZE; ++i){
        int try = (i + index) % TABLE_SIZE;
        if(hash_table[try] == NULL){
            hash_table[try] = p;
            return true;
        }
    }
    return false;
}

void hash_table_deletion(char *name){
    int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; ++i){
        int try = (i + index) % TABLE_SIZE;
        if(hash_table[try]==NULL)
            return;
        if(hash_table[try] == DELETED_NODE)
            continue;
        if(strncmp(hash_table[try]->name, name, MAX_NAME) == 0){
            hash_table[try] = DELETED_NODE;
            return;
        }   
    }       
}

person *hash_table_lookup(char *name){
    if(name == NULL) return NULL;
    int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; ++i){
        int try = i + index;
        if(hash_table[try] == NULL)
            return NULL;//the person is not here
        if(hash_table[try] == DELETED_NODE)
            continue;
        if(strncmp(hash_table[try]->name, name,MAX_NAME) == 0)
            return hash_table[try];
    }
    return NULL;
}

int main(){
    init_hash_table();
    print_table();

    person Stefano = {.name = "Stefano", .age = 4};
    person Georgio = {.name = "Georgio", .age = 2};
    person Ida = {.name = "Ida", .age = 1};
    person Leo = {.name = "Leo", .age = 1};
    person Harry = {.name = "Harry", .age = 20};
    person Kitty = {.name = "Kitty", .age = 19};
    person Teresa = {.name = "Teresa", .age = 19};
    person Sanny = {.name = "Sanny", .age = 19};
    person Jenny = {.name = "Jenny", .age = 13};
    person Athina = {.name = "Athina", .age = 3};

    hash_table_insert(&Stefano);
    hash_table_insert(&Georgio);
    hash_table_insert(&Ida);
    hash_table_insert(&Leo);
    hash_table_insert(&Harry);
    hash_table_insert(&Kitty);
    hash_table_insert(&Teresa);
    hash_table_insert(&Sanny);
    hash_table_insert(&Jenny);
    hash_table_insert(&Athina);

    print_table();

    hash_table_deletion("Kitty");
    hash_table_deletion("Sanny");

    person *tmp = hash_table_lookup("Stefano");
    if(tmp == NULL)
        printf("Stefano IS NOT FOUND!!\n");
    else
        printf("Found : %s\n", tmp->name);

    person *temp = hash_table_lookup("Harry");
    if(temp == NULL)
        printf("Harry IS NOT FOUND!!\n");
    else
        printf("Found : %s\n", temp->name);

    print_table();
    return 0;
}

```









