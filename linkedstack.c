#include <stdio.h>
#include <stdlib.h>

struct node {
    int info;
    struct node* next;
};

struct node* push(struct node* top, int data) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    if (newnode == NULL) {
        printf("Memory unavailable\n");
        return top;
    }

    newnode->info = data;
    newnode->next = top;
    return newnode;  
}

struct node* pop(struct node* top){
    if (top == NULL) {
        printf("Underflow\n");
        return NULL;
    }

    struct node* temp = top;
    printf("Popped element: %d\n", top->info);
    top = top->next;
    free(temp);
    return top;
}

void peek(struct node* top) {
    if (top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    printf("Top element: %d\n", top->info);
}

void display(struct node* top) {
    if (top == NULL) {
        printf("Stack is empty\n");
        return;
    }

    struct node* temp = top;
    printf("Stack elements:\n");
    while (temp != NULL) {
        printf("%d  ", temp->info);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    struct node* top = NULL;  
    int value, choice;

    while (1) {
        printf("Enter 1 to push\n");
        printf("Enter 2 to pop\n");
        printf("Enter 3 to peek\n");
        printf("Enter 4 to display\n");
        printf("Enter 5 to exit the program\n");
        printf("Enter your choice:");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter value to push: ");
            scanf("%d", &value);
            top = push(top, value);  
        }
        else if (choice == 2) {
            top = pop(top);
        }
        else if (choice == 3) {
            peek(top);
        }
        else if (choice == 4) {
            display(top);
        }
        else if (choice == 5) {
            printf("Exiting program\n");
            while (top != NULL) {
                struct node* temp = top;
                top = top->next;
                free(temp);
                break;
            }
        }
        else {
            printf("Invalid choice, try again\n");
        }
    }
    return 0;
}
