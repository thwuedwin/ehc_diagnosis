#ifndef ENHANCED_HYPERCUBE_H
#define ENHANCED_HYPERCUBE_H
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
typedef struct node {
    uint32_t id;
    bool faulty;
} node_t;

typedef struct graph {
    int n;
    int k;
    int size;
    node_t **nodes;
} graph_t;

graph_t* new_graph (int n, int k);
node_t* new_node (uint32_t id);
void free_graph(graph_t* graph);

void set_faults(graph_t* graph, int n);
void set_faults_for_test(graph_t* graph);

// #define list_for_each(node, head) \
//     for (node = (head)->next; node != (head); node = node->next)
#define for_each_hypercube_edge(id, n, i) \
    for (int __j = 0; __j < (n) && ((i) = (id) ^ (1 << __j), 1); ++__j)

#define SKIP_MASK(k) ((1 << k) - 1)

int test(graph_t* graph, uint32_t tester, uint32_t testee);
bool is_adjacent(uint32_t tester, uint32_t testee);
#endif
