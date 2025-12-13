#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

#include "lab5.h"

static Graph* init_graph(char* path);
static Edge* create_node(int length, int vertex);
static void delete_node(Edge** head);
static void delete_linked_list(Edge** head);
static void free_all(Graph* graph);

static Graph* init_graph(char* path) {
    FILE *file = fopen(path, "rt");
    if (!file) {
        perror("fopen");
        return NULL;
    }

    int vertices_count, edge_count;
    if (fscanf(file, "%d %d", &vertices_count, &edge_count) != 2) {
        fprintf(stderr, "bad format\n");
        fclose(file);
        return NULL;
    }

#ifdef DEBUG
    printf("vertices: %d\nedges: %d\n", vertices_count, edge_count);
#endif

    Graph* graph = malloc(sizeof(Graph));
    if (!graph) {
        fclose(file);
        return NULL;
    }

    graph->vertices_count = vertices_count;
    graph->vertices = malloc(sizeof(Vertex) * vertices_count);
    if (!graph->vertices) {
        fclose(file);
        free(graph);
        return NULL;
    }
    
    for (int i = 0; i < vertices_count; i++) {
        graph->vertices[i].head = NULL;
    }

    for (int i = 0; i < edge_count; i++) {
        int from, to, length;
        if (fscanf(file, "%d %d %d", &from, &to, &length) != 3) {
            fprintf(stderr, "bad format\n");
            fclose(file);
            free_all(graph);
            return NULL;
        }
        Edge* tmp = create_node(length, to);
        if (!tmp) {
            fclose(file);
            free_all(graph);
            return NULL;
        }
        tmp->next = graph->vertices[from - 1].head;
        graph->vertices[from - 1].head = tmp;
    }

    fclose(file);
    return graph;
}
static Edge* create_node(int length, int vertex) {
    Edge* new_node = malloc(sizeof(Edge));
    if (!new_node) return NULL;

    new_node->length = length;
    new_node->vertex = vertex;
    new_node->next = NULL;

    return new_node;
}

static void delete_node(Edge** head) {
    if (head == NULL || *head == NULL) return;
    Edge* node_to_remove = *head;
    *head = node_to_remove->next;
    
    free(node_to_remove);
}
static void delete_linked_list(Edge** head) {
    while (*head != NULL) {
        delete_node(head);
    }
}
static void free_all(Graph* graph) {
    if (!graph) return;

    for (int i = 0; i < graph->vertices_count; i++) {
        delete_linked_list(&graph->vertices[i].head);
    }
    free(graph->vertices);
    free(graph);
}

static int dijkstra_alg(Graph* graph, int start, int finish) {
    if (!graph || !graph->vertices || graph->vertices_count <= 0) return -1;
    if (start < 1 || start > graph->vertices_count) return -1;
    if (finish < 1 || finish > graph->vertices_count) return -1;

    int node_count = graph->vertices_count;

    int *dist = malloc(sizeof(int) * node_count);
    if (!dist) return -1;

    char *used = calloc(node_count, sizeof(char));
    if (!used) {
        free(dist);
        return -1;
    }
    
    for (int i = 0; i < node_count; i++) dist[i] = INF;
    dist[start - 1] = 0;

    for (int iteration = 0; iteration < node_count; iteration++) {
        int closest_node = -1;

        for (int i = 0; i < node_count; i++) {
            if (used[i] || dist[i] >= INF) continue;

            if (closest_node == -1 || dist[i] < dist[closest_node])
                closest_node = i;
        }

        if (closest_node == -1) break;
        if (closest_node == finish - 1) break;

        used[closest_node] = 1;

        for (Edge* edge = graph->vertices[closest_node].head; edge != NULL; edge = edge->next) {
            int neighbor = edge->vertex - 1;
            int length = edge->length;
            
            if (length < 0) {
                free(dist);
                free(used);
                return -1;
            }
            
            int new_dist = dist[closest_node] + length;

            if (new_dist < dist[neighbor]) {
                dist[neighbor] = new_dist;
            }
        }
    }

    int result = (dist[finish - 1] >= INF) ? -1 : dist[finish - 1];

    free(dist);
    free(used);
    return result;
}
static int floydwarshal_alg(Graph* graph, int start, int finish) {
    if (!graph) return -1; // Защита от NULL
    int N = graph->vertices_count;
    
    if (start < 1 || start > N || finish < 1 || finish > N) return -1;

    int* matr = malloc(sizeof(int) * N * N);
    if (!matr) return -1;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) matr[i*N + j] = INF;
        
        for (Edge* e = graph->vertices[i].head; e != NULL; e = e->next)
            matr[i*N + (e->vertex - 1)] = e->length;
        
        matr[i*N + i] = 0; 
    }

    for (int k = 0; k < N; k++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                int ik = matr[i*N + k];
                int kj = matr[k*N + j];
                
                if (ik == INF || kj == INF) continue;
                
                int sum = ik + kj;
                if (matr[i*N + j] > sum) 
                    matr[i*N + j] = sum;
            }

    int result = matr[(start - 1)*N + (finish - 1)];
    free(matr);

    return (result >= INF) ? -1 : result;
}

int lab5(char* path) {
    Graph* graph = init_graph(path);
    int start = 2, finish = 7; 

    int D_ans = dijkstra_alg(graph, start, finish);
    int FW_ans = floydwarshal_alg(graph, start, finish);
    if (D_ans == -1 || FW_ans == -1) {
        printf("n/a\n");
        return 1;
    }

    printf("Dijkstra alg answer: %d\n", D_ans);
    printf("Floyd–Warshall alg answer: %d\n", FW_ans);
    
    free_all(graph);
    return 0;
}