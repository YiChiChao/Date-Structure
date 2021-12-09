#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_COUNT 10000001
#define ll long long int
char s_exp[MAX_COUNT+1];
int arr_index = 0;

typedef struct node{
    int weight;
    struct node *left;
    struct node *right;
}Node;


Node *buildTree(char s_exp[]){
    Node *newnode;
    char num[8] = {0};
    if(s_exp[arr_index++] == '('){
        //if the node is not empty
        if(s_exp[arr_index] != ')'){
            int i = 0;
            while(s_exp[arr_index] != '('){
                num[i] = s_exp[arr_index];
                ++i;
                ++arr_index;
            }
            num[i] = '\0';
            newnode = (Node*) malloc(sizeof(Node));
            newnode->weight = atoi(num);
            newnode->left = buildTree(s_exp);
            newnode->right = buildTree(s_exp);
            //skip the right paranthesis for this node
            ++arr_index;
        }
        else {
            //skip the right paranthesis for this node
            ++arr_index;
            newnode = NULL;
        }
    }
    else newnode = NULL;
    return newnode;
}


ll fast_power(int a, int times){
    long long int ans = 1;
    while(times){
        if(times % 2 == 1) ans = (ans * a);
        a = a * a ;
        times = times/2;
    }
    //printf("%lld\n", ans);
    return ans;
}

ll Treeheight(Node *root){
    if(root == NULL)return 0;

    ll left_height;
    ll right_height;

    left_height = Treeheight(root->left);
    right_height = Treeheight(root->right);

    if(left_height > right_height)return left_height+1;
    else return right_height+1;
}

void nullleftCount(Node *root, int level, int *left, int *check){
    if(*check == 1)return;
    if(root == NULL){
        if(level != 1){
            *left += fast_power(2, level-1);
            return;
        }
        else {
            *left += 1;
            return;
        }
    }
    if(level == 1){
        *check = 1;
        return;
    }
    if(level > 1){
        nullleftCount(root->left, level-1, left, check);
        nullleftCount(root->right, level-1,left, check);
    }
    return;
}

void nullrightCount(Node *root, int level, int *right, int *check){
    if(*check == 1)return;
    if(root == NULL){
        if(level != 1){
            *right += fast_power(2, level-1);
            //printf("rightcheck=%d\n", *right);
            return;
        }
        else {
            *right += 1;
            //printf("rightcheck=%d\n", *right);
            return;
        }
    }
    if(level == 1){
        *check = 1;
        return;
    }
    if(level > 1){
        nullrightCount(root->right, level-1,right, check);
        nullrightCount(root->left, level-1, right, check);
    }
    return;
}

int main(){
    while(fgets(s_exp, MAX_COUNT, stdin)!= NULL && s_exp[0] == '('){
        //printf("%s\n", s_exp);
        printf("%s\n", s_exp);
        Node *root = buildTree(s_exp);
        ll ans;
        ll leaf = 0;
        ll max = 0;
        int right = 0;
        int left = 0;
        int check = 0;
        int height = Treeheight(root);
        for(int i = 1; i <= height; ++i){
            right = 0;
            left = 0;
            leaf = fast_power(2, i-1);
            //printf("leaf = %lld\n", leaf);
            if(leaf == 1)ans = 0;
            else{
                check = 0;
                nullrightCount(root, i, &right, &check);
                check = 0;
                nullleftCount(root, i, &left, &check);
                //printf("left = %d right = %d\n", left, right);
                ans = leaf-right-left;
                if(ans == 1)ans = 0;
            }
            if(max < ans)max = ans;
        }
        printf("%lld\n", max);
        arr_index = 0;
    }
    return 0;
}