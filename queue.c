#include<stdio.h>
#define size 5

int arr[size],front=-1,rear=-1;

int isfull(){
    return (rear == size - 1);
}

int isempty(){
    return (front == rear);
}

void enqueue(){
    if(isfull()){
        printf("Queue is full\n");
        return;
    }
    int data;
    printf("Enter the data:");
    scanf("%d", &data);
    rear = rear + 1;
    arr[rear] = data;
}

void dequeue(){
    if(isempty()){
        printf("Queue is empty\n");
        return;
    }
    front = front + 1;
    printf("%d is removed from the queue\n", arr[front]);
}

void traverse(){
    if(isempty()){
        printf("Queue is empty\n");
        return;
    }
    printf("Front->");
    for(int i = front + 1; i <= rear; i++){
        printf(" %d ", arr[i]);
    }
    printf("<-Rear\n");
}

int main(){
    int choice;
    while(1){
        printf("Enter 1 for Insert\n");
        printf("Enter 2 for Delete\n");
        printf("Enter 3 for Traversal\n");
        printf("Enter 4 for Exit\n");
        printf("Enter your choice:");
        scanf("%d", &choice);

        if(choice == 1){
            enqueue();
        }
        
        if(choice == 2){
            dequeue();
        }
        
        if(choice == 3){
            traverse();
        }
        
        if(choice == 4){
            printf("Exiting the program\n");
            break;
        }
    }
    
    return 0;
}
