#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int degree;   // количество соседей (или потомков)
    int capacity; // текущая емкость динамического массива adj
    int *adj;     // массив номеров соседей (или потомков)
} Vertex;

typedef struct
{
    int size;
    Vertex *vertices;
} Graph;

void addNeighbor(Vertex *vertex, int neighbor)
{
    if (vertex->degree >= vertex->capacity)
    {
        int newCapacity = (vertex->capacity == 0) ? 2 : vertex->capacity * 2;
        int *temp = realloc(vertex->adj, newCapacity * sizeof(int));
        vertex->adj = temp;
        vertex->capacity = newCapacity;
    }
    vertex->adj[vertex->degree++] = neighbor;
}

void inputGraph(Graph *graph)
{
    int i, neighbor;
    printf("Введите количество вершин графа: ");
    scanf("%d", &(graph->size));

    graph->vertices = (Vertex *)malloc(graph->size * sizeof(Vertex));
    
    for (i = 0; i < graph->size; i++)
    {
        graph->vertices[i].degree = 0;
        graph->vertices[i].capacity = 0;
        graph->vertices[i].adj = NULL;

        printf("Вершина %d: ", i);
        while (1)
        {
            scanf("%d", &neighbor);
            if (neighbor == 0)
            {
                break;
            }
            addNeighbor(&graph->vertices[i], neighbor);
        }
    }
}

void freeGraph(Graph *graph)
{
    int i;
    for (i = 0; i < graph->size; i++)
    {
        if (graph->vertices[i].adj != NULL)
        {
            free(graph->vertices[i].adj);
        }
    }
    free(graph->vertices);
}

void dfs(Graph *graph, int startVertex)
{
    int *visited = (int *)calloc(graph->size, sizeof(int));
    int *stack = (int *)malloc(graph->size * sizeof(int));
    int *childIndex = (int *)malloc(graph->size * sizeof(int));

    int top = 0;
    stack[top] = startVertex;
    childIndex[top] = 0;
    top++;

    printf("Обход в глубину: ");
    while (top > 0)
    {
        int current = stack[top - 1];
        if (!visited[current])
        {
            visited[current] = 1;
            printf("%d ", current);
        }
        if (childIndex[top - 1] < graph->vertices[current].degree)
        {
            int next = graph->vertices[current].adj[childIndex[top - 1]];
            childIndex[top - 1]++;
            if (next >= 0 && next < graph->size && !visited[next])
            {
                stack[top] = next;
                childIndex[top] = 0;
                top++;
            }
        }
        else
        {
            top--;
        }
    }
    printf("\n");

    free(visited);
    free(stack);
    free(childIndex);
}

void main()
{
    Graph graph;
    int mode;
    int start;

    printf("Выберите режим работы:\n");
    printf("1 - Обход графа\n");
    printf("2 - Обход дерева\n");
    printf("Ваш выбор: ");
    scanf("%d", &mode);

    if (mode == 1)
    {
        printf("\n-- Ввод графа --\n");
        inputGraph(&graph);
        printf("Введите стартовую вершину для обхода графа: ");
        scanf("%d", &start);
        printf("\nРезультат обхода графа:\n");
        dfs(&graph, start);
    }
    else if (mode == 2)
    {
        printf("\n-- Ввод дерева --\n");
        inputGraph(&graph);
        printf("Введите корень дерева для обхода: ");
        scanf("%d", &start);
        printf("\nРезультат обхода дерева:\n");
        dfs(&graph, start);
    }
    else
    {
        printf("Неверный выбор!\n");
        return;
    }

    freeGraph(&graph);
}