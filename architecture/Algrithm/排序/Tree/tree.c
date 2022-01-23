#include <stdio.h>
#include <stdlib.h>

typedef struct node {
        int data;
        struct node *left;
        struct node *right;
} NODE;

//先序遍历
void preorder(NODE *node) {
        if (node != NULL) {
                printf("%d\n", node->data);
                preorder(node->left);
                preorder(node->right);
        }
}

//中序遍历
void inorder(NODE *node) {
        if (node != NULL) {
                inorder(node->left);
                printf("%d\n", node->data);
                inorder(node->right);
        }
}

//后序遍历
void postorder(NODE *node) {
        if (node != NULL) {
                postorder(node->left);
                postorder(node->right);
                printf("%d\n", node->data);
        }
}

//二叉树
int main(void) {
        NODE    n1;
        NODE    n2;
        NODE    n3;
        NODE    n4;
        
        n1.data = 5;
        n2.data = 6;
        n3.data = 7;
        n4.data = 8;
        
        n1.left  = &n2;
        n1.right = &n3;
        n2.left  = &n4;
        n2.right = NULL;
        n3.left  = &n4;
        n3.right = NULL;
        n4.left  = &n4;
        n4.right = NULL;
        
        preorder(&n1);
}

