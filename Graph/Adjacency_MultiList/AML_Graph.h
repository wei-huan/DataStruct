#ifndef AML_Graph
#define AML_Graph

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTEX_NUM    20
#define INFINITY          32678
#define VERTEX_NUM        5

typedef char VertexData;
typedef enum {DG,DN,UDG,UDN,NotSet}GraphKind;
typedef enum {Yes,No}SearchMark;

typedef struct Vertex
{
    VertexData VD;
    struct ArcNode* Firstedge;
}Vertex;

typedef struct ArcNode
{
    SearchMark SMark;
    int IVex,JVex;
    struct ArcNode *ILink,*JLink;
}ArcNode;

typedef struct Graph
{
    Vertex Vertex[MAX_VERTEX_NUM];
    int VertexNum,ArcNum;
    GraphKind Kind;
}Graph,AMLGraph;

extern void Create_AMLGraph(Graph *G,const VertexData VXList[VERTEX_NUM],const VertexData AdjastVXChart[VERTEX_NUM][VERTEX_NUM],const int vxnum,const GraphKind kind);
extern void Traverse_AMLGraph(Graph *G);
extern int Locate_AMLNode(Graph *G,VertexData VX);
extern void Add_AMLNode(Graph *G,VertexData NodeData);
extern void Delete_AMLNode(Graph *G,VertexData NodeData);
extern void Add_AMLArc(Graph *G,VertexData Head,VertexData Tail);
extern void Delete_AMLArc(Graph *G,VertexData Head,VertexData Tail);
extern void Delete_AMLGraph(Graph *G);
#endif