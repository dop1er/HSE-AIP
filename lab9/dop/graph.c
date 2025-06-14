#include "graph.h"

Graph* create_graph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) {
        printf("Memory allocation error!\n");
        return NULL;
    }
    
    graph->vertices = vertices;
    
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjacency_matrix[i][j] = 0;
        }
    }
    
    return graph;
}

void print_graph(Graph* graph) {
    printf("\nEntered adjacency matrix:\n");
    printf("    ");
    for (int i = 0; i < graph->vertices; i++) {
        printf("%4d", i);
    }
    printf("\n");
    
    for (int i = 0; i < graph->vertices; i++) {
        printf("%2d: ", i);
        for (int j = 0; j < graph->vertices; j++) {
            if (graph->adjacency_matrix[i][j] == 0 && i != j) {
                printf("   -");
            } else {
                printf("%4d", graph->adjacency_matrix[i][j]);
            }
        }
        printf("\n");
    }
}