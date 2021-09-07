#ifndef AM_Graph_Type
#define AM_Graph_Type

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTEX_NUM   20
#define INFINITY         32768
#define VERTEX_NUM       5

typedef enum {DG,DN,UDG,UDN,NotSet}GraphKind_Type;
typedef enum {NotAdj,Adj}Adj_Type;
typedef char VertexData_Type;
typedef int ArcWeight_Type;
typedef ArcWeight_Type ArcNode_Type;

typedef struct Graph
{
    VertexData_Type Vertex[MAX_VERTEX_NUM];
    ArcNode_Type ArcNodeMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int VertexNum,ArcNum;
    GraphKind_Type Kind;
}Graph_Type, AMGraph_Type;

extern void Create_AMGraph_Type(Graph_Type *G,const VertexData_Type VXList[VERTEX_NUM], const VertexData_Type AdjastVXChart[VERTEX_NUM][VERTEX_NUM],const int vxnum,const GraphKind_Type kind);
extern int Locate_AMNode(Graph_Type *G, VertexData_Type VX);
extern void Traverse_AMGraph_Type(Graph_Type *G);
extern void Add_AMNode(Graph_Type *G, VertexData_Type NodeData);
extern void Delete_AMNode(Graph_Type *G, VertexData_Type NodeData);
extern void Add_AMArc(Graph_Type *G, VertexData_Type Head, VertexData_Type Tail);
extern void Delete_AMArc(Graph_Type *G, VertexData_Type Head, VertexData_Type Tail);
#endif
