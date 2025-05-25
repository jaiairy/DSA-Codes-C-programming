//Write a program to give the product of matrix using dynamic memory allocation 

#include <stdio.h>
#include <stdlib.h>

int main() 
{
    int r1, c1, r2, c2, i, j, k;
    printf("Enter rows and columns of first matrix: ");
    scanf("%d %d", &r1, &c1);

    printf("Enter rows and columns of second matrix: ");
    scanf("%d %d", &r2, &c2);
    if (c1 != r2) 
    {
        printf("Matrix multiplication not possible! (Columns of A must equal Rows of B)\n");
        return 1; 
    }
    int *A = (int *)malloc(r1 * c1 * sizeof(int));
    int *B = (int *)malloc(r2 * c2 * sizeof(int));
    int *C = (int *)malloc(r1 * c2 * sizeof(int));
    printf("Enter elements of first matrix:\n");
    for (i = 0; i < r1; i++){
        for (j = 0; j < c1; j++){
            scanf("%d", (A + i * c1 + j));
        }
    }
    printf("Enter elements of second matrix:\n");
    for (i = 0; i < r2; i++){
        for (j = 0; j < c2; j++){
            scanf("%d", (B + i * c2 + j));
        }
    }
    for (i = 0; i < r1; i++) 
    {
        for (j = 0; j < c2; j++) 
        {
            *(C + i * c2 + j) = 0;
            for (k = 0; k < c1; k++) 
            {
                *(C + i * c2 + j) += (*(A + i * c1 + k)) * (*(B + k * c2 + j));
            }
        }
    }
    printf("Product matrix:\n");
    for (i = 0; i < r1; i++) 
    {
        for (j = 0; j < c2; j++) 
        {
            printf("%d ", *(C + i * c2 + j));
        }
        printf("\n");
    }
    free(A);
    free(B);
    free(C);

    return 0;
}