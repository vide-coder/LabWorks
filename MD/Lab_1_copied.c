#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
// объявляем и определяем структуру для списка
// смежности
typedef struct _node
{
    int value;
    struct _node *next;
} node;
//---------------------------------------------------
// процедуры варианта выбора
void MIin(); // ввод матрицы инцидентности
void MSin(); // ввод матрицы смежности
void SSin(); // ввод списка смежности
// процедуры ввода
void readArray(int *, int, int); // матрицы
node *readList();                // списка смежности
// процедуры вывода
void printArray(int *, int, int); // матрицы
void printList(node *);           // списка смежности

// процедуры преобразования
// м. инцидентности -> м. смежности
void MI_MS(int *, int *, int, int);
// м. смежности -> список смежности
void MS_SS(int *, int, node **);
// список смежности -> м. инцидентности
void SS_MI(int *, int, node **);
// дополнительные
// подсчёт элементов списка смежности
int countInList(node **, int);
// освобождение памяти для строки из списка
void destroy(node *);
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
        MIin();
        break;
    case 2:
        MSin();
        break;
    case 3:
        SSin();
        break;
    default:
        printf("\t Программа закрывается...\n");
        break;
    }
    getch();
    return 0;
}
// определение функций...
void MIin()
{
    int M, N, i, choice;
    int *A, *B;
    node **arrayOfList;

    printf("Укажите размеры массива:\n");
    printf("M=");
    scanf("%d", &M);
    printf("N=");
    scanf("%d", &N);
    A = (int *)malloc(M * N * sizeof(int));
    readArray(A, M, N);
    printf("-----------------------------------\n");
    printf("Ваша матрица инцидентности:\n");
    printArray(A, M, N);
    printf("----------------------------------\n");
    printf("Выберите, в какой форме отобразить:\n");
    printf("1 - Перевести в матрицу смежности\n");
    printf("2 - Перевести в список смежности\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printf("Перевод в матрицу смежности\n");
        B = (int *)calloc(N * N, sizeof(int));
        // выделение памяти для МС

        MI_MS(A, B, M, N);

        // преобразование
        printf("\nПолученная матрица смежности:\n");
        printf("----------------------------------\n");
        printArray(B, N, N);
        // вывод полученной матрицы
        printf("----------------------------------\n");

        free(A);
        free(B);
        break;

    case 2:
        B = (int *)calloc(N * N, sizeof(int));

        // выделение памяти для промежуточной МС
        MI_MS(A, B, M, N);

        // преобразование

        free(A);

        printf("Перевод в список смежности\n");
        arrayOfList = (node **)malloc(N * sizeof(node *));
        // выделение памяти для СС

        MS_SS(B, N, arrayOfList);
        printf("\nПолученный список смежности:\n");
        printf("----------------------------------\n");

        for (i = 0; i < N; i++)
        {
            printf("%d:", i + 1);

            printList(*(arrayOfList + i));
        }

        printf("----------------------------------\n");

        free(B);
        for (i = 0; i < N; i++)

            destroy(*(arrayOfList + i));

        free(arrayOfList);
        break;

    default:
        printf("\nНеверный выбор...\n");

        free(A);
    }
}
void MSin()
{
    int M, N, i, choice;
    int *A;
    node **arrayOfList;
    printf("Укажите кол-во вершин:\n");
    printf("N=");
    scanf("%d", &N);
    A = (int *)malloc(N * N * sizeof(int));
    readArray(A, N, N);
    printf("----------------------------------\n");
    printf("Матрица смежности:\n");
    printArray(A, N, N);
    printf("----------------------------------\n");
    printf("Выберите, в какой форме отобразить:\n");
    printf("1 - Перевести в список смежности\n");
    printf("2 - Перевести в матрицу инцидентности\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printf("Перевод в список смежности\n");
        arrayOfList = (node **)malloc(N * sizeof(node *));
        MS_SS(A, N, arrayOfList);
        printf("\nПолученный список смежности:\n");
        printf("----------------------------------\n");

        for (i = 0; i < N; i++)
        {
            printf("%d:", i + 1);

            printList(*(arrayOfList + i));
        }
        free(A);
        for (i = 0; i < N; i++)

            destroy(*(arrayOfList + i));

        free(arrayOfList);
        break;

    case 2:
        arrayOfList = (node **)malloc(N * sizeof(node *));
        MS_SS(A, N, arrayOfList);
        M = countInList(arrayOfList, N);
        free(A);

        printf("Перевод в матрицу инцидентности\n");
        A = (int *)calloc(M * N, sizeof(int));
        SS_MI(A, N, arrayOfList);
        printf("\nПолученная матрица инцидентности:\n");
        printf("----------------------------------------\n");

        printArray(A, M, N);

        printf("----------------------------------------\n");

        free(A);
        for (i = 0; i < N; i++)

            destroy(*(arrayOfList + i));

        free(arrayOfList);
        break;

    default:
        printf("\nНеверный выбор...\n");

        free(A);
    }
}
void SSin()
{
    int M, N, i, choice;
    int *A, *B;
    node **arrayOfList;
    printf("\n\t+ Кол-во вершин в графе: ");
    scanf("%d", &N);
    arrayOfList = (node **)malloc(N * sizeof(node *));
    // выделение памяти под СС
    for (i = 0; i < N; i++)
    {
        printf("Вершина #%d\n", i + 1);
        *(arrayOfList + i) = readList();
    }

    printf("----------------------------------\n");
    printf("Список смежности:\n");
    for (i = 0; i < N; i++)
    {
        printf("%d:", i + 1);
        printList(*(arrayOfList + i));
    }
    printf("----------------------------------\n");
    M = countInList(arrayOfList, N);
    printf("Выберите, в какой форме отобразить:\n");
    printf("1 - Перевод в матрицу инцидентности\n");
    printf("2 - Перевод в матрицу смежности\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printf("Перевод в матрицу инцидентности\n");
        A = (int *)calloc(M * N, sizeof(int));
        SS_MI(A, N, arrayOfList);
        printf("\nПолученная матрица инцидентности:");
        printf("\n--------------------------------------\n");

        printArray(A, M, N);

        printf("----------------------------------------\n");

        free(A);
        for (i = 0; i < N; i++)

            destroy(*(arrayOfList + i));

        free(arrayOfList);
        break;

    case 2:
        A = (int *)calloc(M * N, sizeof(int));
        SS_MI(A, N, arrayOfList);
        for (i = 0; i < N; i++)

            destroy(*(arrayOfList + i));

        free(arrayOfList);
        B = (int *)calloc(N * N, sizeof(int));
        printf("Перевод в матрицу смежности\n");

        MI_MS(A, B, M, N);
        printf("\nПолученная матрица смежности:");
        printf("\n--------------------------------------\n");

        printArray(B, N, N);

        printf("----------------------------------------\n");

        free(A);
        free(B);
        break;

    default:
        printf("\nНеверный выбор\n");
        for (i = 0; i < N; i++)

            destroy(*(arrayOfList + i));

        free(arrayOfList);
    }
}
void readArray(int *A, int M, int N)
{
    int i, j;
    for (i = 0; i < M; i++)
        for (j = 0; j < N; j++)
        {
            printf("A[%d][%d]=", i + 1, j + 1);
            scanf("%d", (A + i * N + j));
        }
}
node *readList()
{
    int i = 0, semn;
    int sizeOfNode = sizeof(node);
    node *A = NULL, *R1, *R2;
    printf("%d : ", ++i);
    scanf("%d", &semn);
    if (semn)
    {
        R1 = (node *)malloc(sizeOfNode);
        R1->value = semn;
        R1->next = NULL;
        A = R1;
        printf("%d : ", ++i);
        scanf("%d", &semn);
    }
    while (semn)
    {
        R2 = (node *)malloc(sizeOfNode);
        R2->value = semn;
        R2->next = NULL;
        R1->next = R2;
        R1 = R2;
        printf("%d : ", ++i);
        scanf("%d", &semn);
    }
    printf("\n");
    return A;
}

void printArray(int *A, int M, int N)
{
    int i, j;
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
            printf("%3d", *(A + i * N + j));
        printf("\n");
    }
}
void printList(node *R)
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
void MI_MS(int *A, int *B, int M, int N)
{
    int i, j, a, b;
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
            if (*(A + i * N + j) == 2)
                a = b = j;
            else
            {
                if (*(A + i * N + j) == -1)
                    a = j;
                if (*(A + i * N + j) == 1)
                    b = j;
            }
        *(B + a * N + b) = 1;
    }
}
void MS_SS(int *A, int N, node **arrayOfList)
{
    int i, j, k;
    int sizeOfNode = sizeof(node);
    node *R1, *R2;

    for (i = 0; i < N; i++) // найти первую 1 в строке
    {
        j = 0;
        k = 0;
        while (!k && (j < N))
        {
            if (*(A + i * N + j))
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
            while (j < N)
            {
                if (*(A + i * N + j))
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
            *(arrayOfList + i) = NULL;
    }
}
void SS_MI(int *A, int N, node **arrayOfList)
{
    int i, j, k = 0;
    node *R;
    for (i = 0; i < N; i++)
    {
        R = *(arrayOfList + i);
        while (R)
        {
            if ((R->value) - 1 == i)
                *(A + k * N + i) = 2;
            else
            {

                *(A + k * N + i) = -1;
                *(A + k * N + (R->value) - 1) = 1;
            }
            R = R->next;
            k++;
        }
    }
}
int countInList(node **arrayOfList, int N)
{
    int i, k = 0;
    node *R;
    for (i = 0; i < N; i++)
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
void destroy(node *R)
{
    node *TMP;
    while (R)
    {
        TMP = R;
        R = R->next;
        free(TMP);
    }
}