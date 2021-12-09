#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define STACKSIZE 200005

typedef struct stack{
    int top;
    int items[STACKSIZE];
}Stack;

void push(Stack *store, int x){
    if(store->top == STACKSIZE-1){
        getchar();
        exit(0);
    }
    else{
        store->top += 1;
        int top = store->top;
        store->items[top] = x;
    }
}

bool isEmpty(Stack *store){
    return (store->top == -1)? true:false;
}

int pop(Stack *store){
    int top = store->top--;
    return store->items[top];
}

int *record_shorty(int arr[], int n){
    int *result = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; ++i){
        result[i] = 0;
    }
    Stack store;
    store.top = -1;
    int pop_element;
    push(&store, n-1);
    for(int i = n-2; i >= 0; --i){
        
        if(!isEmpty(&store)){
            //if the stack is not empty pop the target out
            pop_element = pop(&store);

            //if the pop_element is bigger than the compare
            // then the shorty of the pop_element is compare
            while(arr[pop_element] > arr[i]){
                result[pop_element] = i+1;
                //printf("ans[%d] = %d compare = %d\n",pop_element, arr[pop_element], i);
                if(isEmpty(&store)) break;
                pop_element = pop(&store);
            }

            //if pop_element is smaller than the compare
            //push the pop_element back
            if(arr[pop_element] < arr[i]) push(&store, pop_element);

        }
        push(&store, i);
    }

    return result;
}

int main(){
    int n;
    int arr[200005]={0};
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        scanf("%d", &arr[i]);
    }
    int *ans = record_shorty(arr, n);
    for(int i = 0; i < n; ++i){
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}

