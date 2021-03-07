#ifndef AM_Graph
#define AM_Graph

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

#define MAX_VERTEX_NUM 20
#define INFINITY 32768

typedef enum {DG,DN,UDG,UDN}GraphKind;
typedef enum {NotAdj,Adj}AdjType;
typedef char VertexData;
typedef struct ArcNode
{
    AdjType adj;
}ArcNode;

typedef struct Graph
{
    VertexData VX[MAX_VERTEX_NUM];
    ArcNode ArcNode_Matrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int VertexNum,ArcNum;
    GraphKind Kind;
}MatrixGraph;

extern void Create_AMGraph(Graph *G,const VertexData VXList[],const VertexData AdjastVXChart[][],const int vxnum,const GraphKind kind);
extern int Locate_AMNode(Graph *G,VertexData VX);
extern void Traverse_AMGraph(Graph *G);
extern void Add_AMNode(Graph *G,VertexData NodeData);
extern void Delete_AMNode(Graph *G,VertexData NodeData);
extern void Add_AMArc(Graph *G,VertexData Head,VertexData Tail);
extern void Delete_AMArc(Graph *G,VertexData Head,VertexData Tail);
#endif