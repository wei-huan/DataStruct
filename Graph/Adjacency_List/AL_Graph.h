#ifndef AL_Graph
#define AL_Graph

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include "../../Queue/cyclequeue.h"

#define MAX_VERTEX_NUM   20
#define INFINITY         32768
#define VERTEX_NUM       5

typedef enum {NotSet, DG, UDG, DN, UDN}GraphKind_Type;
typedef enum {Yes, No}SrchMark_Type;
// typedef char VertexData_Type;
// typedef int ArcWeight_Type;

// typedef struct ArcNode{
//     int ANIdx;
//     VertexData_Type AVD;
//     ArcWeight_Type AW;
//     struct ArcNode *NextAdj;
// }ArcNode_Type, *ArcNodePtr_Type; 

typedef struct VertexNode{
    VertexData_Type VD;
    ArcNodePtr_Type FirstAdj;
}VertexNode_Type,*VertexNodePtr_Type;

typedef struct Graph{
    VertexNode_Type Vertex[MAX_VERTEX_NUM];
    int VertexNum,ArcNum;
    GraphKind_Type Kind;
}Graph_Type, ALGraph_Type, *GraphPtr_Type, *ALGraphPtr_Type;

// 普里姆算法的辅助数组
typedef struct Closedge{
    int adjver_Index;
    ArcWeight_Type W; 
}Closedge_Type;

// 迪杰斯特拉算法的辅助数组
typedef struct Dijkstra_Element{
    SrchMark_Type isAdd;
    int prev_idx;
    int dis;
}Dijkstra_Element_Type, Dijkstra_Array_Type;

void Create_ALGraph(ALGraphPtr_Type G);
void Greate_Inverse_ALGraph(ALGraphPtr_Type G, ALGraphPtr_Type AG);
int Locate_ALNode(ALGraphPtr_Type G, VertexData_Type VX);
ArcNodePtr_Type Locate_Arc(ALGraphPtr_Type G, VertexData_Type SV, VertexData_Type EV);
void Traverse_BFS_ALGraph(ALGraphPtr_Type G);
void Traverse_DFS_ALGraph(ALGraphPtr_Type G);
void DFS_ALGraph(ALGraphPtr_Type G, int VIndex);
void BFS_ALGraph(ALGraphPtr_Type G, int VIndex);
int Count_Node_Indegree(ALGraphPtr_Type G, VertexData_Type NodeData);
void Count_All_Indegree(ALGraphPtr_Type G, int Indgree_Arr[]);
int Count_Node_Outdegree(ALGraphPtr_Type G, VertexData_Type NodeData);
void Count_All_Outdegree(ALGraphPtr_Type G, int Outgree_Arr[]);
int TopoOrder_ALGraph(ALGraphPtr_Type G, int erly_t_array[], int topo_sris[]);
int TopoOrder_Inverse_ALGraph(ALGraphPtr_Type AG, int late_t_array[]);
int Critical_Path(ALGraphPtr_Type G);
void TopoSort_ALGraph(ALGraphPtr_Type G);
void Dijkstra(ALGraphPtr_Type G, VertexData_Type src_node);
void Floyd(ALGraphPtr_Type G, VertexData_Type src_node);
void Add_ALNode(ALGraphPtr_Type G, VertexData_Type NodeData);
void Delete_ALNode(ALGraphPtr_Type G, VertexData_Type NodeData);
void Add_ALArc(ALGraphPtr_Type G, VertexData_Type Head, VertexData_Type Tail, ArcWeight_Type AW);
ArcNodePtr_Type Search_ALArc(ALGraphPtr_Type G, VertexData_Type Head, VertexData_Type Tail);
void Delete_ALArc(ALGraphPtr_Type G, VertexData_Type Head, VertexData_Type Tail);
void MiniSpanTree_Prim(ALGraphPtr_Type G, VertexData_Type Start_V);
void MiniSpanTree_Kerus(ALGraphPtr_Type G);
void Destroy_ALGraph(ALGraphPtr_Type G);
#endif
