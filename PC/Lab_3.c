#include <stdio.h>

int main(void) // Незаконченна и не работает :<
{
    int rows = 0, cols = 0;
    scanf("%d %d", &rows, &cols);

    if (rows == 0 || cols == 0)
    {
        return 0;
    }

    const int NUM_ROWS = rows;
    const int NUM_COLS = cols;
    int matrix[NUM_ROWS][NUM_COLS];

    for (size_t i = 0; i < NUM_ROWS; i++)
    {
        for (size_t j = 0; j < NUM_COLS; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    int minRowValue = matrix[0][0];
    int maxCollumnValue = matrix[0][0];
    int targetValue = 0;

    int collumnIndex = 0;
    int rowIndex = 0;

    for (size_t i = 0; i < NUM_ROWS; i++)
    {
        for (size_t j = 0; j < NUM_COLS; j++)
        {
            if (minRowValue >= matrix[i][j])
            {
                minRowValue = matrix[i][j];
                collumnIndex = j;
            }
        }

        for (size_t k = 0; k < NUM_ROWS; k++)
        {
            if (maxCollumnValue <= matrix[k][collumnIndex])
            {
                maxCollumnValue = matrix[k][collumnIndex];
                rowIndex = k;
            }
        }

        minRowValue = 999;
        maxCollumnValue = -999;
    }

    if (minRowValue != 999 || maxCollumnValue != -999)
    {
        printf("%d ", matrix[rowIndex][collumnIndex]);
    }
    
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < rows - i - 1; j++)
        {
            printf("%d ", matrix[i][j]);
        }
    }
}