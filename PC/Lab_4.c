#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>              // Задание не сделано и не работает как надо даже на уровне логики

/*
ЗАДАНИЕ: Удалить нулевые строки и столбцы матрицы, получив тем самым новую матрицу

РЕАЛИЗАЦИЯ:
1. Создание первоначального массива. Важно знать размер по i и j
2. 2 цикла: который проходится по строкам и по столбцам
3.
*/

// int main()
// {
//     int matrixSizeI = 4;
//     int matrixSizeJ = 4;

//     int inputMatrix[4][4] =
//         {
//             {1, 2, 0, 4},
//             {5, 6, 0, 8},
//             {0, 0, 0, 0},
//             {3, 7, 0, 9}
//         };

//     int **outputMatrix = calloc(matrixSizeI, sizeof(int*));

//     for (size_t i = 0; i < matrixSizeI; i++)
//     {
//         outputMatrix[i] = calloc(matrixSizeJ, sizeof(int));
//     }

//     for (size_t i = 0; i < matrixSizeI; i++)
//     {
//         for (size_t j = 0; j < matrixSizeJ; j++)
//         {
//             if (inputMatrix[i][j] != 0)
//             {
//                 continue;
//             }

//             if (j == matrixSizeJ - 1)
//             {
//                 // Remove string function
//                 int skipRow = i;

//                 // Выделяем память под новую матрицу
//                 outputMatrix = (int**)realloc(outputMatrix, matrixSizeI - 1); //

//                 for (size_t i = 0; i < matrixSizeI; i++)
//                 {
//                     outputMatrix[i] = calloc(matrixSizeJ, sizeof(int));
//                 }

//                 // Основная логика
//                 for (size_t i = 0; i < matrixSizeI; i++)
//                 {
//                     for (size_t j = 0; j < matrixSizeJ; j++)
//                     {
//                         if (i != skipRow)
//                         {
//                             outputMatrix[i][j] = inputMatrix[i][j];
//                         }
//                     }
//                 }

//                 // Вывод матрицы до удаления строки и после
//                 printf("Первый массив: \n");
//                 for (size_t i = 0; i < matrixSizeI; i++)
//                 {
//                     for (size_t j = 0; j < matrixSizeJ; j++)
//                     {
//                         printf("%d ", inputMatrix[i][j]);
//                     }
//                     printf("\n");
//                 }

//                 printf("Второй массив: \n");
//                 for (size_t i = 0; i < matrixSizeI; i++)
//                 {
//                     for (size_t j = 0; j < matrixSizeJ; j++)
//                     {
//                         printf("%d ", outputMatrix[i][j]);
//                     }
//                     printf("\n");
//                 }
//             }
//         }
//     }
// }


















































// Код от ChatGPT


// Функция для определения размеров новой матрицы и заполнения её
void compressMatrix(int **sourceMatrix, int sourceRows, int sourceCols, int ***compressedMatrix, int *compressedRows, int *compressedCols)
{
    // Подсчет размеров новой матрицы
    int rowCount = 0, colCount = 0;

    for (int i = 0; i < sourceRows; i++)
    {
        for (int j = 0; j < sourceCols; j++)
        {
            if (sourceMatrix[i][j] != 0)
            {
                rowCount++;
                break;
            }
        }
    }

    for (int j = 0; j < sourceCols; j++)
    {
        for (int i = 0; i < sourceRows; i++)
        {
            if (sourceMatrix[i][j] != 0)
            {
                colCount++;
                break;
            }
        }
    }

    *compressedRows = rowCount;
    *compressedCols = colCount;

    // Выделение памяти для новой матрицы
    *compressedMatrix = (int **)malloc(*compressedRows * sizeof(int *));
    for (int i = 0; i < *compressedRows; i++)
    {
        (*compressedMatrix)[i] = (int *)malloc(*compressedCols * sizeof(int));
    }

    // Заполнение новой матрицы
    int newRowIdx = 0;
    for (int i = 0; i < sourceRows; i++)
    {
        int isNonZeroRow = 0;
        for (int j = 0; j < sourceCols; j++)
        {
            if (sourceMatrix[i][j] != 0)
            {
                isNonZeroRow = 1;
                break;
            }
        }
        if (isNonZeroRow)
        {
            int newColIdx = 0;
            for (int j = 0; j < sourceCols; j++)
            {
                int isNonZeroCol = 0;
                for (int k = 0; k < sourceRows; k++)
                {
                    if (sourceMatrix[k][j] != 0)
                    {
                        isNonZeroCol = 1;
                        break;
                    }
                }
                if (isNonZeroCol)
                {
                    (*compressedMatrix)[newRowIdx][newColIdx++] = sourceMatrix[i][j];
                }
            }
            newRowIdx++;
        }
    }
}

// Функция для освобождения памяти матрицы
void freeMatrix(int **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

int main()
{
    int sourceRows, sourceCols;

    // Считывание размеров исходной матрицы
    scanf("%d %d", &sourceRows, &sourceCols);

    // Выделение памяти и считывание исходной матрицы
    int **sourceMatrix = (int **)malloc(sourceRows * sizeof(int *));
    for (int i = 0; i < sourceRows; i++)
    {
        sourceMatrix[i] = (int *)malloc(sourceCols * sizeof(int));
        for (int j = 0; j < sourceCols; j++)
        {
            scanf("%d", &sourceMatrix[i][j]);
        }
    }

    int **compressedMatrix;
    int compressedRows, compressedCols;

    // Уплотнение матрицы
    compressMatrix(sourceMatrix, sourceRows, sourceCols, &compressedMatrix, &compressedRows, &compressedCols);

    // Освобождение памяти
    freeMatrix(sourceMatrix, sourceRows);
    freeMatrix(compressedMatrix, compressedRows);

    return 0;
}



























































// int main(void)
// {
//     size_t brow, bcol;
//     scanf("%zu%zu", &brow, &bcol);
//     int B[brow][bcol];

//     for (size_t i = 0; i < brow; i++)
//     {
//         for (size_t j = 0; j < bcol; j++)
//         {
//             scanf("%d", &B[i][j]);
//         }
//     }

//     //RemoveNullLines(B, brow);
//     //RemoveNullLines(B, bcol);

//     for (size_t i = 0; i < sizeof(B) / sizeof(*B); i++)
//     {
//         for (size_t j = 0; j < sizeof(B) / sizeof(*B); j++)
//         {
//             printf("%d ", B[i][j]);
//         }

//         printf("\n");
//     }

//     // вызов функции, выделяющей память под матрицу
//     // Cons(A, arow, acol);
// }

// void RemoveNullComponents(int *matrix, int size)
// {
//     for (size_t i = 0; i < size; i++)
//     {
//         int previous = 0;

//         for (size_t j = 0; j < size; j++)
//         {
//             if (matrix[i + j] != previous)
//             {
//                 return;
//             }

//             previous = matrix[i + j];
//         }
//     }
// }

// void Cons(int *matrix, int numberRows, int numberColls)
// {

// } /* определение функции создания матрицы здесь */