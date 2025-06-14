#include "graph.h"

Graph* input_graph() {
    int vertices;
    
    printf("Enter the number of vertices in the graph (maximum %d): ", MAX_VERTICES);
    if (scanf("%d", &vertices) != 1 || vertices <= 0 || vertices > MAX_VERTICES) {
        printf("Error: invalid number of vertices!\n");
        return NULL;
    }
    
    Graph* graph = create_graph(vertices);
    if (!graph) {
        return NULL;
    }
    
    printf("\nInputting %dx%d adjacency matrix:\n", vertices, vertices);
    printf("Enter the matrix row by row (0 - no edge, positive number - edge weight):\n");
    printf("Vertices are numbered from 0 to %d\n\n", vertices - 1);
    
    for (int i = 0; i < vertices; i++) {
        printf("Row %d (from vertex %d): ", i, i);
        for (int j = 0; j < vertices; j++) {
            if (scanf("%d", &graph->adjacency_matrix[i][j]) != 1) {
                printf("Input error! Try again.\n");
                while (getchar() != '\n');
                j--;
                continue;
            }
            
            if (graph->adjacency_matrix[i][j] < 0) {
                printf("Error: edge weight cannot be negative! Enter again: ");
                j--;
                continue;
            }
            
            if (i == j && graph->adjacency_matrix[i][j] != 0) {
                printf("Warning: distance from vertex to itself set to 0\n");
                graph->adjacency_matrix[i][j] = 0;
            }
        }
    }
    
    return graph;
}

int input_vertices(int* start, int* end, int max_vertices) {
    printf("\nEnter start vertex (0-%d): ", max_vertices - 1);
    if (scanf("%d", start) != 1 || *start < 0 || *start >= max_vertices) {
        printf("Error: invalid start vertex!\n");
        return 0;
    }
    
    printf("Enter end vertex (0-%d): ", max_vertices - 1);
    if (scanf("%d", end) != 1 || *end < 0 || *end >= max_vertices) {
        printf("Error: invalid end vertex!\n");
        return 0;
    }
    
    return 1;
}