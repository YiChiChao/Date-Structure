#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_COUNT 10000001
#define ll long long int 
#define MIN -120000000001
#define MAX 120000000001
char s_exp[MAX_COUNT+1];
int arr_index = 0;

typedef struct node{
    ll weight;
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

void Preorder_traverse(Node *root){
    if(root == NULL)return;
    printf("%lld ", root->weight);
    if(root->left != NULL)Preorder_traverse(root->left);
    if(root->right != NULL)Preorder_traverse(root->right);
    return;
}

void Inorder_traverse(Node *root){
    if(root == NULL)return;
    if(root->left != NULL)Inorder_traverse(root->left);
    printf("%lld ", root->weight);
    if(root->right != NULL)Inorder_traverse(root->right);
    return;
}

void Postorder_traverse(Node *root){
    if(root == NULL)return;
    if(root->left != NULL)Postorder_traverse(root->left);
    if(root->right != NULL)Postorder_traverse(root->right);
    printf("%lld ", root->weight);
    return;
}

void Traversal(Node *root){
    Preorder_traverse(root);
    printf("\n");
    Inorder_traverse(root);
    printf("\n");
    Postorder_traverse(root);
    printf("\n");
    return;
}


ll WeightSum(Node *root){
    if(root == NULL)return 0;
    ll sum = 0;
    sum += root->weight;
    //collect the weight sum from the left subtree and right subtree and add it to the tree
    if(root->left != NULL)sum += WeightSum(root->left);
    if(root->right != NULL)sum += WeightSum(root->right);
    return sum;
}

ll MaximumPathSum(Node *root){
    //set the null return as a very small number 
    if(root == NULL)return MIN;
    ll count = 0;
    count += root->weight;
    ll left_num = MaximumPathSum(root->left);
    ll right_num = MaximumPathSum(root->right);
    if(left_num > right_num) {
        count += left_num;
    }
    else if(left_num == right_num){
        //if the child nodes are not null  but have the same value 
        if(right_num != MIN)count += left_num;
    }
    else count += right_num;
    return count;
}

ll BinaryTower(Node *root, ll *count){
    ll tmp = 0;
    if(root == NULL)return MAX;
    if(root->right == NULL && root->left == NULL)return 0;//represented as a leafnode
    ll right = BinaryTower(root->right, count);
    ll left = BinaryTower(root->left, count);
    if(right < left)tmp = (right+1) % 3;
    else if(right == left && right == MAX)tmp = 0;
    else tmp = (left+1) % 3;
    if (tmp == 1) (*count)++;
    return tmp;
}

void DeleteLeaf(Node **root){
    Node *nownode = *root;
    if(nownode == NULL)return;
    if(nownode->left == NULL && nownode->right == NULL){
        free(nownode);
        *root = NULL;
        return;
    }
    //if the node is not a leaf node
    //keep going down
    if(nownode->left != NULL) DeleteLeaf(&(nownode->left));
    if(nownode->right != NULL) DeleteLeaf(&(nownode->right));
    return;
} 

int Foldable(Node *leftpointer, Node *rightpointer){
    int ans = 0;
    //if there are no left and right node
    //it is foldable, then return 1
    if(leftpointer == NULL && rightpointer == NULL)return 0;
    //not foldable scenario return 1
    else if(leftpointer == NULL && rightpointer != NULL)return 1;
    else if(leftpointer != NULL && rightpointer == NULL)return 1;
    else{
        //if the subtree is unfoldable
        //if would return a nonzero number
        ans += Foldable(leftpointer->left, rightpointer->right);
        ans += Foldable(leftpointer->right, rightpointer->left);
    }
    return ans;
}

Node* Invert(Node *root){
    if(root == NULL)return NULL;
    //no need to invert
    if(root->left == NULL && root->right == NULL)return root;
    Node* left = Invert(root->left);
    Node* right = Invert(root->right);
    root->left = right;
    root->right = left;
    return root;
}

ll KingdomUnitedPath(Node *root, long long int *max){
    //the *max is to record the max path from the whole tree
    //the midpath is to record the number count if the left node and the right node and the root node has the same amount 
    long long int midpath = 0;
    long long int leftpath;
    long long int rightpath;
    if(root == NULL) return 0;
    leftpath = KingdomUnitedPath(root->left, max);
    rightpath = KingdomUnitedPath(root->right, max);

    if(root->left == NULL)leftpath = 0;
    else {
        if(root->weight == root->left->weight){
            //if the root weight is same as the root left node
            //the path should add one more path
            midpath += ++leftpath;
            //if the root weight is not same as the root left node
            //the path counting would stop and has to compare with the max counting path 
        }else{
            leftpath = 0;
        }
    }
    //same concept as the left node part
    if(root->right == NULL)rightpath = 0;
    else{
        if(root->weight == root->right->weight){
            midpath += ++rightpath;
        }else{
            rightpath = 0;
        }
    }
    if(midpath > *max) *max = midpath;
    //the return for the scenarion when the left and right and root nod are all the same
    //choose the longer path since we only count the path not the whole subtree
    return (leftpath > rightpath) ? leftpath : rightpath;
}

//it is the path not the total connected node

void freeTree(Node *root){
    if(root == NULL)return;
    if(root->left != NULL)freeTree(root->left);
    if(root->right != NULL)freeTree(root->right);
    free(root);
    return;
}



int main(){
    while(~scanf("%s", s_exp)){
        Node *root = buildTree(s_exp);
        ll ans;
        char buffer[20];
        while(~scanf("%s", buffer)){
            if(!strcmp(buffer, "Traverse")){
                Traversal(root);
            }else if(!strcmp(buffer, "WeightSum")){
                ans = WeightSum(root);
                printf("%lld\n", ans);
            }else if(!strcmp(buffer, "MaximumPathSum")){
                if((ans = MaximumPathSum(root)) == MIN)ans = 0;
                printf("%lld\n", ans);
            }else if(!strcmp(buffer, "BinaryTower")){
                ans = 0;
                if(BinaryTower(root, &ans) == 0)ans += 1;
                printf("%lld\n", ans);
            }else if(!strcmp(buffer, "DeleteLeaf")){
                DeleteLeaf(&root);
            }else if(!strcmp(buffer, "Foldable")){
                if(Foldable(root, root) != 0)printf("No\n");
                else printf("Yes\n");
            }else if(!strcmp(buffer, "Invert")){
                root = Invert(root);
            }else if(!strcmp(buffer, "KingdomUnitedPath")){
                ans = 0;
                KingdomUnitedPath(root, &ans);
                printf("%lld\n", ans);
            }else if(!strcmp(buffer, "End")){
                printf("\n");
                break;
            }
        }
        //freeTree(root);
        arr_index = 0;
    }
    return 0;
}