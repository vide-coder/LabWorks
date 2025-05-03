#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *left;
    struct Node *right;
} Node;

void PrintTree(Node *root)
{
    if (root == NULL)
        return;

    PrintTree(root->left);
    printf("%d ", root->value);
    PrintTree(root->right);
}

void Initialize(Node *node, int value)
{
    node->value = value;
    node->left = NULL;
    node->right = NULL;
}

void Insert(Node *root, int value)
{
    if (value < root->value)
    {
        if (root->left == NULL)
        {
            Node *node = malloc(sizeof(Node));
            Initialize(node, value);
            root->left = node;
        }
        else
        {
            Insert(root->left, value);
        }
    }
    else if (value >= root->value)
    {
        if (root->right == NULL)
        {
            Node *node = malloc(sizeof(Node));
            Initialize(node, value);
            root->right = node;
        }
        else
        {
            Insert(root->right, value);
        }
    }
}

void InitializeTree(Node **root)
{
    *root = malloc(sizeof(Node));
    Initialize(*root, 8);

    Insert(*root, 3);
    Insert(*root, 10);
    Insert(*root, 1);
    Insert(*root, 6);
    Insert(*root, 14);
    Insert(*root, 4);
    Insert(*root, 7);
    Insert(*root, 13);
}

Node *Search(Node *node, int value)
{
    if (node == NULL)
        return NULL;
    if (node->value == value)
        return node;
    return (value < node->value) ? Search(node->left, value) : Search(node->right, value);
}

void Clear(Node *root, Node **externalReference)
{
    if (root == NULL)
    {
        *externalReference = NULL;
        return;
    }
    Clear(root->left, externalReference);
    Clear(root->right, externalReference);
}

Node* GetMin(Node *node, int *counter)
{
    if (node == NULL)
        return NULL;
    if (node->left == NULL)
        return node;

    (*counter)++;
    return GetMin(node->left, counter);
}

Node* GetMax(Node *node, int *counter)
{
    if (node == NULL)
        return NULL;
    if (node->right == NULL)
        return node;

    *counter++;
    return GetMax(node->right, counter);
}

int GetHeight(Node *root)
{
    int *counter = malloc(sizeof(int));
    *counter = 1;

    GetMin(root, counter);
    int maxValueLeght = *counter;
    *counter = 1;
    
    GetMax(root, counter);
    int minValueLeght = *counter;
    *counter = 1;

    return maxValueLeght >= minValueLeght ? maxValueLeght : minValueLeght;
}

void main()
{
    Node *root = NULL;

    InitializeTree(&root);
    PrintTree(root);

    printf("\nВысота: %d", GetHeight(root));

    Insert(root, 0);
    Insert(root, 2);
    Insert(root, 9);
    Insert(root, 5);

    printf("\n");
    PrintTree(root);

    printf("\n%p, %p, %p ", Search(root, 0), Search(root, 11), Search(root, 2));

    printf("\nВысота: %d", GetHeight(root));

    printf("\n");
    PrintTree(root);
    Clear(root, &root);
    printf("\n");
    PrintTree(root);
}