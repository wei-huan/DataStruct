#include "OL_Graph.h"

SearchMark_Type S_Array[MAX_VERTEX_NUM];

//创建十字链表形式的图
void Create_OLGraph(Graph_Type* G,
                   const VertexData_Type VXList[VERTEX_NUM],
                   const VertexData_Type AdjastVXChart[VERTEX_NUM][VERTEX_NUM],
                   const int vxnum,
                   const GraphKind_Type kind){
    ArcNodePtr_Type AddArc;             // 声明添加弧节点指针
    int HeadIndex = -1;            // 声明并初始化弧头顶点对应下标                    

    // 初始化弧节点个数为0
    G->ArcNum=0;
    // 写入顶点个数
    G->VertexNum=vxnum;
    // 写入图类型
    G->Kind=kind;

    // 将顶点数据写入图的顶点数组
    for(int i = 0; i<vxnum; i++){
        // 写入数据
        G->Vertex_Type[i].VD=VXList[i];
        // 顶点邻接弧节点先设为NULL
        G->Vertex_Type[i].FirstInHeadArc = NULL;
        G->Vertex_Type[i].FirstOutTailArc = NULL;
    }

    // 根据邻接顶点二维表生成图的十字链表

    // 大循环,按行循环邻接顶点二维表
    for(int i = 0; i < vxnum; i++){   
        // 小循环,按列循环邻接顶点二维表
        for(int j = 0; j < vxnum; j++){
            // 如果邻接顶点二维表Aij元素在A到Z范围内且不等于本顶点,则判断能否定位到该顶点
            if('A' <= AdjastVXChart[i][j] && AdjastVXChart[i][j] <= 'Z' && AdjastVXChart[i][j] != G->Vertex_Type[i].VD){    
                // 获取要写入的邻接点在顶点数组的下标
                HeadIndex = Locate_OLNode(G, AdjastVXChart[i][j]);

                // 如果定位不到到该顶点, 报错, 退出程序
                if(HeadIndex == -1){
                    printf("无此节点\n");
                    exit(0);
                }
                // 如果定位到该节点, 写入数据到指针AddArc指向的空间
                else{   
                    // 为下一个邻接顶点分配空间
                    AddArc = (ArcNodePtr_Type)malloc(sizeof(ArcNode_Type));
                    // 写入弧尾顶点对应下标
                    AddArc->TailVexIndex = i;
                    // 写入弧头顶点对应下标
                    AddArc->HeadVexIndex = HeadIndex;
                    // 写入弧尾顶点对应数组的顶点的首出弧节点的链表
                    AddArc->SameTailArc = G->Vertex_Type[i].FirstOutTailArc; 
                    G->Vertex_Type[i].FirstOutTailArc = AddArc;
                    // 写入弧头顶点对应数组的顶点的首入弧节点的链表
                    AddArc->SameHeadArc = G->Vertex_Type[HeadIndex].FirstInHeadArc;
                    G->Vertex_Type[HeadIndex].FirstInHeadArc = AddArc;
                    // 弧个数加1
                    G->ArcNum++;
                }
            }
        }
    }
    printf("ArcNum: %d\n", G->ArcNum);
}

// 定位顶点在图的顶点数组的位置, 成功返回下标, 失败返回-1
int Locate_OLNode(Graph_Type *G,VertexData_Type VX){
    //对图的顶点数组遍历查找
    for(int VIndex=0;VIndex<G->VertexNum;VIndex++)
        if(G->Vertex_Type[VIndex].VD==VX)
            return VIndex;

    // 未找到返回-1
    return -1;
}

// 广度优先遍历邻接表形式的图
void Traverse_BFS_OLGraph(Graph_Type *G){
    for(int vi = 0; vi < G->VertexNum; vi++)
        S_Array[vi] = No;

    for(int vi = 0; vi < G->VertexNum; vi++)
        if(S_Array[vi] == No)
            BFS_OLGraph(G, vi);    
}

void BFS_OLGraph(Graph_Type *G,int VIndex){
    ArcNodePtr_Type S_Arc;
    
    S_Array[VIndex] = Yes;
    printf("visit_node: %c\n", G->Vertex_Type[VIndex].VD);

    if(G->Vertex_Type[VIndex].FirstOutTailArc != NULL){
        S_Arc = G->Vertex_Type[VIndex].FirstOutTailArc;

        while(S_Arc->SameTailArc != NULL){
            S_Arc = S_Arc->SameTailArc;

            if(S_Array[S_Arc->HeadVexIndex] == No){
                S_Array[S_Arc->HeadVexIndex] = Yes;
                printf("visit_node: %c\n", G->Vertex_Type[S_Arc->HeadVexIndex].VD);
            }
        }
    }    
}

// 深度优先遍历邻接表形式的图
void Traverse_DFS_OLGraph(Graph_Type *G){
    for(int vi = 0; vi < G->VertexNum; vi++)
        S_Array[vi] = No;

    for(int vi = 0; vi < G->VertexNum; vi++)
        if(S_Array[vi] == No)
            DFS_OLGraph(G, vi);
}

// 深度优先遍历节点
void DFS_OLGraph(Graph_Type *G,int VIndex){
    ArcNodePtr_Type S_Arc;
    
    S_Array[VIndex] = Yes;
    printf("visit_node: %c\n", G->Vertex_Type[VIndex].VD);

    if(G->Vertex_Type[VIndex].FirstOutTailArc != NULL){
        S_Arc = G->Vertex_Type[VIndex].FirstOutTailArc;

        //printf("%c first out tailvex head: %c\n",  G->Vertex_Type[VIndex].VD, G->Vertex_Type[S_Arc->HeadVexIndex].VD);

        while(S_Arc->SameTailArc != NULL){
            if(S_Array[S_Arc->HeadVexIndex] == No)
                DFS_OLGraph(G, S_Arc->HeadVexIndex);

            S_Arc = S_Arc->SameTailArc;
        }
    }
}

// 添加顶点
void Add_OLNode(Graph_Type *G,VertexData_Type NodeData){
}

//删除顶点
void Delete_OLNode(Graph_Type *G,VertexData_Type NodeData){
}

//添加弧
void Add_OLArc(Graph_Type *G,VertexData_Type Head,VertexData_Type Tail){
}

//删除弧
void Delete_OLArc(Graph_Type *G,VertexData_Type Head,VertexData_Type Tail){
}

// 删除图
void Delete_OLGraph(Graph_Type* G){
    ArcNodePtr_Type DeletePtr, SetNullPtr_T, SetNullPtr_H;

    // 大循环, 按行循环十字链表
    for(int i = 0; i < G->VertexNum; i++){
        if(G->Vertex_Type[i].FirstOutTailArc != NULL){
            // 找到同尾弧的最后一条弧    
            DeletePtr = G->Vertex_Type[i].FirstOutTailArc;
        
            while(DeletePtr->SameTailArc != NULL)
                DeletePtr = DeletePtr->SameTailArc;

            // 删除弧, 直到本行同尾弧被删除完毕
            while(DeletePtr != NULL){
                // 找到要删除弧的前一条同尾弧, 断开连接
                SetNullPtr_T = G->Vertex_Type[i].FirstOutTailArc;

                if(SetNullPtr_T != DeletePtr){
                    while(SetNullPtr_T->SameTailArc != DeletePtr)
                        SetNullPtr_T = SetNullPtr_T->SameTailArc;

                    SetNullPtr_T->SameTailArc = NULL;
                }
                // 要删除的弧是该行的最后一条弧, 因为要释放, 所以其他指针不能指向要删除的弧
                else{
                    SetNullPtr_T = NULL;
                    G->Vertex_Type[i].FirstOutTailArc = NULL;
                }

                // 断开其他同头弧与当前要删除的弧的连接
                if(G->Vertex_Type[DeletePtr->HeadVexIndex].FirstInHeadArc == DeletePtr)
                    G->Vertex_Type[DeletePtr->HeadVexIndex].FirstInHeadArc = NULL;
                else{
                    SetNullPtr_H = G->Vertex_Type[DeletePtr->HeadVexIndex].FirstInHeadArc;

                    while (SetNullPtr_H->SameHeadArc != DeletePtr)
                        SetNullPtr_H = SetNullPtr_H->SameHeadArc;

                    SetNullPtr_H->SameHeadArc = NULL;
                }

                // 断开要删除的弧与其他同头弧的连接
                if(DeletePtr->SameHeadArc != NULL)
                    DeletePtr->SameHeadArc = NULL;

                free(DeletePtr);

                DeletePtr = SetNullPtr_T;
            }
        }
    }
    G->VertexNum = 0;
    G->ArcNum = 0;
    G->Kind = NotSet;
}
