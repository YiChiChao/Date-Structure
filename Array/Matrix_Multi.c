#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101

typedef struct {
    int col;
    int row;
    int value;
} term;

typedef struct{
    term a[MAX_TERMS];
} matrix;
matrix *matrix_create(int max_row, int max_column){
    matrix *ans = malloc(sizeof(matrix));
    int count = 0;
    ans->a[0].row = max_row;
    ans->a[0].col = max_column;
    for(int i = 0; i < max_row; ++i){
        for(int j = 0; j < max_column; ++j){
            int tmp;
            scanf("%d", &tmp);
            if(!tmp)continue;
            ++count;
            ans->a[count].value = tmp;
            ans->a[count].row = i;
            ans->a[count].col = j;
        }
    }
    ans->a[0].value = count;
    return ans;
}
void print_sparse(matrix *input){
    int index = input->a[0].value;
    printf("row\tcolumn\tvalue\n");
    for(int i = 0; i <= index; ++i){
        printf("%d\t%d\t%d\n", input->a[i].row, input->a[i].col, input->a[i].value);
    }
}
matrix *fast_transpose(matrix *M){
    matrix *ans = malloc(sizeof(matrix));
    int column = M->a[0].col;
    int index = M->a[0].value;
    ans->a[0].row = column;
    ans->a[0].col = M->a[0].row;
    ans->a[0].value = index;
    int* row_size = malloc(column * sizeof(int));
    int* row_start = malloc(column * sizeof(int));
    row_start[0] = 0;
    for(int i = 0; i < column; ++i){
        row_size[i] = 0;
    }
    for(int i = 1; i <= index; ++i){
        ++row_size[M->a[i].col];
    }
    for(int i = 1; i< column; ++i){
        row_start[i] = row_size[i-1] + row_start[i-1];
    }

    /*printf("row_size\trow_start\n");
    for(int i = 0; i < column; ++i){
        printf("%d\t%d\n", row_size[i], row_start[i]);
    }*/
    printf("row\tcolumn\tvalue\n");
    
    for(int i = 1; i <= index; ++i){
        int j = ++row_start[M->a[i].col]; 
        ans->a[j].row = M->a[i].col;
        ans->a[j].col = M->a[i].row;
        ans->a[j].value = M->a[i].value;
        //printf("%d\t%d\t%d\n", ans->a[i].row, ans->a[i].col, ans->a[i].value);
        
    }
    return ans;
}
matrix *matrix_mult(matrix *a, matrix *b){
    matrix *ans = malloc(sizeof(matrix));
    int a_row = a->a[1];
    int a_col = 0;
    int b_row = 0;
    int b_col = 0;
    for (int i = 1; i <= a->a[0].value;){
        int sum = 0;
        for(int j = 1; j <= b->a[0].value;){
            if(a->a[i].row > b->a[j].row)++j;
            if(a->a[i].row < b->a[j].row)++i;
            if(a->a[i].row == b->a[j].row){
                sum += a->a[i].value * b->a[j].value;
            }
        }           
    }
    }




    return ans;
}
void storesum(term d[], int *totald, int row, int column, int *sum){

}

int main(){
    matrix *input_A = matrix_create(6, 6);
    matrix *input_B = matrix_create(6, 5);
    print_sparse(input_A);
    matrix *trans = fast_transpose(input_B);
    //printf("finish\n");
    print_sparse(trans);
    return 0;
}
