#include <stdio.h>
#include <stdlib.h>
#include "Lab_2.c"

typedef List Stack;
typedef List Queue;

void PushToStack(Stack *stack, int value) 
{
    PushBack(stack, value);
}
void PopFromStack(Stack *stack) 
{
    PopBack(stack);
}
int TopOfStack(Stack *stack) 
{
    return Back(stack);
}

void PushToQueue(Queue *queue, int value)
{
    PushFront(queue, value);
}
void PopFromQueue(Queue *queue)
{
    PopBack(queue);
}
int FrontOfQueue(Queue *queue)
{
    return Back(queue);
}
int BackOfQueue(Queue *queue)
{
    return Front(queue);
}
int IsEmpty(List *list) 
{
    return GetSize(list->head) == 0;
}

void main()
{
    Stack stack = {0};
    for (size_t i = 0; i < 5; i++)
        PushToStack(&stack, i);
    for (size_t i = 0; !IsEmpty(&stack); PopFromStack(&stack))
        printf("%d ", TopOfStack(&stack));
    printf("\n");
    // 4 3 2 1 0

    Queue queue = {0};
    for (size_t i = 0; i < 5; i++)
        PushToQueue(&queue, i);
    for (size_t i = 0; !IsEmpty(&queue); PopFromQueue(&queue))
        printf("%d ", FrontOfQueue(&queue));
    printf("\n");
    // 0 1 2 3 4
}