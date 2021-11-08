# CS Class (Data Structure)

## Stack
https://scanftree.com/Data_Structure/postfix-to-infix

## Prefix Infix Postfix Convert Rules
![image alt](https://i.imgur.com/8yCDHlW.jpg)

## Tree
### 通則
1. **Degree** (deg(A))：每一個Node的Subtree數量 
2. **Degree of a tree**：Tree當中最大的 degree 數
3. **Leaf Node**：degree 為 0 的Node
4. **Nonterminal**：the node with subtree
5. Tree中的edge數一定是(node數-1)
6. 每個Node只會有一個parent

![](https://i.imgur.com/F31ol16.png)
```
Ex: deg(A) = 3, deg(D) = 2, deg(J) = 0
```


7. **Level**：
    * Level(root) = 1
    * Level(node) = $l$ + 1 (where level of n's parent is $l$ )
8. **Height** or **Depth** of a tree：Max level of any node in the tree
![](https://i.imgur.com/4w2GZgP.png)
``` 
EX: 
Level(A) = 1, Level(G) = 3
Height of the tree = 4
```

:::info
**每個Node只會有一個Level**
[pf]: Level的數值來自於Node的Parent，由於每個Node只會有一個Parent，所以Level也會是唯一

:::

---


### **Binary Tree**

#### 定義：

由有限集合的節點所組成的結構。節點可以是Empty，或是由一個 $root$ 和兩個 $disjoint$ $binary$ $tree$ ( called left subtree and right subtree) 所組成



#### Node 數量最大值：
1. 第$i$層的Node數最大值為 $2^{(i-1)}$
2. 當 **Depth = k**, Tree的Node數最大值為 $2^k-1$



#### Property of Binary Tree

If $n_0$ = **number of leaf nodes** and $n_2$ = **number of degree-2 nodes**, then **$n_0 = n_2+1$**

- proof：
- $n = n_0 + n_1 +n_2$ ($n_1$ = **number of degree-1 nodes**)
- $n = B+1$ (B is the number of branches in the tree)
- $B = n_1 +2n_2$
- $n_0 + n_1 +n_2 = n_1 +2n_2+1$
- $n_0 = n_2+1$

---
### **Max(Min)Heap** 

#### 定義：一個 *Complete Binary Tree* 且所有Node的值都不小於(不大於)其ChildrenNode 的值。

#### Array Representation
>因為Heap是一棵*Complete Binary Tree*，所以適合用Array Representation 來執行


##### 規則
令$Node(i)$的位子為$i$ (陣列從$1$開始)
- $Parent(i) = Node(i/2)$ if $i \neq 1$.
> If $i = 1$, the node is the root and has no parent.
- $leftChild(i) = Node(2i)$
- $rightChild(i) = Node(2i+1)$

##### 舉例
![](https://i.imgur.com/AjOosWq.png)
```
Node(B) = Node(2)

Parent(B)= Node(2/2) = Node(1) = Node(A)

leftChild(B)= Node(2*2)= Node(4)= Node(D)

rightChild(B)= Node(2*2+1) = Node(5)= Node(E)
```
---
#### $Insertion$ (Max Heap)：
##### 規則：
1. 把 $newNode$ 掛在整個 Heap 的最後面。(維持 Complete Binary Tree)
2. 檢查 $newNode$ 是否大於其 $Parent$
3. 如果有，就將兩個 $Node$ 位置互換

##### 舉例：
```Insert 5```
1. 把 $Node(5)$ 掛在整個 Heap 的最後面。
![](https://i.imgur.com/JJp1mZG.png)

2. 檢查 $Node(5)$ 是否大於其 $Parent$ ( $Node(2)$ )
![](https://i.imgur.com/hYUPVu6.png)

3. $Node(5) > Node(2)$，將兩個 $Node$ 位置互換
![](https://i.imgur.com/drV7uw1.png)

4. 繼續往上檢查，發現已經符合Max Heap，完成。





##### 時間複雜度：
因為 $newNode$ 最多互換的次數是整個樹高，所以時間複雜度是$$O(logn)$$

---
#### $Deletion$ (Max Heap)：
##### 規則：
1. 把 $root$ 拔掉
2. 把最後的 $leafNode$ 拿去補 $root$的位置 (維持 Complete Binary Tree)
3. 將 $root$ 跟兩個 $Children$ 比較大小，如果比較小，就跟比較大的 $Child$ 互換位置

##### 舉例：
```Delete```

![](https://i.imgur.com/hENeAFj.png)
1. 把 $Root$ 移除。
![](https://i.imgur.com/KtC9aQW.png)


2. 把最後的 $leafNode$ ( $Node(8)$ ) 拿去補 $root$ 的位置 
![](https://i.imgur.com/U5CeWIX.png)


3. 將 $root$ 跟兩個 $Children$ 比較大小，如果比較小，就跟比較大的 $Child$ ( $Node(16)$ ) 互換位置
![](https://i.imgur.com/dQmLPaU.png)


4. 繼續往下檢查，直到發現已經符合Max Heap，完成。
![](https://i.imgur.com/cXzYunW.png)




##### 時間複雜度：
因為 $root$ 最多互換的次數是整個樹高，所以時間複雜度是$$O(logn)$$

---
### Binary Search Tree (BST)
#### 定義：一個$Binary$ $Tree$，且每一個 $Node$ 的 $Leftnode$ 都比他小，$Rightnode$ 都比他大。其 $Subtree$ 也都是 $BST$
---
#### $Deletion$
##### 規則：
1. 先找到指定的Node
2. Node會有三種情況：
    1. $LeafNode$：直接刪掉並設其為NULL，完成
    2. on-LeafNode$ 有一個 $ChildNode$：將其 $Parent$ 跟 $Child$ 連接，free 掉 ，完成
    3. non-LeafNode$ 有兩個 $ChildNode$：取左子樹最大或右子數最小的$nowNode$去取代指定的$Node$，並重複$deletion$處理$nowNode$的原位置。
##### 時間複雜度：
查找Node是 $O(h)$，互換兩次各是 $O(1)$。($h$是樹高)

Worst Case：當此樹是$skewed$ $tree$ ， $h = n$ ， $O(n)$

---




















