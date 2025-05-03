#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int isize = 0;
    scanf("%i", &isize);

    const size_t count = isize;

    int array[count];

    for (size_t i = 0; i < count; i++)
    {
        scanf("%i", array + i);
    }

    int arraySize = sizeof(array) / sizeof(*array);

    for (int i = 0; i < arraySize - 1; i++)
    {
        for (int j = (arraySize - 1); j > i; j--)
        {
            if (array[j - 1] < array[j])
            {
                int temp = array[j - 1];
                array[j - 1] = array[j];
                array[j] = temp;
            }
        }
    }

    for (size_t i = 0; i < arraySize; i++)
    {
        printf("%d ", array[i]);
    }

    // Задание 2
    int maxChainSize = 0;

    size_t chainFirstElementIndex = 0;
    scanf("%zu", &chainFirstElementIndex);
    const size_t r = chainFirstElementIndex;

    for (size_t i = 0; i < arraySize - 1; i++)
    {
        if (array[i] == array[i + 1])
        {
            int chainSize = 2;

            if (i + chainSize > arraySize)
            {
                return 0;
            }

            while (array[i] == array[i + chainSize])
            {
                chainSize++;
            }

            if (chainSize > maxChainSize)
            {
                maxChainSize = chainSize;
                chainFirstElementIndex = i;
                i += ++chainSize;
            }
        }
    }

    assert(r == chainFirstElementIndex);

    return 0;
}