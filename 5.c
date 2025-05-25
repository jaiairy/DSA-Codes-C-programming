//Write a program to give the sum of all elements in a array

#include <stdio.h>

int sum(int arr[], int index, int n) {
    if (index == n) {
        return 0;
    }
    return arr[index] + sum(arr, index + 1, n);
}

int main() {
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("Sum of array elements: %d\n", sum(arr, 0, n));
    return 0;
}
