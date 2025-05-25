//Create an array ‘a1’ with ‘n’ elements. Insert an element in ith position of ‘a1’ and also delete an element from jth position of ‘a1’.

#include <stdio.h>

void insert(int a1[], int n, int i, int element) {
    for (int j = n; j > i; j--) {
        a1[j] = a1[j-1];
    }
    a1[i] = element;
}

void delete(int a1[], int n, int j) {
    for (int k = j; k < n - 1; k++) {
        a1[k] = a1[k + 1];
    }
}

int main() {
    int n, i, j, element;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    int a1[n];
    printf("Enter the elements of the array:\n");
    for (int k = 0; k < n; k++) {
        scanf("%d", &a1[k]);
    }
    printf("Enter the position (i) to insert an element: ");
    scanf("%d", &i);
    printf("Enter the element to insert: ");
    scanf("%d", &element);
    insert(a1, n, i, element);
    n++;
    printf("Array after insertion: ");
    for (int k = 0; k < n; k++) {
        printf("%d ", a1[k]);
    }
    printf("\n");
    printf("Enter the position (j) to delete an element: ");
    scanf("%d", &j);
    delete(a1, n, j);
    n--; 
    printf("Array after deletion: ");
    for (int k = 0; k < n; k++) {
        printf("%d ", a1[k]);
    }
    printf("\n");

    return 0;
}
