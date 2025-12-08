#include <stdio.h>
#include <stdlib.h>

int all_good = 1;
int *arr = NULL;
int size = 0;

void input_mode();
void std_in();
void random_in();
void file_in();

void sort_mode();
void bubble_sort();
void selection_sort();

int main() {

    input_mode();
    if (!all_good) {
        if(arr) free(arr); 
        return 1;
    } 
    
    
    if(arr) free(arr); 
    return 0;
}

void input_mode() {
    int choice;

    printf("Choose sorting mode (1 - standard input, 2 - random, 3 - file): ");
    while(scanf("%d", &choice) != 1 || (choice != 1 && choice != 2 && choice != 3)) {
        printf("Choose 1,2 or 3: ");
        while (getchar() != '\n');
    }
    
    switch(choice) {
        case 1:
            std_in();
            break;
        case 2:
            random_in();
            break;
        case 3:
            file_in();
            break;
    } 
}
void std_in() {
    if (arr != NULL) {
        free(arr);
        arr = NULL;
    }
    size = 0;    
    char ch;


    printf("Enter the int numbers array: ");

    while(1) {

        arr = realloc(arr, (size + 1) * sizeof(int));
        if (arr == NULL) {
            printf("Memory allocation failed\n");
            all_good = 0;
            return;
        }

        scanf("%d", &arr[size]);
        size++;

        ch = getchar();
        if (ch == '\n' || ch == EOF) {
            break;
        } else if (ch != '\n' && ch != EOF && ch != ' ') {
            printf("n/a\n");
            if(arr) free(arr);
            all_good = 0;
            return;
        }
    }

    sort_mode();
}
void random_in() {
    char ch;

    if (arr != NULL) {
        free(arr);
        arr = NULL;
    }
    
    printf("Enter size of array: ");
    scanf("%d", &size);
    
    ch = getchar();
    if (ch != '\n' && ch != EOF) {
        printf("n/a\n");
        all_good = 0;
        return;
    }
    if (size <= 0) {
        printf("n/a\n");
        all_good = 0;
        return;
    }

    arr = malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
    printf("Array created succesfuly! Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    sort_mode();
}
void file_in() {
    if (arr != NULL) {
        free(arr);
        arr = NULL;
    }
    size = 0;
    char path[1000], buf[100];
    int num;

    printf("Enter path to file: ");
    scanf("%999s", path);
    
    FILE *file = fopen(path, "r");
    if (!file) {
        printf("n/a\n");
        all_good = 0;
        return;
    }

    while(1) {
        arr = realloc(arr, (size + 1) * sizeof(int));
        if (arr == NULL) {
            printf("Memory allocation failed\n");
            all_good = 0;
            return;
        }
        if(fscanf(file, "%d", &num) == 1) {
            arr[size++] = num;
        } else {
            if (fscanf(file, "%s", buf) != EOF) {
                printf("n/a\n");
                if(arr) free(arr); 
                all_good = 0;
                return;
            } else break;
        }
    }
    fclose(file);

    if (size == 0) {
        printf("n/a\n");
        all_good = 0;
        return;
    }

    printf("Array writed succesfuly! Array: "
    );
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i != size - 1) printf(" ");
        else printf("\n");
    }
    
    sort_mode();
}

void sort_mode() {
    int choice;

    printf("Choose sorting mode (1 - bubble sort or 2 - selection sort): ");
    while(scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
        printf("Choose 1 or 2: ");
        while (getchar() != '\n');
    }

    if (choice == 1) bubble_sort();
    else if (choice == 2) selection_sort();

    printf("Sorted array: ");

    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]); 
        if (i != size - 1) printf(" ");
    }
    printf("\n");
}
void bubble_sort() {
    int help;

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                help = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = help;
            }
        }
    }
}
void selection_sort() {
    int min, help ; 

    for (int i = 0; i < size - 1; i++) {
        min = i;

        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }

        if (min != i) {
            help = arr[i];
            arr[i] = arr[min];
            arr[min] = help;
        }
    }
}
