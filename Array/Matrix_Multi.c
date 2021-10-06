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
    //store the total column and row and the number of nonzero elements
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
    int value = input->a[0].value;
    printf("row\tcolumn\tvalue\n");
    for(int i = 0; i <= value; ++i){
        printf("%d\t%d\t%d\n", input->a[i].row, input->a[i].col, input->a[i].value);
    }
}
matrix *fast_transpose(matrix *M){
    matrix *ans = malloc(sizeof(matrix));

    int column = M->a[0].col;
    int row = M->a[0].row;
    int value = M->a[0].value;

    int* row_size = malloc(column * sizeof(int));
    int* row_start = malloc(column * sizeof(int));
    //row start from 1 since index 0 store the information of the matrix
    row_start[0] = 1;
    //init the array
    for(int i = 0; i < column; ++i){
        row_size[i] = 0;
    }
    //th count each row index
    for(int i = 0; i <= value; ++i){
        ++row_size[M->a[i].col];
    }
    //add the former rowsize and row start equal to where the next index start
    for(int i = 1; i< column; ++i){
        row_start[i] = row_size[i-1] + row_start[i-1];
    }

    for(int i = 0; i <= value; ++i){
        //add the row start to the next space
        int j = row_start[M->a[i].col]++; 
        ans->a[j].row = M->a[i].col;
        ans->a[j].col = M->a[i].row;
        ans->a[j].value = M->a[i].value;
    }
    return ans;
}

void storesum(matrix **d, int *totald, int row, int column, int *sum){
    if(*sum != 0){
        (*d)->a[++*totald].row = row;
        (*d)->a[*totald].col = column;
        (*d)->a[*totald].value = *sum;
        *sum = 0;
    }
}

matrix *matrix_mult(matrix *a, matrix *b){
    matrix *new_b = fast_transpose(b);
    matrix *ans = malloc(sizeof(matrix));

    int i, j, totalans = 0/*to count the ans's nonzero ele,ents*/;
    int column, row = a->a[1].row;
    //record where the A row start due to the multi method A has to times all the rows of B before going to the next row
    int row_begin = 1;
    int sum = 0;
    for(i = 1; i <= a->a[0].value; ){
        sum = 0;
        column = new_b->a[1].row;
        for(j = 1; j <= (new_b->a[0].value)+1;){
            //when the a row has gone to the end
            if(a->a[i].row != row){
                storesum(&ans,&totalans, row, column, &sum);
                //back to the beginning of the row
                i = row_begin;
                //let the b row get to the end
                for(; new_b->a[j].row == column; ++j);
                //record the row of b since it jump to the next row
                column = new_b->a[j].row;
            }
            //when the b row has gone to the end
            else if(new_b->a[j].row != column){
                storesum(&ans, &totalans, row, column, &sum);
                i = row_begin;
                //since the b row is already at the end(the position is at the beginning of the next row)
                //just record it
                column = new_b->a[j].row;
            }
            else{
                if(a->a[i].col > new_b->a[j].col){
                    ++j;
                }
                else if(a->a[i].col < new_b->a[j].col){
                    ++i;
                }
                else{
                    sum += a->a[i].value * new_b->a[j].value;
                    ++i;
                    ++j;
                }
            }
        }
        //when b rows has all been calculated
        //let a run to the end
        for(;a->a[i].row == row;++i);
        row_begin = i;
        row = a->a[i].row;
    }
    ans->a[0].row = a->a[0].row;
    ans->a[0].col = new_b->a[0].row;
    ans->a[0].value = totalans;
    return ans;
}



int main(){
    matrix *input_A = matrix_create(2, 2);
    matrix *input_B = matrix_create(2, 2);
    print_sparse(input_A);
    print_sparse(input_B);
    matrix *trans = fast_transpose(input_B);
    //printf("finish\n");
    print_sparse(trans);
    matrix *multi = matrix_mult(input_A, input_B);
    //print_sparse(multi);
    return 0;
}
