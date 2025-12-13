#ifndef LAB4_H
#define LAB4_H

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

int lab4(char* path);

#endif