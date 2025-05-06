#include <stdio.h>
#include "enhanced_hypercube.h"

int main (int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <n> <k>\n", argv[0]);
        return 1; // exit with error
    }

    int n = atoi(argv[1]);
    int k = atoi(argv[2]);

    printf("n = %d, k = %d\n", n, k);
    graph_t* graph = new_graph(n, k);
    int size = graph->size;
    printf("size: %d\n", size);
    
    set_faults_for_test(graph);
    for (int i = 0; i < size; ++i) {
        printf("node %d: %d\n", i, graph->nodes[i]->faulty);
    }

    // testing
    uint32_t id = 21, i;
    for (int j = 0; j <= n; ++j) {
        if (j < n) {    // hypercube edges
            i = id ^ (1 << j);
            printf("hypercube edge: ");
        }
        else {          // skip 
            i = id ^ SKIP_MASK(k);
            printf("skip: ");
        }
        int result = test(graph, id, i);
        printf("(%u, %u) = %d\n", id, i, result);
    }

    free(graph);
    return 0;
}
