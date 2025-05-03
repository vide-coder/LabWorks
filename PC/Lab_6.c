#include <stdio.h>
#include <stdlib.h>
#include <string.h>                     // Полностью скопированный код Никиты Матвея
                                 
typedef char* string;

struct date {
    unsigned int days;
    unsigned int months;
    unsigned int years;
};

struct record {
    char name[30];
    char surname[30];
    struct date birthday;
};

int main(void) {
    size_t count = 0;
    printf("Enter the number of records: ");
    scanf("%zu", &count);

    struct record* table = malloc(sizeof(struct record) * count);
    if (table == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (size_t i = 0; i < count; ++i) {
        printf("Enter name: ");
        scanf("%29s", table[i].name);
        if (strpbrk(table[i].name, "0123456789!@#$%^&*()_+-=~`[]{}|;:'\",.<>?/\\ \t\n") != NULL) {
            printf("Invalid name. Please enter a valid name.\n");
            i--;
            count--;
            continue;
        }

        printf("Enter surname: ");
        scanf("%29s", table[i].surname);
        if (strpbrk(table[i].surname, "0123456789!@#$%^&*()_+-=~`[]{}|;:'\",.<>?/\\ \t\n") != NULL) {
            printf("Invalid surname. Please enter a valid surname.\n");
            i--;
            count--;
            continue;
        }

        printf("Enter birthday dd mm yyyy: ");
        scanf("%u %u %u", &table[i].birthday.days, &table[i].birthday.months, &table[i].birthday.years);
    }


    table = realloc(table, sizeof(struct record) * count);

    printf("\nValid records:\n");
    for (size_t i = 0; i < count; i++) {
        printf("Name: %s, Surname: %s, Birthday: %02u/%02u/%04u\n",
               table[i].name, table[i].surname,
               table[i].birthday.days, table[i].birthday.months, table[i].birthday.years);
    }


    return 0;
}