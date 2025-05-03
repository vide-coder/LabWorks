#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct List
{
    struct Node *head;
    struct Node *tail;
    int size;
} List;
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

void Clear(List *list);
void ClearNodeChain(Node **head);
int GetSize(Node *head);
void Validate(List *list);

void Resize(List *list, int newSize)
{
    Node *head = list->head;

    if (newSize == 0)
    {
        Clear(list);
        return;
    }
    if (list->size == newSize)
    {
        return;
    }
    if (list->size > newSize)
    {
        int iterator = 1;

        while (head)
        {
            if (iterator == newSize)
            {
                ClearNodeChain(&(head->next));
                head->next = NULL;
                list->tail = head;
                return;
            }

            iterator++;
            list->size = iterator;
            head = head->next;
        }
    }
    if (list->size < newSize)
    {
        int iterator = 1;

        while (head)
        {
            if (head->next == NULL && iterator < newSize)
            {
                Node *nextNode = malloc(sizeof(Node));
                nextNode->data = 0;
                nextNode->next = NULL;
                head->next = nextNode;
                list->tail = head;
            }

            iterator++;
            list->size = iterator;
            head = head->next;
        }
    }
}
void Initialize(List *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}
int Front(List *list)
{
    return list->head->data;
}
int Back(List *list)
{
    return list->tail->data;
}
void PushFront(List *list, int value)
{
    Validate(list);

    Node *newNode = malloc(sizeof(Node));
    newNode->next = list->head;
    newNode->data = value;
    list->head = newNode;
    list->size += 1;
}
void PushBack(List *list, int value)
{
    Validate(list);

    Node *newNode = malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->data = value;
    list->tail = newNode;
    list->size += 1;
}
void PopFront(List *list)
{
    if (list->size == 0)
        return;

    Node *head = list->head;
    list->head = list->head->next;
    free(head);

    if(!list->head)
        list->tail = NULL;

    --list->size;
}
void PopBack(List *list)
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
void Clear(List *list)
{
    while (list->head)
    {
        Node *previous = (Node *)list->head;
        list->head = list->head->next;

        free(previous);
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}
void ClearNodeChain(Node **head)
{
    while (*head)
    {
        Node *previous = *head;
        *head = (*head)->next;

        free(previous);
    }
}
int GetSize(Node *head)
{
    int nodesCount = 0;

    while (head)
    {
        nodesCount++;
        head = head->next;
    }

    return nodesCount;
}
void Insert(List *list, int index, int value) // тут дают ссылку на сам элемент, а не индекс
{
    if (index > list->size)
    {
        Resize(list, index + 1);
    }

    Node *head = list->head;
    int iterator = 1;

    while (list->head)
    {
        if (iterator == index)
        {
            Node *newNode = malloc(sizeof(Node));
            newNode->next = list->head->next;
            newNode->data = value;
            list->head->next = newNode;
            list->head = head;
            return;
        }

        iterator++;
        list->size = iterator;
        list->head = list->head->next;
    }

    list->head = head;
}
void Erase(List *list, int index)
{
    if (index > list->size)
    {
        return;
    }

    Node *head = list->head;
    int iterator = 1;

    while (list->head)
    {
        if (iterator == index)
        {
            Node *node = list->head->next;
            list->head->next = list->head->next->next;
            node->next = NULL;
            free(node);

            list->head = head;
            return;
        }

        iterator++;
        list->size = iterator;
        list->head = list->head->next;
    }

    list->head = head;
}
void Validate(List *list)
{
    Node *head = list->head;

    if (list->head == NULL)
    {
        Initialize(list);
        Resize(list, 1);
    }

    while (head)
    {
        if (head->next == NULL)
        {
            list->tail = head;
        }

        head = head->next;
    }
    
    list->size = GetSize(list->head);
}

void test_initialize()
{
    List example;

    Initialize(&example);
    //assert(received == SIG_DEF);
    assert(example.head == NULL);
    assert(example.tail == NULL);
    assert(example.size == 0);
}
// void test_push_front()
// {
//     List example = {NULL, NULL, 0};

//     PushFront(&example, 1);
//     //assert(received == SIG_DEF);
//     assert(example.head);
//     assert(example.tail);
//     assert(example.head == example.tail);
//     assert(example.head->data == 1);
//     assert(example.size == 1);

//     PushFront(&example, 2);
//     //assert(received == SIG_DEF);
//     assert(example.head != example.tail);
//     assert(example.head->next == example.tail);
//     assert(example.head->data == 2);
//     assert(example.tail->data == 1);
//     assert(example.size == 2);

//     free(example.tail);
//     free(example.head);
// }
// void test_pop_front()
// {
//     List example = {malloc(sizeof(Node)), calloc(1, sizeof(Node)), 2};
//     assert(example.head);
//     assert(example.tail);
//     example.head->next = example.tail;
//     example.head->data = 1;

//     PopFront(&example);
//     //assert(received == SIG_DEF);
//     assert(example.head == example.tail);
//     assert(example.head->next == NULL);
//     assert(example.head->data == 0);
//     assert(example.size == 1);

//     PopFront(&example);
//     //assert(received == SIG_DEF);
//     assert(example.head == NULL);
//     assert(example.tail == NULL);
//     assert(example.size == 0);

//     PopFront(&example);
//     //assert(received == SIG_IC);
//     assert(example.head == NULL);
//     assert(example.tail == NULL);
//     assert(example.size == 0);
// }
// void test_push_back()
// {
//     List example = {NULL, NULL, 0};

//     PushBack(&example, 1);
//     //assert(received == SIG_DEF);
//     assert(example.head);
//     assert(example.head == example.tail);
//     assert(example.head->data == 1);
//     assert(example.size == 1);

//     PushBack(&example, 2);
//     //assert(received == SIG_DEF);
//     assert(example.head->next == example.tail);
//     assert(example.head->data == 1);
//     assert(example.tail->data == 2);
//     assert(example.size == 2);

//     free(example.tail);
//     free(example.head);
// }
// void test_pop_back()
// {
//     List example = {malloc(sizeof(Node)), calloc(1, sizeof(Node)), 2};
//     assert(example.head);
//     assert(example.tail);
//     example.head->data = 1;
//     example.head->next = example.tail;

//     PopBack(&example);
//     //assert(received == SIG_DEF);
//     assert(example.head == example.tail);
//     assert(example.tail->data == 1);
//     assert(example.size == 1);

//     PopBack(&example);
//     //assert(received == SIG_DEF);
//     assert(example.head == NULL);
//     assert(example.tail == NULL);
//     assert(example.size == 0);

//     PopBack(&example);
//     //assert(received == SIG_IC);
//     assert(example.head == NULL);
//     assert(example.tail == NULL);
//     assert(example.size == 0);
// }
// void test_insert()
// {
//     List example;
//     example.head = calloc(1, sizeof(Node));
//     assert(example.head);
//     example.tail = example.head;
//     example.size = 1;

//     Insert(&example, 2, 5);
//     //assert(received == SIG_DEF);
//     assert(example.head->next == example.tail);
//     assert(example.head->data == 0);
//     assert(example.tail->data == 2);
//     assert(example.size == 2);

//     Insert(example.head, 1, &example);
//     //assert(received == SIG_DEF);
//     assert(example.head->next->next == example.tail);
//     assert(example.head->next->data == 1);
//     assert(example.tail->data == 2);

//     free(example.tail);
//     free(example.head->next);
//     free(example.head);
// }
// void test_erase()
// {
//     List example = {malloc(sizeof(Node)), calloc(1, sizeof(Node)), 4};
//     Node *sec = malloc(sizeof(Node));
//     Node *thrd = malloc(sizeof(Node));
//     assert(example.head);
//     assert(example.tail);
//     assert(sec);
//     assert(thrd);
//     thrd->next = example.tail;
//     thrd->data = 1;
//     sec->next = thrd;
//     sec->data = 2;
//     example.head->next = sec;
//     example.head->data = 3;

//     erase(example.tail, &example);
//     //assert(received == SIG_DEF);
//     assert(example.head->next == sec);
//     assert(sec->next == thrd);
//     assert(example.tail == thrd->next);
//     assert(example.size == 4);

//     erase(example.head->next, &example);
//     //assert(received == SIG_DEF);
//     assert(example.head->next->next == example.tail);
//     assert(example.head->next->data == 2);
//     assert(example.tail->data == 0);
//     assert(example.tail->next == NULL);
//     assert(example.size == 3);

//     erase(example.head, &example);
//     //assert(received == SIG_DEF);
//     assert(example.head->next == example.tail);
//     assert(example.head->data == 3);
//     assert(example.tail->data == 0);
//     assert(example.tail->next == NULL);
//     assert(example.size == 2);

//     erase(example.head, &example);
//     //assert(received == SIG_DEF);
//     assert(example.head == example.tail);
//     assert(example.head->data == 3);
//     assert(example.tail->next == NULL);
//     assert(example.size == 1);
// }
// void test_front()
// {
//     List example = {NULL, NULL, 0};

//     //assert(front(&example) == SIG_IC);
//     //assert(received == SIG_IC);

//     example.head = malloc(sizeof(Node));
//     assert(example.head);
//     example.head->next = NULL;
//     example.tail = example.head;
//     example.head->data = 1;
//     example.size = 1;
//     assert(front(&example) == 1);
//     //assert(received == SIG_DEF);

//     example.tail = malloc(sizeof(Node));
//     assert(example.tail);
//     example.size = 2;
//     example.head->next = example.tail;
//     example.tail->next = NULL;
//     example.tail->data = 2;
//     assert(front(&example) == 1);
//     //assert(received == SIG_DEF);
// }
// void test_back()
// {
//     List example = {NULL, NULL, 0};

//     //assert(back(&example) == SIG_IC);
//     //assert(received == SIG_IC);

//     example.head = malloc(sizeof(Node));
//     assert(example.head);
//     example.head->next = NULL;
//     example.tail = example.head;
//     example.head->data = 1;
//     example.size = 1;
//     assert(back(&example) == 1);
//     //assert(received == SIG_DEF);

//     example.tail = malloc(sizeof(Node));
//     assert(example.tail);
//     example.size = 2;
//     example.head->next = example.tail;
//     example.tail->next = NULL;
//     example.tail->data = 2;
//     assert(back(&example) == 2);
//     //assert(received == SIG_DEF);
// }
// void test_resize()
// {
//     List example = {NULL, NULL, 0};

//     resize(&example, -1);
//     //assert(received == SIG_TRN);
//     assert(example.head == NULL);
//     assert(example.tail == NULL);
//     assert(example.size == 0);

//     resize(&example, 2);
//     //assert(received == SIG_DEF);
//     assert(example.head->next == example.tail);
//     assert(example.head->data == 0);
//     assert(example.tail->data == 0);
//     assert(example.size == 2);

//     resize(&example, 3);
//     //assert(received == SIG_DEF);
//     assert(example.head->next->next == example.tail);
//     assert(example.head->data == 0);
//     assert(example.head->next->data == 0);
//     assert(example.tail->data == 0);
//     assert(example.size == 3);

//     resize(&example, 1);
//     //assert(received == SIG_DEF);
//     assert(example.head == example.tail);
//     assert(example.size == 1);
//     assert(example.head->data == 0);
//     assert(example.tail->next == NULL);

//     resize(&example, 0);
//     //assert(received == SIG_DEF);
//     assert(example.head == NULL);
//     assert(example.tail == NULL);
//     assert(example.size == 0);
// }
// void test_size()
// {
//     List example = {calloc(1, sizeof(Node)), calloc(1, sizeof(Node)), 2};
//     assert(example.head);
//     assert(example.tail);

//     example.head->next = example.tail;
//     assert(size(&example) == 2);
//     //assert(received == SIG_DEF);

//     free(example.tail);
//     free(example.head);
//     example.size = 0;

//     assert(size(&example) == 0);
//     //assert(received == SIG_DEF);
// }
// void test_clear()
// {
//     List example = {malloc(sizeof(Node)), calloc(1, sizeof(Node)), 3};
//     assert(example.head);
//     assert(example.tail);

//     Node *sec = malloc(sizeof(Node));
//     assert(sec);
//     example.head->next = sec;
//     sec->next = example.tail;

//     clear(&example);
//     //assert(received == SIG_DEF);
//     assert(example.head == NULL);
//     assert(example.tail == NULL);
//     assert(example.size == 0);

//     clear(&example);
//     //assert(received == SIG_DEF);
//     assert(example.head == NULL);
//     assert(example.tail == NULL);
//     assert(example.size == 0);
// }

// void main()
// {
//     List *list = malloc(sizeof(List));

//     Node *first = malloc(sizeof(Node));
//     *first = (Node){1, NULL};
    
//     Node *second = malloc(sizeof(Node));
//     *second = (Node){2, NULL};
//     first->next = second;
    
//     Node *third = malloc(sizeof(Node));
//     *third = (Node){3, NULL};
//     second->next = third;
    
//     list->head = first;
//     list->tail = third;
//     list->size = GetSize(list->head);

//     // test_initialize();
//     // test_pop_front();
//     // test_pop_back();
//     // test_push_front();
//     // test_push_back();
//     // test_insert();
//     // test_erase();
//     // test_front();
//     // test_back();
//     // test_resize();
//     // test_size();
//     // test_clear();

//     PopBack(list);
//     PopBack(list);
//     PopBack(list);

//     printf("Вывод листа: ");
//     while (list->head)
//     {
//         printf("%d ", list->head->data);
//         list->head = list->head->next;
//     }

//     printf("\nРазмер: %d, Адрес начала: %p, Адрес конца: %p", list->size, list->head, list->tail);
// }