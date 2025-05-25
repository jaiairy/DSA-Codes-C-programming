/*Linear search
    Case 1: Element not present
    Case 2: Occurance of the element is unique
    Case 3: Element is present at multiple locations*/

#include <stdio.h>

int main() 
{
    int n, t, i, f = 0;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the elements of the array:\n");
    for (i = 0; i < n; i++) 
    {
        scanf("%d", &arr[i]);
    }

    printf("Enter the element to search for: ");
    scanf("%d", &t);

    for (i = 0; i < n; i++) 
    {
        if (arr[i] == t) 
        {
            printf("Element found at position %d\n", i+1);
            f = 1;
            break;
        }
    }

    if (f==0) 
    {
        printf("Element not found in the array\n");
    }

    return 0;
}