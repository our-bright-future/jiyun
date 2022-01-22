#include <stdio.h>
#include <stdlib.h>

struct Graph;
struct Vertex;
struct Edge;
struct Inc;

typedef struct Vertex { // 정점 노드
    int v;
    struct Vertex *link;
    struct Inc *header;
} Vertex;

typedef struct Edge { // 간선 노드
    int u;
    int v;
    int weight;
    struct Edge *link;
} Edge;

typedef struct Inc { // 부착 간선 -한 정점에 연결된 간선- 노드
    struct Edge *edge;
    struct Inc *link;
} Inc;

typedef struct Graph {
    Vertex *vertex; // 정점 노드 배열
    Edge *edge; // 간선 노드 배열
} Graph;

Vertex *getVertexNode();
Edge *getEdgeNode();
Inc *getIncNode();

Vertex *getVertex(Graph *g, int v);
Edge *getEdge(Graph *g, int u, int v);
Edge *getPrevEdge(Graph *g, int u, int v);
int getDesVertex(int v, Edge *e);

Graph *creatGraph();
void insertVertex(Graph *g, int v);
void insertEdge(Graph *g, int u, int v, int weight);
void insertInc(Graph *g, int u, int v);
void deleteVertex(Graph *g, int v);
void deleteEdge(Graph *g, int u, int v);
void deleteInc(Graph *g, Vertex *v_node, Edge *e_node);

void searchVertexAndPrintEdges(Graph *g);
void searchEdgeAndFixWeight(Graph *g);

void freeGraph(Graph *g);

Graph *creatGraph() {
    Graph *g = malloc(sizeof(Graph));
    if (g == NULL) {return NULL;}

    g -> vertex = g -> edge = NULL;
    return g;
}

Vertex *getVertexNode() {
    Vertex *vtx = malloc(sizeof(Vertex));
    if (vtx == NULL) {return NULL;}
    vtx -> link = vtx -> header = NULL;
    
    return vtx;
}

Edge *getEdgeNode() {
    Edge *e = malloc(sizeof(Edge));
    if (e == NULL) {return NULL;}
    e -> link = NULL;

    return e;
}

Inc *getIncNode() {
    Inc *i = malloc(sizeof(Inc));
    if (i == NULL) {return NULL;}
    i -> edge = i -> link = NULL;

    return i;
}

void insertVertex(Graph *g, int v) {
    Vertex *vx = getVertexNode();
    vx -> v = v;
    vx -> link = vx -> header = NULL;
    
    if (g -> vertex == NULL){ // 비어있을 때
        g -> vertex = vx;
    } else { // 안비어있을 때
        Vertex *curr = g -> vertex;
        while (curr -> link != NULL) {
            curr = curr -> link;
        }
        curr -> link = vx;
    }
}

void insertInc(Graph *g, int u, int v) {
    Inc *i = getIncNode();
    
}

void insertEdge(Graph *g, int u, int v, int weight) {
    Edge *e = getEdgeNode();
    e -> u = u;
    e -> v = v;
    e -> weight = weight;

    Vertex *curr = g -> vertex;
    while (curr -> link != NULL) {
        if (curr -> v == u) {
            insertInc(g, u, v);
        }
        curr = curr -> link;
    }
    // 일치하는 정점이 리스트 마지막에 있을 경우
    if (curr -> v == u) {
        insertInc(g, u, v);
    }

    if(g -> edge == NULL) {
        g -> edge = e;
        e -> link = NULL;
    } else {
    }
    
}

int main() {
    Graph *g = creatGraph();

    insertVertex(g, 1);
    insertVertex(g, 2);
    insertVertex(g, 3);
    insertVertex(g, 4);
    insertVertex(g, 5);
    insertVertex(g, 6);

    insertEdge(g, 1, 2, 1);
    insertEdge(g, 1, 3, 1);
    insertEdge(g, 4, 1, 1);
    insertEdge(g, 2, 3, 1);
    insertEdge(g, 1, 6, 2);
    insertEdge(g, 5, 6, 3);
    insertEdge(g, 3, 5, 4);
    insertEdge(g, 5, 5, 4);
    
}