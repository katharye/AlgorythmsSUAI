#ifndef LAB5_H
#define LAB5_H

typedef struct Edge {
    int length;
    int vertex;
    struct Edge* next; 
} Edge;

typedef struct Vertex {
    Edge* head;
} Vertex;

typedef struct Graph{
    Vertex* vertices;
    int vertices_count;
} Graph;

// #define DEBUG
#define INF INT_MAX / 2

int lab5(char* path);

#endif