#include<stdio.h>
#define size 10
int arr[size], top = -1;

void push(){
    int n;
    if (top == size - 1){
        printf("Stack Overflow\n");
    }
    else{
        printf("Enter an element: ");
        scanf("%d", &n);
        top++;
        arr[top] = n;
    }  
}

void pop(){ 
    int n;
    if (top == -1){
        printf("Stack Underflow\n");
    }
    else{
        n = arr[top];
        top--;
        printf("Popped element is %d\n", n);
    }
}

void display(){
    int i;
    if (top == -1){
        printf("Stack Empty\n");
    }
    else{
        printf("Elements of the stack are:\n");
        for (i = top; i >= 0; i--){
            printf("%d\n", arr[i]);
        }
    }
}

void peek(){
    if (top == -1){
        printf("Stack Underflow\n");
    }
    else{
        printf("Peek element is %d\n", arr[top]);
    }
}

void s_large() {
    if (top < 1 || top == -1) {
        printf("There is not enough element to find 2nd largest number\n");
    }
    int large = arr[0], slarge = 0, i;
    for (i = 1; i <= top; i++) {
        if (arr[i] > large) {
            slarge = large;
            large = arr[i];
        } 
        else if (arr[i] > slarge && arr[i] != large) {
            slarge = arr[i];
        }
    }
    if (slarge == 0) {
        printf("No second largest element found\n");
    } 
    else {
        printf("Second largest element is %d\n", slarge);
    }
}

int main(){
    int choice;
    printf("STACK\n");
    
    while (1) {
        printf("Enter 1 for push\n");
        printf("Enter 2 for pop\n");
        printf("Enter 3 for display\n");
        printf("Enter 4 to peek\n");
        printf("Enter 5 to find second largest number\n");
        printf("Enter 6 to Exit\n");
        printf("Enter your choice:");
        
        scanf("%d", &choice);
        
        if (choice == 1){
            push();
        }
        else if (choice == 2){
            pop();
        }
        else if (choice == 3){
            display();
        }
        else if (choice == 4){
            peek();
        }
        else if (choice == 5){
            s_large();
        }
        else if (choice == 6){
            printf("Exiting program\n");
            break;
        }
        else{
            printf("Invalid choice\n");
        }
    }
    
    return 0;
}
