#ifndef AL_Graph
#define AL_Graph

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>

#define MAX_VERTEX_NUM   20
#define INFINITY         32768
#define VERTEX_NUM       5

typedef enum {DG,DN,UDG,UDN}GraphKind;
typedef char VertexData;

typedef struct VertexNode
{
    VertexData VD;
    struct ArcNode *FirstAdj;
}VertexNode,*VertexPointer;

typedef struct ArcNode
{
    int ArcNodeIndex;
    VertexData AVD;
    struct ArcNode *NextAdj;
}ArcNode,*ArcNodePointer; 

typedef struct Graph
{
    VertexNode Vertex[MAX_VERTEX_NUM];
    int VertexNum,ArcNum;
    GraphKind Kind;
}Graph,ALGraph;

extern void Create_ALGraph(Graph *G,const VertexData VXList[],const VertexData AdjastVXChart[][VERTEX_NUM],const int vxnum,const GraphKind kind);
extern int Locate_ALNode(Graph *G,VertexData VX);
extern void Traverse_ALGraph(Graph *G);
extern void Add_ALNode(Graph *G,VertexData NodeData);
extern void Delete_ALNode(Graph *G,VertexData NodeData);
extern void Add_ALArc(Graph *G,VertexData Head,VertexData Tail);
extern void Delete_ALArc(Graph *G,VertexData Head,VertexData Tail);
extern void Destroy_ALGraph(Graph *G);
#endif