#include <stdio.h>
#include <stdlib.h>

#include "lab1/lab1.h"
#include "lab2/lab2.h"

void clear();
void print_quest(char* filename);

int main() {
    clear();
    printf("Choose number of lab work:\n1 - lab1\n2 - lab2\n  \n");
    int lab_num;
    if (scanf("%d", &lab_num) != 1) {
        printf("n/a\n");
        return 1;
    }

    switch (lab_num) {
    case 1:
        char filename[256];

        clear();
        print_quest("lab1/quest.txt");

        printf("Enter file name: ");
        scanf("%s", &filename);
        lab1(filename);
        break;
    case 2:
        clear();
        print_quest("lab2/quest.txt");

        lab2();
        break;

    default:
        printf("Incorrect number!\n");
        return 1;
    }
    
    
    printf("\n\nCheck another lab? (Y, n)");
    
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