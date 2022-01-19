/* 방향 그래프,
배열 이용,
동적 할당으로 진행 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

typedef struct graph {
    int nodes;
    bool **edges;
} graph;

graph *create_graph (int num_nodes) {
    graph *g = malloc(sizeof(graph));
    if (g == NULL) {return NULL;}

    g -> nodes = num_nodes;

    //allocate our matrix
    g -> edges = calloc(sizeof(bool *), g -> nodes);
    if (g -> edges == NULL) {
        free(g);
        return NULL;
    }
    for (int from=0; from < g -> nodes; from++) {
        g -> edges[from] = calloc(sizeof(bool), g -> nodes);
        if (g -> edges[from] == NULL) {
            destroy_graph(g);
            return NULL;
        }
    }
    return g;
}

void destoy_graph(graph *g) {
    if (g -> edges == NULL) {
        return ;
    }
    for(int from=0; from < g -> nodes; from++) {
        if (g -> edges[from] != NULL) {
            free(g -> edges[from]);
        }
    }
    free(g -> edges);
    free(g);
}

void print(graph *g) {
    printf("digraph {\n");

    for(int from=0; from < g -> nodes; from++) {
        for(int to=0; to < g -> nodes; to++) {
            if (g -> edges[from][to]) {
                printf("%d -> %d;\n", from, to);
            }
        }
    }
    printf("}\n");
}

bool add_edge(graph *g, unsigned int from_node, unsigned int to_node) {
    if (has_edge(g, from_node, to_node)) {
        return false;
    }
    g -> edges[from_node][to_node] = true;
    return true;
}

bool has_edge(graph *g, unsigned int from_node, unsigned int to_node) {
    assert(g != NULL);
    assert(from_node < g -> nodes);
    assert(to_node < g -> nodes);

    return g -> edges[from_node][to_node];
}

int main() {
    graph *g1 = create_graph(5);

    add_edge(g1, 0, 1);
    .
    .
    .

    print(g1);

    destoy_graph(g1);
}
