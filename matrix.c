//Write a program to give the sum of the row and the column in a matrix

#include <stdio.h>

int main() 
{
    int row, col, i, j;
    printf("Enter number of rows and columns: ");
    scanf("%d %d", &row, &col);
    int matrix[row][col];
    printf("Enter matrix elements:\n");
    for (i = 0; i < row; i++) 
    {
        for (j = 0; j < col; j++) 
        {
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("Sum of rows:\n");
    for (i = 0; i < row; i++) 
    {
        int rowSum = 0;
        for (j = 0; j < col; j++) 
        {
            rowSum += matrix[i][j];
        }
        printf("Row %d sum = %d\n", i + 1, rowSum);
    }
    printf("Sum of columns:\n");
    for (j = 0; j < col; j++) 
    {
        int colSum = 0;
        for (i = 0; i < row; i++) 
        {
            colSum += matrix[i][j];
        }
        printf("Column %d sum = %d\n", j + 1, colSum);
    }
    return 0;
}
