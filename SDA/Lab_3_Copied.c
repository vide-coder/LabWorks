#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct
{
    Node *head;
    Node *tail;
    size_t size;
} List;

void initialize(List *list);

void resize(List *list, size_t new_size);

int front(const List *list);
int back(const List *list);

void push_front(List *list, int value);
void pop_front(List *list);

void push_back(List *list, int value);
void pop_back(List *list);

void clear(List *list);

size_t size(const List *list);

void insert_after(List *list, Node *pos, int value);

void erase_after(List *list, Node *pos);

void initialize(List *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void resize(List *list, size_t new_size)
{
    while (list->size > new_size)
    {
        pop_back(list);
    }
    while (list->size < new_size)
    {
        push_back(list, 0);
    }
}

int front(const List *list)
{
    if (!list->head)
    {
        fprintf(stderr, "Error: front() on empty list\n");
        exit(EXIT_FAILURE);
    }
    return list->head->data;
}

int back(const List *list)
{
    if (!list->tail)
    {
        fprintf(stderr, "Error: back() on empty list\n");
        exit(EXIT_FAILURE);
    }
    return list->tail->data;
}

void push_front(List *list, int value)
{
    Node *node = malloc(sizeof(Node));
    node->data = value;
    node->next = list->head;
    list->head = node;
    if (!list->tail)
    {
        list->tail = node;
    }
    list->size++;
}

void pop_front(List *list)
{
    if (!list->head)
        return;
    Node *tmp = list->head;
    list->head = tmp->next;
    free(tmp);
    if (!list->head)
    {
        list->tail = NULL;
    }
    list->size--;
}

void push_back(List *list, int value)
{
    Node *node = malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;
    if (list->tail)
    {
        list->tail->next = node;
    }
    else
    {
        list->head = node;
    }
    list->tail = node;
    list->size++;
}

void pop_back(List *list)
{
    if (!list->tail)
        return;
    if (list->head == list->tail)
    {
        free(list->head);
        list->head = list->tail = NULL;
    }
    else
    {
        Node *cur = list->head;
        while (cur->next != list->tail)
        {
            cur = cur->next;
        }
        free(list->tail);
        list->tail = cur;
        list->tail->next = NULL;
    }
    list->size--;
}

void clear(List *list)
{
    Node *cur = list->head;
    while (cur)
    {
        Node *next = cur->next;
        free(cur);
        cur = next;
    }
    initialize(list);
}

size_t size(const List *list)
{
    return list->size;
}

void insert_after(List *list, Node *pos, int value)
{
    if (!pos)
    {
        push_front(list, value);
    }
    else
    {
        Node *node = malloc(sizeof(Node));
        node->data = value;
        node->next = pos->next;
        pos->next = node;
        if (list->tail == pos)
        {
            list->tail = node;
        }
        list->size++;
    }
}

void erase_after(List *list, Node *pos)
{
    if (!pos)
    {
        pop_front(list);
    }
    else if (pos->next)
    {
        Node *tmp = pos->next;
        pos->next = tmp->next;
        if (tmp == list->tail)
        {
            list->tail = pos;
        }
        free(tmp);
        list->size--;
    }
}

typedef List stack;
typedef List queue;

void push_stack(stack *list, int value)
{
    push_back(list, value);
}

void pop_stack(stack *stack)
{
    pop_back(stack);
}

int top(stack *stack)
{
    back(stack);
}

int empty(List *list)
{
    return size(list) == 0;
}

void push_queue(queue *queue, int value)
{
    push_front(queue, value);
}

void pop_queue(queue *queue)
{
    pop_back(queue);
}

int front_queue(queue *queue)
{
    back(queue);
}

int back_queue(queue *queue)
{
    front(queue);
}

int main(void)
{
    stack s = {0};
    for (size_t i = 0; i < 5; i++)
        push_stack(&s, i);
    for (; !empty(&s); pop_stack(&s))
        printf("%d ", top(&s));
    // 4 3 2 1 0

    queue q = {0};
    for (size_t i = 0; i < 5; i++)
        push_queue(&q, i);
    for (; !empty(&q); pop_queue(&q))
        printf("%d ", front_queue(&q));
    // 0 1 2 3 4
}
