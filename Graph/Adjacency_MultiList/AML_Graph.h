#ifndef AML_Graph
#define AML_Graph

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTEX_NUM    20
#define INFINITY          32678
#define VERTEX_NUM        5

typedef char VertexData_Type;
typedef int  ArcWeight_Type;
typedef enum {DG,DN,UDG,UDN,NotSet}GraphKind_Type;
typedef enum {Yes,No}SearchMark_Type;
typedef void CALLBACK(VertexData_Type,VertexData_Type);

typedef struct ArcNode{
    int IVex,JVex;
    ArcWeight_Type AW;
    struct ArcNode_Type* ILink;
    struct ArcNode_Type* JLink;
}ArcNode_Type,*ArcNodePtr_Type;

typedef struct Vertex{
    VertexData_Type VD;
    ArcNodePtr_Type Firstedge;
}Vertex_Type,*VertexPtr_Type;

typedef struct Graph{
    Vertex_Type Vertex_Type[MAX_VERTEX_NUM];
    int VertexNum,ArcNum;
    GraphKind_Type Kind;
}Graph_Type, AMLGraph_Type, *GraphPtr_Type, *AMLGraphPtr_Type;

void Create_AMLGraph(Graph_Type *G,const VertexData_Type VXList[VERTEX_NUM],const VertexData_Type AdjastVXChart[VERTEX_NUM][VERTEX_NUM],const int vxnum,const GraphKind_Type kind);
void Traverse_BFS_AMLGraph(Graph_Type *G);
void Traverse_DFS_AMLGraph(Graph_Type *G);
void DFS_AMLGraph(Graph_Type *G,int VIndex);
void BFS_AMLGraph(Graph_Type *G,int VIndex);
void Test_Draw(Graph_Type *G,CALLBACK visit);
int Locate_AMLNode(Graph_Type *G,VertexData_Type VX);
void Add_AMLNode(Graph_Type *G,VertexData_Type NodeData);
void Delete_AMLNode(Graph_Type *G,VertexData_Type NodeData);
void Add_AMLArc(Graph_Type *G,VertexData_Type Head,VertexData_Type Tail);
void Delete_AMLArc(Graph_Type *G,VertexData_Type Head,VertexData_Type Tail);
void Delete_AMLGraph(Graph_Type *G);
#endif
