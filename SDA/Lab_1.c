#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct
{
    int *data;
    int *size;
    int *capacity;
} Array;

// Вспомогательные функции
int GetSize(Array *array)
{
    return array->size - array->data;
}

int GetCapacity(Array *array)
{
    return array->capacity - array->data;
}

void IncreaseCapacity(Array *array, int additionalElementsCount) // O(N)
{
    int newCapacity = GetCapacity(array) + additionalElementsCount;
    array->data = realloc(array->data, sizeof(int) * newCapacity);

    for (size_t i = GetCapacity(array); i < newCapacity; i++)
    {
        array->data[i] = 0;
    }

    array->capacity = array->data + newCapacity;    
}

void ValidateArray(Array *array)
{
    const int capacity = 1;

    if (array->data == NULL || array->size == NULL || array->capacity == NULL)
    {
        array->data = malloc(sizeof(int) * capacity);
        array->size = array->data;
        array->capacity = &array->data[capacity];
    }

    if (GetCapacity(array) < (array->data - array->data))
    {
        array->capacity = array->data;
    }
    
    if (GetSize(array) < (array->data - array->data) || GetSize(array) > GetCapacity(array))
    {
        array->size = array->data;
    }
}

void SetArrayPointers(Array *array, int size, int capacity)
{
    ValidateArray(array);

    array->data = malloc(sizeof(int) * capacity);
    array->size = &array->data[size];
    array->capacity = &array->data[capacity];
}

// Основные функции
void Resize(Array *array, int newSize) // O(N)
{
    if (newSize == GetSize(array))
    {
        return;
    }

    if (newSize > GetSize(array))
    {
        if (newSize > GetCapacity(array))
        {
            IncreaseCapacity(array, newSize);
        }

        for (size_t i = GetSize(array); i < newSize; i++)
        {
            array->data[i] = 0;
        }

        array->size = array->data + newSize;
    }
    else
    {
        array->size = array->data + newSize;
    }
}

void Initialize(Array *array) // O(1)
{
    const int additionalCapacity = 10;
    int newCapacity = GetSize(array) + additionalCapacity;

    array->data = realloc(NULL, sizeof(int) * newCapacity);
    array->capacity = array->data + newCapacity;    
}

int At(Array *array, int index) // O(1)
{
    if (index > GetCapacity(array))
    {
        IncreaseCapacity(array, index);
    }

    if (index > GetSize(array))
    {
        array->size = array->data + index;
    }
    
    return array->data[index];
}

void PushBack(Array *array, int value) // O(N)
{
    if (GetCapacity(array) <= GetSize(array)) 
    {
        const int elementsCount = 1;
        IncreaseCapacity(array, elementsCount);
    }

    array->data[GetSize(array)] = value;
    array->size++;
}

void Insert(Array *array, int index, int value) // O(N)
{   
    #pragma region Function // Дубляж, выдели функцию
    if (index > GetSize(array))
    {
        if (index > GetCapacity(array))
        {
            IncreaseCapacity(array, index);
        }
        
        array->size = array->data + index;
    }
    #pragma endregion

    #pragma region CoreLogic
    int currentElementValue = array->data[index];
    int nextElementValue = array->data[index + 1];

    for (size_t i = index; i < (GetSize(array) - index); i++)
    {
        array->data[i + 1] = currentElementValue;
        currentElementValue = nextElementValue;
        nextElementValue = array->data[i + 1];
    }

    array->data[index] = value;
    array->size++;
    #pragma endregion
}

void PopBack(Array *array) // O(1)
{
    if (GetSize(array) == 0)
    {
        return;
    }
    
    array->size--;
}

void Remove(Array *array, int index) // O(N)
{
    if (index > GetSize(array))
    {
        if (index > GetCapacity(array))
        {
            IncreaseCapacity(array, index);
        }

        array->size = array->data + index;
    }

    for (size_t i = index; i < GetSize(array); i++)
    {
        array->data[i] = array->data[i + 1];
    }

    array->size--;
}

void Clear(Array *array) // O(1)
{
    free(array->data);

    const int capacity = 10;
    array->data = malloc(sizeof(int) * capacity);
    array->size = array->data;
    array->capacity = array->data + capacity;
}

// Тесты
void TestResize()
{
    Array array;
    SetArrayPointers(&array, 5, 9);

    Resize(&array, 10);
    assert(GetSize(&array) == 10);
    assert(GetCapacity(&array) != 10);
    assert(array.data != NULL);

    free(array.data);
    printf("TestResize passed.\n");
}

void TestInitialize()
{
    Array array;
    SetArrayPointers(&array, 5, 10);

    Initialize(&array);
    assert(array.data != NULL);
    assert(GetCapacity(&array) >= 10);

    free(array.data);
    printf("TestInitialize passed.\n");
}

void TestAt()
{
    Array array;
    SetArrayPointers(&array, 5, 10);

    array.data[2] = 42;
    assert(At(&array, 2) == 42);
    
    free(array.data);
    printf("TestAt passed.\n");
}

void TestPushBack()
{
    Array array;
    SetArrayPointers(&array, 10, 10);

    PushBack(&array, 99);
    assert(array.data[GetSize(&array) - 1] == 99);
    assert(array.data != NULL);
    assert(GetCapacity(&array) > 10);
    assert(GetSize(&array) == 11);
    SetArrayPointers(&array, 0, 0);
    PushBack(&array, 1);
    assert(array.data != NULL);
    assert(GetSize(&array) == 1);
    assert(GetCapacity(&array) == 1);
    assert(array.data[0] == 1); 
    PushBack(&array, 2);
    assert(GetCapacity(&array) == 2);
    assert(GetSize(&array) == 2);
    assert(array.data != NULL);
    assert(array.data[1] == 2);

    free(array.data);
    printf("TestPushBack passed.\n");
}

void TestInsert()
{
    Array array;
    SetArrayPointers(&array, 5, 10);

    array.data[0] = 1;
    array.data[1] = 2;
    array.data[2] = 3;
    
    Insert(&array, 1, 99);
    assert(array.data[1] == 99);
    
    free(array.data);
    printf("TestInsert passed.\n");
}

void TestPopBack()
{
    Array array;
    SetArrayPointers(&array, 5, 10);

    PopBack(&array);
    assert(GetSize(&array) == 4); // Исправь хардкод

    free(array.data);
    printf("TestPopBack passed.\n");
}

void TestRemove()
{
    Array array;
    SetArrayPointers(&array, 5, 10);

    array.data[0] = 1;
    array.data[1] = 2;
    array.data[2] = 3;
    
    Remove(&array, 1);
    assert(array.data[1] == 3);
    assert(GetSize(&array) == 4); // Исправь хардкод

    free(array.data);
    printf("TestRemove passed.\n");
}

void TestClear()
{
    Array array;
    SetArrayPointers(&array, 5, 10);

    Clear(&array);
    assert(array.data != NULL);
    assert(GetSize(&array) == 0);
    assert(GetCapacity(&array) == 10);
    assert(GetSize(&array) == 0);

    free(array.data);
    printf("TestClear passed.\n");
}

void main()
{
    Array array;

    TestResize();
    TestInitialize();
    TestAt();
    TestPushBack();
    TestInsert();
    TestPopBack();
    TestRemove();
    TestClear();
    
    printf("все тесты пройдены!");
}