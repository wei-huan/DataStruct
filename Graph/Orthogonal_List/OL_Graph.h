#ifndef OL_Graph
#define OL_Graph

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTEX_NUM    20
#define INFINITY        32678

typedef char VertexData;
typedef enum {DG,DN,UDG,UDN}GraphKind;

typedef struct ArcNode
{
    int TailVexIndex,HeadVexIndex;
    struct ArcNode* SameHeadArc,SameTailArc;
}ArcNode;

typedef struct Vertex
{
    VertexData VD;
    ArcNode* FirstInHeadArc;
    ArcNode* FirstOutTailArc;
}Vertex;

typedef struct Graph
{
    Vertex Vertex[MAX_VERTEX_NUM];
    int VertexNum,ArcNum;
    GraphKind Kind;
}OL_Graph;

extern void Creat_OLGraph(Graph* G,);
extern void Traverse_OLGraph(Graph *G);
extern void Add_OLNode(Graph *G,VertexData NodeData);
extern void Delete_OLNode(Graph *G,VertexData NodeData);
extern void Add_OLArc(Graph *G,VertexData Head,VertexData Tail);
extern void Delete_OLArc(Graph *G,VertexData Head,VertexData Tail);
extern void Delete_OLGraph(Graph* G);
#endif