#include <stdio.h>
#include <stdlib.h>

#include "lab1/lab1.h"
#include "lab2/lab2.h"
#include "lab3/lab3.h"
#include "lab4/lab4.h"
#include "lab5/lab5.h"


void clear();
void print_quest(char* filename);

int main() {
    clear();
    printf("Choose number of lab work:\n");
    printf("  1 - Основы работы с консольным приложением и синтаксический разбор текста\n");
    printf("  2 - Сортировка одномерных массивов\n");
    printf("  3 - Линейные списки\n");
    printf("  4 - Двоичные деревья поиска\n");
    printf("  5 - Поиск кратчайших путей в ориентированном взвешенном графе\n");
    printf("\n");
    
    int lab_num;
    if (scanf("%d", &lab_num) != 1) {
        printf("n/a\n");
        return 1;
    }

    switch (lab_num) {
    case 1:
        char filename[256];

        clear();
        print_quest("src/lab1/quest.txt");

        printf("Enter file name: ");
        scanf("%255s", filename);
        lab1(filename);
        break;
    case 2:
        clear();
        print_quest("src/lab2/quest.txt");

        lab2();
        break;
    case 3:
        clear();
        print_quest("src/lab3/quest.txt");

        lab3();
        break;
    case 4:
        clear();
        print_quest("src/lab4/quest.txt");

        lab4("src/lab4/input.txt");
        break;
    case 5:
        clear();
        print_quest("src/lab5/quest.txt");

        lab5("src/lab5/graph.txt");
        break;
    default:
        printf("Incorrect number!\n");
        return 1;
    }
    

    printf("\n\nCheck another lab? (1 - Yes)\n");
    int answer;
    if (scanf("%d", &answer) != 1) {
        return 0;
    }
    if (answer == 1) main();
}

void clear() {
#ifdef _WIN32
    system("cls");
#else 
    system("clear");
#endif
}

void print_quest(char* filename) {
    FILE *file = fopen(filename, "rt");
    char buffer[1000];
    printf("\033[93m");
    printf("--==QUEST==--\n");
    while (fgets(buffer, 1000, file)) {
        printf("%s", buffer);
    }
    printf("\n--=========--\n\n");
    printf(reset);
}