#include <stdio.h>
#include <stdlib.h>

double** createMatrix(int rows, int cols) 
{
    double** matrix = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) 
    {
        matrix[i] = (double*)malloc(cols * sizeof(double));
    }
    return matrix;
}

void freeMatrix(double** matrix, int rows) 
{
    for (int i = 0; i < rows; i++) 
    {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to get absolute value
double absValue(double x) 
{
    return x < 0 ? -x : x;
}


void gaussianElimination(double** matrix, int rows, int cols) 
{

    for (int i = 0; i < rows; i++) 
    {

        int pivot_row = i;
        double max_val = absValue(matrix[i][i]);
        
        for (int j = i + 1; j < rows; j++) 
        {
            double current_val = absValue(matrix[j][i]);
            if (current_val > max_val) 
            {
                max_val = current_val;
                pivot_row = j;
            }
        }

        if (pivot_row != i) 
        {
            for (int j = 0; j < cols; j++) 
            {
                double temp = matrix[i][j];
                matrix[i][j] = matrix[pivot_row][j];
                matrix[pivot_row][j] = temp;
            }
        }

        double pivot = matrix[i][i];
        if (pivot != 0) 
        {
            for (int j = 0; j < cols; j++) 
            {
                matrix[i][j] /= pivot;
            }
        }

        for (int j = 0; j < rows; j++) 
        {
            if (i != j) 
            {
                double factor = matrix[j][i];
                for (int k = 0; k < cols; k++) 
                {
                    matrix[j][k] -= factor * matrix[i][k];
                }
            }
        }
    }

    // Fix negative zeros
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            if (absValue(matrix[i][j]) < 1e-10) 
            {
                matrix[i][j] = 0.0;
            }
        }
    }
}

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) 
    {
        printf("Error opening file\n");
        return 1;
    }

    int rows, cols;
    int read_count;
    read_count = fscanf(file, "%d", &rows);

    if (read_count != 1) 
    {
        fclose(file);
        return 1;
    }
    
    read_count = fscanf(file, "%d", &cols);
    if (read_count != 1) 
    {
        fclose(file);
        return 1;
    }

    double** matrix = createMatrix(rows, cols);
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            read_count = fscanf(file, "%lf", &matrix[i][j]);
            if (read_count != 1) 
            {
                freeMatrix(matrix, rows);
                fclose(file);
                return 1;
            }
        }
    }
    fclose(file);

    gaussianElimination(matrix, rows, cols);

    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            printf("%lf\t", matrix[i][j]);
            
        }
        printf("\n");
    }


    freeMatrix(matrix, rows);
    return 0;
}