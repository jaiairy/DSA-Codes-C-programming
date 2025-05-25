#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

typedef struct Node {
    int sapid;
    struct Node* next;
} Node;

Node* hashtable[TABLE_SIZE];

int lastthreedigit(int sapid) {
    return sapid % 1000;
}

int singledigitsum(int n) {
    int sum;
    do {
        sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }
        n = sum;
    } while (sum >= 10);
    return sum;
}

int hashFunction(int sapid) {
    int last3 = lastthreedigit(sapid);
    int digitSum = singledigitsum(last3);
    return digitSum % TABLE_SIZE;
}

void insert(int sapid) {
    int index = hashFunction(sapid);

    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->sapid = sapid;
    newnode->next = NULL;

    if (hashtable[index] == NULL) {
        hashtable[index] = newnode;
    } else {
        Node* temp = hashtable[index];
        while (temp->next != NULL) {
            if (temp->sapid == sapid) {
                printf("SAP ID %d already exists.\n", sapid);
                free(newnode);
                return;
            }
            temp = temp->next;
        }
        if (temp->sapid == sapid) {
            printf("SAP ID %d already exists.\n", sapid);
            free(newnode);
            return;
        }
        temp->next = newnode;
        printf("Collision handled using separate chaining at index %d.\n", index);
    }

    printf("Inserted SAP ID %d in family %d\n", sapid, index);
}

void search(int sapid) {
    int index = hashFunction(sapid);
    Node* temp = hashtable[index];
    while (temp != NULL) {
        if (temp->sapid == sapid) {
            printf("SAP ID %d found in family %d\n", sapid, index);
            return;
        }
        temp = temp->next;
    }
    printf("SAP ID %d not found\n", sapid);
}

void delete(int sapid) {
    int index = hashFunction(sapid);
    Node* temp = hashtable[index];
    Node* prev = NULL;

    while (temp != NULL) {
        if (temp->sapid == sapid) {
            if (prev == NULL) {
                hashtable[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("SAP ID %d deleted from family %d\n", sapid, index);
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("SAP ID %d not found for deletion\n", sapid);
}

void display() {
    printf("\nHash Table (Separate Chaining):\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Family %d: ", i);
        Node* temp = hashtable[i];
        if (temp == NULL) {
            printf("EMPTY");
        }
        while (temp != NULL) {
            printf("%d -> ", temp->sapid);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int choice, sapid;

    for (int i = 0; i < TABLE_SIZE; i++) {
        hashtable[i] = NULL;
    }

    do {
        printf("\n   MENU   \n");
        printf("1 to Insert\n");
        printf("2 to Delete\n");
        printf("3 to Search\n");
        printf("4 to Display\n");
        printf("5 to Exit\n");
        printf("Enter your choice:");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter SAP ID to insert: ");
            scanf("%d", &sapid);
            insert(sapid);
        } else if (choice == 2) {
            printf("Enter SAP ID to delete: ");
            scanf("%d", &sapid);
            delete(sapid);
        } else if (choice == 3) {
            printf("Enter SAP ID to search: ");
            scanf("%d", &sapid);
            search(sapid);
        } else if (choice == 4) {
            display();
        } else if (choice == 5) {
            printf("Exiting\n");
        } else {
            printf("Invalid choice\n");
        }

    } while (choice != 5);

    return 0;
}
