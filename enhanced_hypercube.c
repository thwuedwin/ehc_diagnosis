#include "enhanced_hypercube.h"

graph_t* new_graph (int n, int k) {
    if (n <= 0) {
        fprintf(stderr, "Error: n should larger than 0\n");
        exit(EXIT_FAILURE);
    }
    if (k > n || k <= 1) {
        fprintf(stderr, "Error: k should be integer between 1 and n\n");
        exit(EXIT_FAILURE);
    }
    graph_t* graph = malloc(sizeof(graph_t));
    graph->n = n;
    graph->k = k;
    graph->size = 1 << n;
    graph->nodes = malloc(sizeof(node_t) * graph->size);
    for (uint32_t i = 0; i < graph->size; ++i) {
        graph->nodes[i] = new_node(i);
    }

    return graph;
}
node_t* new_node (uint32_t id) {
    node_t* node = malloc(sizeof(node_t));
    node->id = id;
    node->faulty = false;
    return node;
}
void free_graph(graph_t* graph) {
    for (uint32_t i = 0; i < graph->size; ++i) {
        free(graph->nodes[i]);
    }
    free(graph);
}

void set_faults (graph_t* graph, int n) {
    srand(time(NULL));
    if (n > graph->size) {
        fprintf(stderr, "Error: number of faulty nodes (%d) exceeds total number of nodes (%d)\n", n, graph->size);
        exit(EXIT_FAILURE);
    }

    while(n) {
        int i = rand() % graph->size;
        if (!graph->nodes[i]->faulty) {
            graph->nodes[i]->faulty = true;
            --n;
        }
    }
}


// return 0 is tester evaluate testee to be fault-free, otherwise 1.
// The result is reliable when tester is fault-free.
int test(graph_t* graph, uint32_t tester, uint32_t testee) {
    if (tester >= graph->size || testee >= graph->size) {
        fprintf(stderr, "Error: index of nodes out of range\n");
        exit(EXIT_FAILURE);
    }
    if (!is_adjacent(tester, testee)) {
        fprintf(stderr, "Error: tester and testee is not adjacent\n");
        exit(EXIT_FAILURE);
    }
    int result;
    node_t *tester_node = graph->nodes[tester],
           *testee_node = graph->nodes[testee];
    if (!tester_node->faulty) {
        result = testee_node->faulty;
    } else {
        // If tester is faulty, the result is not reliable.
        result = rand() % 2;
    }

    return result;
} 

bool is_adjacent(uint32_t tester, uint32_t testee) {
    // check if adjacent
    return true;
}

// For testing
void set_faults_for_test(graph_t *graph) {
    graph->nodes[1]->faulty = true;
    graph->nodes[5]->faulty = true;
    graph->nodes[8]->faulty = true;
    graph->nodes[16]->faulty = true;
    graph->nodes[23]->faulty = true;
    graph->nodes[24]->faulty = true;
}
