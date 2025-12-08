#include <stdlib.h>
#include <stdio.h>

#define true 1
#define false 0

struct Trunk {
    struct Trunk* prev;
    char* str;
};

struct Node {     
    int key;            
    struct Node* left;  
    struct Node* right; 
};

struct Node* createNode(int key);
struct Node* insertNode(struct Node* root, int key); 
void deleteLeavesAtLevel(struct Node** root, int targetLevel, int currentLevel); 
void showTrunks(struct Trunk* p);
void printTree(struct Node* root, struct Trunk* prev, int isLeft);
void freeTree(struct Node** root);

int main() {
    struct Node* root = NULL;
    int key;
    FILE *file;

    file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Ошибка открытия файла input.txt\n");
        return 1;
    }
    
    printf("Чтение данных из файла...\n");
    while (fscanf(file, "%d", &key) != EOF) {
        root = insertNode(root, key);
    }
    fclose(file);

    printf("Исходное дерево:\n");
    printTree(root, NULL, 0);
    printf("\n");

    int level;
    printf("Введите уровень, на котором нужно удалить листья (корень = 0): ");
    if (scanf("%d", &level) != 1) {
        printf("Ошибка ввода.\n");
        freeTree(&root);
        return 1;
    }

    printf("\nУдаление листьев на уровне %d...\n", level);
    deleteLeavesAtLevel(&root, level, 0);

    printf("Дерево после удаления:\n");
    printTree(root, NULL, 0);
    printf("\n");

    freeTree(&root);

    return 0;
}

void deleteLeavesAtLevel(struct Node** root, int targetLevel, int currentLevel) {
    if (*root != NULL) {
        if (currentLevel == targetLevel) {
            if ((*root)->left == NULL && (*root)->right == NULL) {
                free(*root);   
                *root = NULL;  
            }
        } else {
            deleteLeavesAtLevel(&(*root)->left, targetLevel, currentLevel + 1);
            deleteLeavesAtLevel(&(*root)->right, targetLevel, currentLevel + 1);
        }

    }
}

struct Node* insertNode(struct Node* root, int key) {
    if (root == NULL) {
        root =  createNode(key);
    } else if (key < root->key) {
        root->left = insertNode(root->left, key);
    } else if (key > root->key) {
        root->right = insertNode(root->right, key);
    }
    return root;
}

struct Node* createNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeTree(struct Node** root) {
    if (*root != NULL) {   
        freeTree(&(*root)->left);
        freeTree(&(*root)->right);
        free(*root);
        *root = NULL;
    }
}




void showTrunks(struct Trunk* p) {
    if (p == NULL) {
        return;
    }

    showTrunks(p->prev);
    printf("%s", p->str);
}

void printTree(struct Node* root, struct Trunk* prev, int isLeft) {
    if (root == NULL) {
        return;
    }

    char* prev_str = "     ";

    struct Trunk* trunk = (struct Trunk*)malloc(sizeof(struct Trunk)); 
    trunk->prev = prev;
    trunk->str = prev_str;

    printTree(root->right, trunk, true);
    if (!prev) {
        trunk->str = "-----";
    }
    else if (isLeft)
    {
        trunk->str = ".----";
        prev_str = "    |";
    }
    else {
        trunk->str = "----";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    printf(" %d\n", root->key);

    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "    |";

    printTree(root->left, trunk, false);
    free(trunk);
}