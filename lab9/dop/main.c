#include "graph.h"

Graph* input_graph();
int input_vertices(int* start, int* end, int max_vertices);

int main() {
    Graph* graph = input_graph();
    if (!graph) {
        printf("Graph creation error!\n");
        return 1;
    }
    
    print_graph(graph);
    
    int start, end;
    if (!input_vertices(&start, &end, graph->vertices)) {
        free(graph);
        return 1;
    }
    
    printf("\nSearching for shortest path...\n");
    PathResult result = find_shortest_path(graph, start, end);
    
    print_path_result(result, start, end);
    
    free(graph);
    
    return 0;
}