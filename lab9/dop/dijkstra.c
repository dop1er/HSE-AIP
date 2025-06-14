#include "graph.h"

int min_distance(int dist[], int visited[], int vertices) {
    int min = INF;
    int min_index = -1;
    
    for (int v = 0; v < vertices; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    
    return min_index;
}

void reconstruct_path(int parent[], int start, int end, int path[], int* path_length) {
    if (end == -1) {
        *path_length = 0;
        return;
    }
    
    int temp_path[MAX_VERTICES];
    int temp_length = 0;
    int current = end;
    
    while (current != -1) {
        temp_path[temp_length++] = current;
        current = parent[current];
    }
    
    *path_length = temp_length;
    for (int i = 0; i < temp_length; i++) {
        path[i] = temp_path[temp_length - 1 - i];
    }
}

PathResult find_shortest_path(Graph* graph, int start, int end) {
    PathResult result;
    result.found = 0;
    result.distance = INF;
    result.path_length = 0;
    
    if (start < 0 || start >= graph->vertices || 
        end < 0 || end >= graph->vertices) {
        return result;
    }
    
    int dist[MAX_VERTICES];
    int visited[MAX_VERTICES];
    int parent[MAX_VERTICES];
    
    for (int i = 0; i < graph->vertices; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }
    
    dist[start] = 0;
    
    for (int count = 0; count < graph->vertices - 1; count++) {
        int u = min_distance(dist, visited, graph->vertices);
        
        if (u == -1) break;
        
        visited[u] = 1;
        
        for (int v = 0; v < graph->vertices; v++) {
            if (!visited[v] && 
                graph->adjacency_matrix[u][v] > 0 &&
                dist[u] != INF &&
                dist[u] + graph->adjacency_matrix[u][v] < dist[v]) {
                
                dist[v] = dist[u] + graph->adjacency_matrix[u][v];
                parent[v] = u;
            }
        }
    }
    
    if (dist[end] != INF) {
        result.found = 1;
        result.distance = dist[end];
        reconstruct_path(parent, start, end, result.path, &result.path_length);
    }
    
    return result;
}

void print_path_result(PathResult result, int start, int end) {
    if (!result.found) {
        printf("\nPath from vertex %d to vertex %d not found!\n", start, end);
        return;
    }
    
    printf("\nShortest path from vertex %d to vertex %d:\n", start, end);
    printf("Path: ");
    
    for (int i = 0; i < result.path_length; i++) {
        printf("%d", result.path[i]);
        if (i < result.path_length - 1) {
            printf(" -> ");
        }
    }
    
    printf("\nPath length: %d\n", result.distance);
}