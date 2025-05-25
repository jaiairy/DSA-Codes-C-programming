#include<stdio.h>
#define size 5

int queue[size],front=-1,rear=-1;

int isfull(){
    return (rear == size - 1);
}

int isempty(){
    return (front == rear);
}

void enqueue(){
    if(isfull()){
        printf("Overflow\n");
        return;
    }
    int data;
    printf("Enter the data:");
    scanf("%d", &data);
    rear = rear + 1;
    queue[rear] = data;
}

void dequeue(){
    if(isempty()){
        printf("Underflow\n");
        return;
    }
    printf("%d is removed from the Stack\n", queue[rear]);
    rear--;
}

void traverse(){
    if(isempty()){
        printf("Stack is empty\n");
        return;
    }
    for(int i = front + 1; i <= rear; i++){
        printf(" %d ", queue[i]);
    }
    printf("<-Top\n");
}
void peek(){
    if(isempty()){
        printf("Stack is empty\n");
        return;
    }
    else{
        printf("%d is the top element\n",rear+1);
    }
}

int main(){
    int choice;
    while(1){
        printf("\n");
        printf("Enter 1 for Push\n");
        printf("Enter 2 for Pop\n");
        printf("Enter 3 for Traversal\n");
        printf("Enter 4 to Peek\n");
        printf("Enter 5 for Exit\n");
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
            peek();
        }

        if(choice == 5){
            printf("Exiting the program\n");
            break;
        }
    }
    
    return 0;
}
