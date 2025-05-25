#include <stdio.h>
#include <stdlib.h>

struct node 
{
    int data;
    struct node *left;
    struct node *right;
};

struct node* createnode(int data) 
{
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->left = newnode->right = NULL;
    return newnode;
}

struct node* insert_bst(struct node* root, int data) 
{
    if (root == NULL)
    {
        return createnode(data);
    }
    if (data <= root->data)
    {
        root->left = insert_bst(root->left, data);
    }
    else
    {
        root->right = insert_bst(root->right, data);
    }
    return root;
}

void inorder_traverse(struct node* root) 
{
    if (root == NULL)
    {
        return;
    }
    inorder_traverse(root->left);
    printf("%d ", root->data);
    inorder_traverse(root->right);
}

int main() {
    struct node* root = NULL;
    int choice, data;
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert data\n");
        printf("2. Display inorder traversal\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter a number: ");
            scanf("%d", &data);
            root = insert_bst(root, data);
        } 
        else if (choice == 2) {
            printf("Inorder traversal: ");
            inorder_traverse(root);
            printf("\n");
        } 
        else if (choice == 3) {
            printf("Exiting program\n");
            return 0;
        } 
        else {
            printf("Invalid choice\n");
        }
    }
}
