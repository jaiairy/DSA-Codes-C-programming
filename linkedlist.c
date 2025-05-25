#include <stdio.h>
#include <stdlib.h>

struct node {
    int info;
    struct node* next;
};

struct node* head = NULL;

void createnode() {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    if (newnode == NULL) {
        printf("Memory unavailable\n");
        return;
    }
    printf("Enter the data to be added: ");
    scanf("%d", &newnode->info);
    newnode->next = NULL;
    head = newnode;
}

void printlist() {
    struct node* temp = head;
    if (temp == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->info);
        temp = temp->next;
    }
    printf("NULL\n");
}

void insert_begin(int data) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    if (newnode == NULL) {
        printf("Memory unavailable\n");
        return;
    }
    newnode->info = data;
    newnode->next = head;
    head = newnode;
}

void insert_back(int data) {
    struct node* newback = (struct node*)malloc(sizeof(struct node));
    if (newback == NULL) {
        printf("Memory unavailable\n");
        return;
    }
    newback->info = data;
    newback->next = NULL;

    if (head == NULL) {
        head = newback;
        return;
    }

    struct node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newback;
}

void insert_at_position(int data, int pos) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    if (newnode == NULL) {
        printf("Memory unavailable\n");
        return;
    }
    newnode->info = data;
    newnode->next = NULL;

    if (head == NULL) {
        printf("List is empty. Use option 1 to create a node first.\n");
        free(newnode);
        return;
    }

    struct node* temp = head;

    while (temp != NULL && temp->info != pos) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Position not found in the list.\n");
        free(newnode);
        return;
    }

    newnode->next = temp->next;
    temp->next = newnode;
    printf("Inserted %d after %d.\n", data, pos);
}

void delete_begin() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct node* temp = head;
    head = head->next;
    free(temp);
    printf("First node deleted.\n");
}

void delete_back() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    if (head->next == NULL) {
        free(head);
        head = NULL;
        printf("Last node deleted.\n");
        return;
    }

    struct node* temp = head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }

    free(temp->next);
    temp->next = NULL;
    printf("Last node deleted.\n");
}

void delete_at_position(int pos) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct node* temp = head;
    struct node* prev = NULL;

    if (head->info == pos) {
        head = head->next;
        free(temp);
        printf("Node with info %d deleted.\n", pos);
        return;
    }

    while (temp != NULL && temp->info != pos) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Info not found in the list\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Node with info %d deleted.\n", pos);
}

void find_middle() {
    if (head == NULL) {
        printf("List is empty\n");
    }

    else {
        int count = 0;
        struct node* temp = head;

        while (temp != NULL) {
            count++;
            temp = temp->next;
        }

        if(count % 2 == 0) {
            printf("There is no middle element present\n");
        }

        else {
            int mid = count / 2; 
            temp = head;

            for (int i = 0; i < mid; i++) {
                temp = temp->next;
        }
            printf("Middle element: %d\n", temp->info);
        }
    }
}

int main() {
    int choice, data, pos;

    while (1) {
        printf("\n  Linked List Menu  \n");
        printf("1 Create first node\n");
        printf("2 Insert at beginning\n");
        printf("3 Insert at end\n");
        printf("4 Insert at specific position\n");
        printf("5 Delete from beginning\n");
        printf("6 Delete from end\n");
        printf("7 Delete at specific position\n");
        printf("8 Print list\n");
        printf("9 Find middle element\n");
        printf("10 Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            createnode();
        } 
        else if (choice == 2) {
            printf("Enter data to insert at beginning: ");
            scanf("%d", &data);
            insert_begin(data);
        } 
        else if (choice == 3) {
            printf("Enter data to insert at end: ");
            scanf("%d", &data);
            insert_back(data);
        } 
        else if (choice == 4) {
            printf("Enter data to insert: ");
            scanf("%d", &data);
            printf("Enter the info you want to insert after: ");
            scanf("%d", &pos);
            insert_at_position(data, pos);
        } 
        else if (choice == 5) {
            delete_begin();
        } 
        else if (choice == 6) {
            delete_back();
        } 
        else if (choice == 7) {
            printf("Enter the info you want to delete: ");
            scanf("%d", &pos);
            delete_at_position(pos);
        } 
        else if (choice == 8) {
            printlist();
        } 
        else if (choice == 9) {
            find_middle();
        } 
        else if (choice == 10) {
            printf("Exiting program\n");
            break;
        } 
        else {
            printf("Invalid choice\n");
        }
    }
    return 0;
}
