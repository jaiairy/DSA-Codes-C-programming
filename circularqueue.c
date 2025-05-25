#include<stdio.h>
#define size 5

int arr[size], front = -1, rear = -1;

int isempty() {
    return (front == -1 && rear == -1);
}

int isfull() {
    return ((rear + 1) % size == front);
}

void enqueue() {
    if (isfull()) {
        printf("Queue is full\n");
        return;
    }
    int data;
    printf("Enter the data: ");
    scanf("%d", &data);
    
    if (isempty()) {
        front = rear = 0;
    } 
    else {
        rear = (rear + 1) % size;
    }
    arr[rear] = data;
}

void dequeue() {
    if (isempty()) {
        printf("Queue is empty\n");
        return;
    }
    printf("%d is removed from the queue\n", arr[front]);
    if (front == rear) {
        front = rear = -1;
    } 
    else {
        front = (front + 1) % size;
    }
}

void traverse() {
    if (isempty()) {
        printf("Queue is empty\n");
        return;
    }
    printf("Front -> ");
    int i = front;
    while (1) {
        printf("%d ", arr[i]);
        if (i == rear) {
            break;
        }
        i = (i + 1) % size;
    }
    printf("<- Rear\n");
}

int main() {
    int choice;
    while (1) {
        printf("Enter 1 for Insert\n");
        printf("Enter 2 for Delete\n");
        printf("Enter 3 for Traversal\n");
        printf("Enter 4 for Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            enqueue();
        } 
        else if (choice == 2) {
            dequeue();
        } 
        else if (choice == 3) {
            traverse();
        } 
        else if (choice == 4) {
            printf("Exiting the program\n");
            break;
        } 
        else {
            printf("Invalid choice\n");
        }
    }
    return 0;
}
