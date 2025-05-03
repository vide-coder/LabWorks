#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

typedef struct _node
{
    int value;
    struct _node *next;
} node;

void ReadMatrix(int *A, int rows, int columns);
void PrintArray(int *A, int rows, int columns);
void IncidenceMatrixToAdjacencyMatrix(int *A, int *B, int rows, int columns);
void AdjacencyMatrixToAdjacencyList(int *A, int columns, node **arrayOfList);
void PrintList(node *R);
void FreeNodeMemory(node *R);
int GetElementsCountInList(node **arrayOfList, int columns);
void AdjacencyListToIncidenceMatrix(int *A, int columns, node **arrayOfList);
node *ReadList();
int GetElementsCountInList(node **arrayOfList, int columns);

void InitializeIncidenceMatrix()
{
    int rows, columns, choice;
    int *A, *B;
    node **arrayOfList;

    printf("Укажите размеры массива:\n");
    printf("rows=");
    scanf("%d", &rows);
    printf("columns=");
    scanf("%d", &columns);
    A = (int *)malloc(rows * columns * sizeof(int));
    ReadMatrix(A, rows, columns);
    printf("----------------------------------\n");
    printf("Ваша матрица инцидентности:\n");
    PrintArray(A, rows, columns);
    printf("----------------------------------\n");
    printf("Выберите, в какой форме отобразить:\n");
    printf("1 - Перевести в матрицу смежности\n");
    printf("2 - Перевести в список смежности\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printf("Перевод в матрицу смежности\n");
        B = (int *)calloc(columns * columns, sizeof(int));
        IncidenceMatrixToAdjacencyMatrix(A, B, rows, columns);
        printf("\nПолученная матрица смежности:\n");
        printf("----------------------------------\n");
        PrintArray(B, columns, columns);
        printf("----------------------------------\n");
        free(A);
        free(B);
        break;
    case 2:
        B = (int *)calloc(columns * columns, sizeof(int));
        IncidenceMatrixToAdjacencyMatrix(A, B, rows, columns);
        free(A);
        printf("Перевод в список смежности\n");
        arrayOfList = (node **)malloc(columns * sizeof(node *));
        AdjacencyMatrixToAdjacencyList(B, columns, arrayOfList);
        printf("\nПолученный список смежности:\n");
        printf("----------------------------------\n");
        for (int i = 0; i < columns; i++)
        {
            printf("%d:", i + 1);

            PrintList(*(arrayOfList + i));
        }
        printf("----------------------------------\n");
        free(B);
        for (int i = 0; i < columns; i++)
            FreeNodeMemory(*(arrayOfList + i));
        free(arrayOfList);
        break;
    default:
        printf("\nНеверный выбор...\n");
        free(A);
    }
}
void InitializeAdjacencyMatrix()
{
    int rows, columns, i, choice;
    int *A;
    node **arrayOfList;
    printf("Укажите кол-во вершин:\n");
    printf("columns=");
    scanf("%d", &columns);
    A = (int *)malloc(columns * columns * sizeof(int));
    ReadMatrix(A, columns, columns);
    printf("----------------------------------\n");
    printf("Матрица смежности:\n");
    PrintArray(A, columns, columns);
    printf("----------------------------------\n");
    printf("Выберите, в какой форме отобразить:\n");
    printf("1 - Перевести в список смежности\n");
    printf("2 - Перевести в матрицу инцидентности\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printf("Перевод в список смежности\n");
        arrayOfList = (node **)malloc(columns * sizeof(node *));
        AdjacencyMatrixToAdjacencyList(A, columns, arrayOfList);
        printf("\nПолученный список смежности:\n");
        printf("----------------------------------\n");
        for (i = 0; i < columns; i++)
        {
            printf("%d:", i + 1);

            PrintList(*(arrayOfList + i));
        }
        free(A);
        for (i = 0; i < columns; i++)
            FreeNodeMemory(*(arrayOfList + i));
        free(arrayOfList);
        break;
    case 2:
        arrayOfList = (node **)malloc(columns * sizeof(node *));
        AdjacencyMatrixToAdjacencyList(A, columns, arrayOfList);
        rows = GetElementsCountInList(arrayOfList, columns);
        free(A);
        printf("Перевод в матрицу инцидентности\n");
        A = (int *)calloc(rows * columns, sizeof(int));
        AdjacencyListToIncidenceMatrix(A, columns, arrayOfList);
        printf("\nПолученная матрица инцидентности:\n");
        printf("----------------------------------------\n");
        PrintArray(A, rows, columns);
        printf("----------------------------------------\n");
        free(A);
        for (i = 0; i < columns; i++)
            FreeNodeMemory(*(arrayOfList + i));
        free(arrayOfList);
        break;
    default:
        printf("\nНеверный выбор...\n");
        free(A);
    }
}
void InitializeAdjacencyList()
{
    int rows, columns, i, choice;
    int *A, *B;
    node **arrayOfList;
    printf("\n\t+ Кол-во вершин в графе: ");
    scanf("%d", &columns);
    arrayOfList = (node **)malloc(columns * sizeof(node *));
    for (i = 0; i < columns; i++)
    {
        printf("Вершина #%d\n", i + 1);
        *(arrayOfList + i) = ReadList();
    }

    printf("----------------------------------\n");
    printf("Список смежности:\n");
    for (i = 0; i < columns; i++)
    {
        printf("%d:", i + 1);
        PrintList(*(arrayOfList + i));
    }
    printf("----------------------------------\n");
    rows = GetElementsCountInList(arrayOfList, columns);
    printf("Выберите, в какой форме отобразить:\n");
    printf("1 - Перевод в матрицу инцидентности\n");
    printf("2 - Перевод в матрицу смежности\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printf("Перевод в матрицу инцидентности\n");
        A = (int *)calloc(rows * columns, sizeof(int));
        AdjacencyListToIncidenceMatrix(A, columns, arrayOfList);
        printf("\nПолученная матрица инцидентности:");
        printf("\n--------------------------------------\n");
        PrintArray(A, rows, columns);
        printf("----------------------------------------\n");
        free(A);
        for (i = 0; i < columns; i++)
            FreeNodeMemory(*(arrayOfList + i));
        free(arrayOfList);
        break;
    case 2:
        A = (int *)calloc(rows * columns, sizeof(int));
        AdjacencyListToIncidenceMatrix(A, columns, arrayOfList);
        for (i = 0; i < columns; i++)
            FreeNodeMemory(*(arrayOfList + i));
        free(arrayOfList);
        B = (int *)calloc(columns * columns, sizeof(int));
        printf("Перевод в матрицу смежности\n");
        IncidenceMatrixToAdjacencyMatrix(A, B, rows, columns);
        printf("\nПолученная матрица смежности:");
        printf("\n--------------------------------------\n");
        PrintArray(B, columns, columns);
        printf("----------------------------------------\n");
        free(A);
        free(B);
        break;
    default:
        printf("\nНеверный выбор\n");
        for (i = 0; i < columns; i++)
            FreeNodeMemory(*(arrayOfList + i));
        free(arrayOfList);
    }
}

void ReadMatrix(int *A, int rows, int columns)
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            printf("A[%d][%d]=", i + 1, j + 1);
            scanf("%d", (A + i * columns + j));
        }
    }
}
node *ReadList()
{
    int counter = 0, inputValue;
    node *head = NULL, *tail, *newNode;

    printf("%d : ", ++counter);
    scanf("%d", &inputValue);
    if (inputValue)
    {
        tail = (node *)malloc(sizeof(node));
        tail->value = inputValue;
        tail->next = NULL;
        head = tail;
        printf("%d : ", ++counter);
        scanf("%d", &inputValue);
    }
    while (inputValue)
    {
        newNode = (node *)malloc(sizeof(node));
        newNode->value = inputValue;
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
        printf("%d : ", ++counter);
        scanf("%d", &inputValue);
    }
    printf("\n");
    return head;
}
void PrintArray(int *A, int rows, int columns)
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            printf("%3d", *(A + i * columns + j));
        }
        printf("\n");
    }
}
void PrintList(node *R)
{
    int i = 0, semn;
    int sizeOfNode = sizeof(node);
    while (R)
    {
        printf("%2d", R->value);
        R = R->next;
    }
    printf("%2d\n", 0);
}

void IncidenceMatrixToAdjacencyMatrix(int *A, int *B, int rows, int columns)
{
    int i, j, a, b;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            if (*(A + i * columns + j) == 2)
            {
                a = b = j;
            }
            else
            {
                if (*(A + i * columns + j) == -1)
                a = j;
                if (*(A + i * columns + j) == 1)
                b = j;
            }
            *(B + a * columns + b) = 1;
        }
    }
}
void AdjacencyMatrixToAdjacencyList(int *A, int columns, node **arrayOfList)
{
    int i, j, k;
    int sizeOfNode = sizeof(node);
    node *R1, *R2;

    for (i = 0; i < columns; i++) // найти первую 1 в строке
    {
        j = 0;
        k = 0;
        while (!k && (j < columns))
        {
            if (*(A + i * columns + j))
                k = j + 1;
            j++;
        }
        // k=0 - нет в строке 1, иначе k - номер
        // первой 1 в строке (отсчёт с 1)
        if (k)
        {
            R1 = (node *)malloc(sizeOfNode);
            R1->value = k;
            R1->next = NULL;
            *(arrayOfList + i) = R1;
            // продолжаем исследовать строку
            while (j < columns)
            {
                if (*(A + i * columns + j))
                {
                    R2 = (node *)malloc(sizeOfNode);
                    R2->value = j + 1;
                    R2->next = NULL;
                    R1->next = R2;
                    R1 = R2;
                }
                j++;
            }
        }
        else
        {
            *(arrayOfList + i) = NULL;
        }
    }
}
void AdjacencyListToIncidenceMatrix(int *A, int columns, node **arrayOfList)
{
    int i, j, k = 0;
    node *R;
    for (i = 0; i < columns; i++)
    {
        R = *(arrayOfList + i);
        while (R)
        {
            if ((R->value) - 1 == i)
            {   
                *(A + k * columns + i) = 2;
            }
            else
            {
                *(A + k * columns + i) = -1;
                *(A + k * columns + (R->value) - 1) = 1;
            }
            R = R->next;
            k++;
        }
    }
}

int GetElementsCountInList(node **arrayOfList, int columns)
{
    int i, k = 0;
    node *R;
    for (i = 0; i < columns; i++)
    {
        R = *(arrayOfList + i);
        while (R)
        {
            R = R->next;
            k++;
        }
    }
    return k;
}
void FreeNodeMemory(node *R)
{
    node *temporary;
    while (R)
    {
        temporary = R;
        R = R->next;
        free(temporary);
    }
}

int main()
{
    setlocale(0, "Rus");
    int choice;
    printf("Выберите подходящий вариант:\n");
    printf("1 - Перевести из матрицы инцидентности\n");
    printf("2 - Перевести из матрицы смежности\n");
    printf("3 - Перевести из списка смежности\n");
    printf("0 - Закрыть программу\n");
    printf("Ваш выбор: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        InitializeIncidenceMatrix();
        break;
    case 2:
        InitializeAdjacencyMatrix();
        break;
    case 3:
        InitializeAdjacencyList();
        break;
    default:
        printf("\t Программа закрывается...\n");
        break;
    }
    getch();
    return 0;
}