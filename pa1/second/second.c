#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
    int bytesread = 0; // add if to use bytesread
    if (argc != 2) 
    {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) 
    {
        perror("Error opening file");
        return 1;
    }

    int n;
    bytesread = fscanf(file, "%d", &n); 
    bytesread = fscanf(file, "%d", &n); 

    int matrix[n][n];
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            bytesread = fscanf(file, "%d", &matrix[i][j]);
        }
    }
    if (bytesread == -1)
    {
        printf("\n");
    }
    fclose(file);
    int rotated[n][n];

    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            rotated[j][n - 1 - i] = matrix[i][j];
        }
    }

    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            printf("%d\t", rotated[i][j]);  
        }
        printf("\n");
    }

    return 0;
}