#ifndef OL_Graph
#define OL_Graph

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTEX_NUM    20
#define INFINITY          32678
#define VERTEX_NUM        5

typedef char VertexData_Type;
typedef int  ArcWeight_Type;
typedef enum {Yes,No}SearchMark_Type;
typedef enum {DG,DN,UDG,UDN,NotSet}GraphKind_Type;

typedef struct ArcNode{
    SearchMark_Type SM;
    ArcWeight_Type AW;
    int TailVexIndex,HeadVexIndex;
    struct ArcNode* SameHeadArc;
    struct ArcNode* SameTailArc;
}ArcNode_Type,*ArcNodePtr_Type;

typedef struct Vertex{
    VertexData_Type VD;
    ArcNodePtr_Type FirstInHeadArc;
    ArcNodePtr_Type FirstOutTailArc;
}Vertex_Type, *VertexPtr_Type;

typedef struct Graph{
    Vertex_Type Vertex_Type[MAX_VERTEX_NUM];
    int VertexNum,ArcNum;
    GraphKind_Type Kind;
}Graph_Type, OLGraph_Type;

void Create_OLGraph(Graph_Type* G,const VertexData_Type VXList[VERTEX_NUM],const VertexData_Type AdjastVXChart[VERTEX_NUM][VERTEX_NUM],const int vxnum,const GraphKind_Type kind);
int Locate_OLNode(Graph_Type *G,VertexData_Type VX);
void Traverse_BFS_OLGraph(Graph_Type *G);
void Traverse_DFS_OLGraph(Graph_Type *G);
void DFS_OLGraph(Graph_Type *G,int VIndex);
void BFS_OLGraph(Graph_Type *G,int VIndex);
void Add_OLNode(Graph_Type *G,VertexData_Type NodeData);
void Delete_OLNode(Graph_Type *G,VertexData_Type NodeData);
void Add_OLArc(Graph_Type *G,VertexData_Type Head,VertexData_Type Tail);
void Delete_OLArc(Graph_Type *G,VertexData_Type Head,VertexData_Type Tail);
void Delete_OLGraph(Graph_Type* G);
#endif
