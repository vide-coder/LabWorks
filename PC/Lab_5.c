/*
  Необходимо для заданной строки написать функции, которые:

  1. Приводит заданную строку к написанию с заглавной буквы, т.е. для ввода "kolbasa" результат: "Kolbasa". Результат вывести на экран.
  2. Изменяет строку таким образом, чтобы все буквы в ней были заглавными, т.е. для ввода "kolbasa" результат: "KOLBASA". Результат вывести на экран.
  3. Изменяет строку таким образом, чтобы все буквы в ней были прописными, т.е. для ввода "KOLBASA" результат: "kolbasa". Результат вывести на экран.
  4. Определяет частоту повторения каждой буквы в строке.

  Пример ввода:  HeLLo
  Пример вывода: Hello HELLO hello
                 e 1 h 1 l 2 o 1

  Пользоваться стандартными функциями для манипуляции буферов и строк (из файла string.h и т.п.) не разрешается.
*/
#include <assert.h>
#include <stdio.h>              // Полностью скопированный код Никиты Матвея

char *capitalize(char *str)
{

    if (str[0] >= 'a' && str[0] <= 'z')
    {
        str[0] = str[0] - ('a' - 'A');
    }

    return str;
}
char *to_upper(char *str)
{

    for (size_t i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] -= ('a' - 'A');
        }
    }

    return str;
}
char *to_lower(char *str)
{

    for (size_t i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] += ('a' - 'A');
        }
    }

    return str;
}

void frequency(char *str, int count[])
{

    while (*str)
    {
        if ('a' <= *str && *str <= 'z')
        {
            count[*str - 'a']++;
        }
        else if ('A' <= *str && *str <= 'Z')
        {
            count[*str - 'A' + 26]++;
        }
        str++;
    }
}

int main()
{
    char str[20] = {0};

    int sizeOfWord = sizeof(str) / sizeof(str[0]);

    scanf("%s", str);

    printf("%s\n", capitalize(str));
    printf("%s\n", to_upper(str));
    printf("%s\n", to_lower(str));

    int count[52] = {};

    frequency(str, count);

    for (int i = 0; i < 52; i++)
    {
        if (count[i] > 0)
        {
            char c = i < 26 ? 'a' + i : 'A' + i - 26;
            printf("Символ '%c' встречается %d раз\n", c, count[i]);
        }
    }
    return 0;
}