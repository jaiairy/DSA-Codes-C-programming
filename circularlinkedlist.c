#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

struct node* insert_head(struct node* head, int value) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    if (newnode == NULL) {
        printf("Memory unvailable\n");
        return head;
    }
    newnode->data = value;

    if (head == NULL) {
        newnode->next = newnode;
        return newnode;
    }

    struct node* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }

    newnode->next = head;
    temp->next = newnode;
    return newnode;
}

struct node* insert_end(struct node* head, int value) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    if (newnode == NULL) {
        printf("Memory unavailable\n");
        return head;
    }
    newnode->data = value;

    if (head == NULL) {
        newnode->next = newnode;
        return newnode;
    }

    struct node* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }

    temp->next = newnode;
    newnode->next = head;
    return head;
}

struct node* delete_head(struct node* head) {
    if (head == NULL) {
        printf("Underflow\n");
        return NULL;
    }

    if (head->next == head) {  
        printf("Deleted element = %d\n", head->data);
        free(head);
        return NULL;
    }

    struct node* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }

    temp->next = head->next;
    printf("Deleted element = %d\n", head->data);
    struct node* newhead = head->next;
    free(head);

    return newhead;
}

struct node* delete_end(struct node* head) {
    if (head == NULL) {
        printf("Underflow\n");
        return NULL;
    }

    if (head->next == head) {  
        printf("Deleted element = %d\n", head->data);
        free(head);
        return NULL;
    }

    struct node* temp = head;
    while (temp->next->next != head) {  
        temp = temp->next;
    }

    printf("Deleted element = %d\n", temp->next->data);
    free(temp->next);
    temp->next = head;  
    return head;
}

void display(struct node* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct node* temp = head;
    while (temp != NULL && temp->next != head) {
        printf("%d -  ", temp->data);
        temp = temp->next;
    }
    if (temp != NULL)
        printf("%d\n", temp->data);
}

int main() {
    struct node* head = NULL;
    int choice, value;

    while (1) {
        printf("\nCircular Linked List Menu\n");
        printf("1. Insert at Head\n");
        printf("2. Insert at End\n");
        printf("3. Delete from Head\n");
        printf("4. Delete from End\n");
        printf("5. Display List\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter value to insert at head: ");
            scanf("%d", &value);
            head = insert_head(head, value);
        }
        else if (choice == 2) {
            printf("Enter value to insert at end: ");
            scanf("%d", &value);
            head = insert_end(head, value);
        }
        else if (choice == 3) {
            head = delete_head(head);
        }
        else if (choice == 4) {
            head = delete_end(head);
        }
        else if (choice == 5) {
            display(head);
        }
        else if (choice == 6) {
            printf("Exiting program\n");
            break;
        }
        else {
            printf("Invalid choice, please enter again\n");
        }
    }
    return 0;
}