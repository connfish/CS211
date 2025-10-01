#include <stdio.h>
#include <stdlib.h>

long long int** createMatrix(int n) 
{
    long long int** matrix = (long long int**)malloc(n * sizeof(long long int*));
    for (int i = 0; i < n; i++) 
    {
        matrix[i] = (long long int*)malloc(n * sizeof(long long int));
    }
    return matrix;
}

void freeMatrix(long long int** matrix, int n) 
{
    for (int i = 0; i < n; i++) 
    {
        free(matrix[i]);
    }
    free(matrix);
}

long long int** createSubMatrix(long long int** matrix, int n, int col) 
{
    long long int** submatrix = createMatrix(n - 1);
    
    int sub_i = 0;
    for (int i = 1; i < n; i++) 
    {
        int sub_j = 0;
        for (int j = 0; j < n; j++) 
        {
            if (j != col) 
            {
                submatrix[sub_i][sub_j] = matrix[i][j];
                sub_j++;
            }
        }
        sub_i++;
    }
    
    return submatrix;
}

long long int determinant(long long int** matrix, int n) 
{
    //base case
    if (n == 1) 
    {
        return matrix[0][0];
    }
    
    // ad-bc base case
    if (n == 2) 
    {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    
    long long int det = 0;
    int sign = 1;
    
    for (int i = 0; i < n; i++) 
    {
        long long int** submatrix = createSubMatrix(matrix, n, i);
        det += sign * matrix[0][i] * determinant(submatrix, n - 1);
        sign = -sign;
        freeMatrix(submatrix, n - 1);
    }
    
    return det;
}

int main(int argc, char* argv[]) 
{
    if (argc != 2) 
    {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    
    FILE* file = fopen(argv[1], "r");
    if (!file) 
    {
        printf("Error opening file\n");
        return 1;
    }
    
    int n;
    if (fscanf(file, "%d", &n) != 1)
    {
        printf("Error reading matrix size\n");
        fclose(file);
        return 1;
    }
    
    long long int** matrix = createMatrix(n);
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            if (fscanf(file, "%lld", &matrix[i][j]) != 1)
            {
                printf("Error reading matrix element at position %d,%d\n", i, j);
                freeMatrix(matrix, n);
                fclose(file);
                return 1;
            }
        }
    }
    
    fclose(file);
    
    long long int result = determinant(matrix, n);
    printf("%lld\n", result);  // long long fixes part 5 test case
    
    freeMatrix(matrix, n);
    
    return 0;
}
