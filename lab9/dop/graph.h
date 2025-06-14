#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF INT_MAX

typedef struct {
    int vertices;
    int adjacency_matrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

typedef struct {
    int distance;
    int path[MAX_VERTICES];
    int path_length;
    int found;
} PathResult;

Graph* create_graph(int vertices);
void print_graph(Graph* graph);
PathResult find_shortest_path(Graph* graph, int start, int end);
void print_path_result(PathResult result, int start, int end);

#endif