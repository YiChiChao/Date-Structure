#include<stdio.h>
#include<stdlib.h>

typedef struct stack{
    int top;
    unsigned capacity;
    char *array;
} Stack;

typedef struct {
    char str;
    long long int row;
    long long int column;
}Node;

typedef struct{
    Node string[2001];
}Mat;

//Stack Operations
Stack* createStack(unsigned capacity){
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    if(!stack) return NULL;
    //init stack
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (int*) malloc(capacity * sizeof(int));
    return stack;
}

int isEmpty(Stack *stack){
    return stack->top == -1;
}

char peek(Stack* stack){
    return stack->array[stack->top];
}

char pop(Stack* stack){
    if(!isEmpty(stack)){
        return stack->array[stack->top--];
    }
    return '$';
}

void push(Stack *stack, char operator){
    stack->array[++stack->top] = operator;
}

int isOperand(char input){
    return (input >= 'A' && input <= 'Z'); 
}



int function(char* exp, Stack *stack, Mat *matrix){
    Node op1;
    Node op2;
    int count = 0;
    for(int i = 0; exp[i]; ++i){
        if(isOperand(exp[i])){
            push(stack, exp[i]);
        }
        else if (exp[i] == '('){
            push(stack, exp[i]);
        }
        else if(exp[i] == ')'){
            op2 = matrix->string[pop(stack)];
            op1 = matrix->string[pop(stack)];
            char clean = pop(stack);
            if(op1.column != op2.row)return -1;
            else {
                count += op1.row * op1.column * op2.row;
                Node newnode;
                newnode.str = i;
                newnode.row = op1.row;
                newnode.column = op2.column;
                matrix->string[i] = newnode;
                push(stack, i);
            }
        }
    }
    return count;
}

int main(){
    Mat *matrix = (Mat*)malloc(sizeof(Mat));
    Stack *stack = createStack(2000);
    char exp[2001]={0};
    int t, d;
    scanf("%d", &t);
    for(int i = 0; i < t; ++i){
        int k;
        scanf("%c", &k);
        scanf("%lld %lld", &(matrix->string[k].row), &(matrix->string[k].column));
    }
    scanf("%d", &d);
    for(int i = 0; i < d; ++i){
        fgets(exp, sizeof(exp), stdin);
        long long int ans = function(exp, stack, matrix);
        if(ans == -1)printf("error\n");
        else printf("%lld\n", ans);
    }
    return 0;
}