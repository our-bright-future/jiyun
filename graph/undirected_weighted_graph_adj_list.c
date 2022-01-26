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
void insertInc(Graph *g, int u, int v, int weight);
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
        vx -> link = curr -> link;
        curr -> link = vx;
    }
}

void insertInc(Graph *g, int u, int v, int weight) {
    Inc *i = getIncNode();
    i -> edge -> u = u;
    i -> edge -> v = v; 
    i -> edge -> weight = weight;
    i -> link = NULL;

    Vertex *vxcurr = g -> vertex;
    while (vxcurr -> link != NULL) {
        if (vxcurr -> v == u) {
            if (vxcurr -> header == NULL) { //Inc가 아직 없을 때
                vxcurr -> header = i;
            } else {
                Inc *iccurr = vxcurr -> header;
                while (iccurr -> link != NULL) {
                    if ((iccurr -> edge -> v) < v && (iccurr -> link -> edge -> v) > v) {
                        break ;
                    }
                    iccurr = iccurr -> link;
                }
                i -> link = iccurr -> link;
                iccurr -> link = i;
            }
        }
        vxcurr = vxcurr -> link;
    }
    // 일치하는 정점이 리스트 마지막에 있을 경우
    if (vxcurr -> header == NULL) { //Inc가 아직 없을 때
        vxcurr -> header = i;
    } else {
        Inc *iccurr = vxcurr -> header;
        while (iccurr -> link != NULL) {
            if ((iccurr -> edge -> v) < v && (iccurr -> link -> edge -> v) > v) {
                break ;
            }
            iccurr = iccurr -> link;
        }
        i -> link = iccurr -> link;
        iccurr -> link = i;
    }
}

void insertEdge(Graph *g, int u, int v, int weight) {
    Edge *e = getEdgeNode();
    e -> u = u;
    e -> v = v;
    e -> weight = weight;
    e -> link = NULL;

    if(g -> edge == NULL) {
        g -> edge = e;
    } else {
        Edge *curr = g -> edge;
        while (curr -> link != NULL) {
            curr = curr -> link;
        }
        e -> link = curr -> link;
        curr -> link = e;
    }
    // 자 이제 해당 간선과 연관된 인접리스트를 설정해보자
    insertInc(g, u, v, weight);
}

/* 정점을 delete할 때 연관된 edge나 inc를 먼저 삭제(free)해야하는 것 아닌가?!???!!!!!??!!? 
-> 맞음!!!!! 대신 그렇게 했을 때 수행 성능이 저하되므로 '비활성화' 방식을 택할 수도 있다 (어떻게.. 하는데..) */
void deleteVertex(Graph *g, int v) {
    Vertex *vxCurr = g -> vertex;
    // 지우고자 하는 타겟 정점이 첫 번째 정점일 때
    if (vxCurr -> v == v) {
        Edge *eCurr = g -> edge;
        while (eCurr -> link) {
            if (eCurr -> u == v) {
                break ;
            }
            eCurr = eCurr -> link;
        }
        deleteEdge(g, eCurr -> u, eCurr -> v); // 노드 포인터를 전달하는게 낫지 않나
        deleteInc(g, vxCurr, eCurr);

        g -> vertex = vxCurr -> link;
        free(vxCurr);
        return ;
    }
    // 그 외
    while (vxCurr -> link -> link != NULL) {
        if (vxCurr -> link -> v == v) {
            break ;
        }
        vxCurr = vxCurr -> link;
    }
    Edge *eCurr = g -> edge;
    while (eCurr -> link) {
        if (eCurr -> u == v) {
            break ;
        }
        eCurr = eCurr -> link;
    }
    deleteEdge(g, eCurr -> u, eCurr -> v);
    deleteInc(g, vxCurr, eCurr);

    vxCurr -> link = vxCurr -> link -> link;
    free(vxCurr);
    return ;
}

void deleteEdge(Graph *g, int u, int v) {

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
