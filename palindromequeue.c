#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define max 1000

int ispalindrome(char str[max]) {
    char queue[max];
    int front = 0, rear = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (isalnum(str[i])) {
            queue[rear] = tolower(str[i]);
            rear++;
        }
    }
    
    rear--; 
    
    while (front < rear) {
        if (queue[front] != queue[rear]) {
            return 0; 
        }
        front++;
        rear--;
    }
    return 1;
}

int main() {
    char str[max];
    printf("Enter a string: ");
    fgets(str, max, stdin);
    str[strcspn(str, "\n")] = '\0'; 
    
    if (ispalindrome(str)) {
        printf("%s is a palindrome\n", str);
    } 
    else {
        printf("%s is not a palindrome\n", str);
    }
    
    return 0;
}
