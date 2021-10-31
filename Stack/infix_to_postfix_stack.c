#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//stack type
typedef struct stack{
    int top;
    unsigned capacity;
    int *array;
} Stack;

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

//check the given character is operand
int isOperand(char input){
    return (input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z'); 
}

//to know the priority of the operator
int Priority(char input){
    switch(input){
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
    }
    return -1;
}

//the main function
int infixTopostfix(char *exp){
    int i, k;

    //create a stack of capacity
    //equal to expression size
    Stack *stack = createStack(strlen(exp));
    if(!stack) {
        printf("create stack unsuccesfully\n");
        return -1;
    }

    for(i = 0, k = -1; exp[i]; ++i){
         //if the character is an operand 
        //directly output it
        if(isOperand(exp[i])){
            exp[++k] = exp[i];
        }

        //if the character is '('
        //push it to the stack
        else if (exp[i] == '('){
            push(stack, exp[i]);
        }

        //if the character is ')'
        //pop the stack til encounter '('
        else if(exp[i] == ')'){
            while(!isEmpty(stack) && peek(stack)!= '('){
                exp[++k] = pop(stack);
            }
            if(!isEmpty(stack) && peek(stack)!='('){
                printf("Invalid expression\n");
                return -1;
            }
            else pop(stack);//pop out the'('
        }
        //if the character is an operator
        else{
            while(!isEmpty(stack) && Priority(exp[i]) <= Priority(peek(stack))){
                exp[++k] = pop(stack);
            }
            push(stack, exp[i]);
        }
    }
    //finish all the exp with operand
    //pop all the operator from the stack
    while(!isEmpty(stack)){
        exp[++k] = pop(stack);
    }
    exp[++k] = '\0';
    printf("%s\n", exp);
    return 0;
}

int main(){
    char exp[] = "A+B*C/(E-F)";
    infixTopostfix(exp);
    printf("print\n");
    return 0;
}

