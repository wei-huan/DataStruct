#include "AML_Graph.h"

SearchMark_Type S_Array[MAX_VERTEX_NUM];

//创建邻接多重表形式的图
void Create_AMLGraph(Graph_Type *G,
                     const VertexData_Type VXList[VERTEX_NUM],
                     const VertexData_Type AdjastVXChart[VERTEX_NUM][VERTEX_NUM],
                     const int vxnum,
                     const GraphKind_Type kind)
{
    ArcNodePtr_Type AddArc=NULL;           //声明添加弧节点指针和辅助搜索指针
    int JIndex=-1;                                                       //声明并初始化弧头顶点对应下标                    

    // 初始化弧节点个数为0
    G->ArcNum = 0;
    // 写入顶点个数
    G->VertexNum = vxnum;
    // 写入图类型
    G->Kind = kind;

    // 将顶点数据写入图的顶点数组
    for(int i = 0; i < vxnum; i++){
        // 写入数据
        G->Vertex_Type[i].VD = VXList[i];
        // 顶点邻接弧节点先设为NULL
        G->Vertex_Type[i].Firstedge = NULL;
    }

    // 根据邻接顶点二维表生成图的邻接多重表

    // 大循环,按行循环邻接顶点二维表
    for(int i = 0; i < vxnum; i++){ 
        // 小循环,按列循环邻接顶点二维表
        for(int j = 0; j < vxnum; j++){
            // 如果邻接顶点二维表Aij元素在A到Z范围内且不等于本顶点,则判断能否定位到该顶点
            if('A' <= AdjastVXChart[i][j] && AdjastVXChart[i][j] <= 'Z' && AdjastVXChart[i][j] != G->Vertex_Type[i].VD){    
                // 获取要写入的邻接点在顶点数组的下标
                JIndex = Locate_AMLNode(G,AdjastVXChart[i][j]);

                // 如果定位不到到该顶点,报错,退出程序
                if(JIndex == -1){
                    printf("无此节点\n");
                    exit(0);
                }
                // 如果定位到该节点,写入数据到指针AddArc指向的空间
                else{   
                    // 为邻接顶点分配空间
                    AddArc = (ArcNode_Type*)malloc(sizeof(ArcNode_Type));
                    // 写入弧头顶点对应下标
                    AddArc->JVex = JIndex;
                    // 写入弧尾顶点对应下标
                    AddArc->IVex = i;
                    // 写入对应顶点数组的首弧节点的链表
                    AddArc->ILink = G->Vertex_Type[i].Firstedge;
                    G->Vertex_Type[i].Firstedge = AddArc;

                    AddArc->JLink = G->Vertex_Type[JIndex].Firstedge;
                    G->Vertex_Type[JIndex].Firstedge = AddArc;
                    // 弧个数加1
                    G->ArcNum++;
                }
            }
        }
    }
}

//定位顶点在图的顶点数组的位置,成功返回下标,失败返回-1
int Locate_AMLNode(Graph_Type *G,VertexData_Type VX)
{
    //对图的顶点数组遍历查找
    for(int VIndex=0;VIndex<G->VertexNum;VIndex++)
        if(G->Vertex_Type[VIndex].VD==VX)
            return VIndex;

    //未找到返回-1
    return -1;
}

//遍历邻接多重表形式的图
void Traverse_BFS_AMLGraph(Graph_Type *G){
    for(int vi = 0; vi < G->VertexNum; vi++)
        S_Array[vi] = No;

    for(int vi = 0; vi < G->VertexNum; vi++)
        if(S_Array[vi] == No)
            BFS_AMLGraph(G, vi);   
}

void BFS_AMLGraph(Graph_Type *G,int VIndex){
    ArcNodePtr_Type S_Arc;
    
    S_Array[VIndex] = Yes;
    printf("visit_node: %c\n", G->Vertex_Type[VIndex].VD);

    if(G->Vertex_Type[VIndex].Firstedge != NULL){
        S_Arc = G->Vertex_Type[VIndex].Firstedge;

        while(S_Arc->ILink != NULL){
            S_Arc = S_Arc->ILink;

            if(S_Array[S_Arc->JVex] == No){
                S_Array[S_Arc->JVex] = Yes;
                printf("visit_node: %c\n", G->Vertex_Type[S_Arc->JVex].VD);
            }
        }
    }    
}

void Traverse_DFS_AMLGraph(Graph_Type *G){
    for(int vi = 0; vi < G->VertexNum; vi++)
        S_Array[vi] = No;

    for(int vi = 0; vi < G->VertexNum; vi++)
        if(S_Array[vi] == No)
            DFS_AMLGraph(G, vi);
}

void DFS_AMLGraph(Graph_Type *G,int VIndex){
    ArcNodePtr_Type S_Arc;
    
    S_Array[VIndex] = Yes;
    printf("visit_node: %c\n", G->Vertex_Type[VIndex].VD);

    if(G->Vertex_Type[VIndex].Firstedge != NULL){
        S_Arc = G->Vertex_Type[VIndex].Firstedge;

        //printf("%c first out tailvex head: %c\n",  G->Vertex_Type[VIndex].VD, G->Vertex_Type[S_Arc->HeadVexIndex].VD);

        while(S_Arc->ILink != NULL){
            if(S_Array[S_Arc->JVex] == No)
                DFS_AMLGraph(G, S_Arc->JVex);

            S_Arc = S_Arc->ILink;
        }
    }

}

void Test_Draw(Graph_Type *G,CALLBACK visit){
    ArcNodePtr_Type SearchArc;

    SearchArc=G->Vertex_Type[0].Firstedge;

    while(SearchArc!=NULL){
        visit(G->Vertex_Type[SearchArc->IVex].VD,G->Vertex_Type[SearchArc->JVex].VD);
        SearchArc=SearchArc->ILink;
    }
}

//添加顶点
void Add_AMLNode(Graph_Type *G,VertexData_Type NodeData){
}

//删除顶点
void Delete_AMLNode(Graph_Type *G,VertexData_Type NodeData){
}

//添加弧
void Add_AMLArc(Graph_Type *G,VertexData_Type Head,VertexData_Type Tail){
}

//删除弧
void Delete_AMLArc(Graph_Type *G,VertexData_Type Head,VertexData_Type Tail){
}

//删除图
void Delete_AMLGraph(Graph_Type *G){
    ArcNodePtr_Type DeletePtr, DeleteNextPtr, SetNullPtr, SetNullPtr_N;  //声明删除弧指针和设空弧指针
    int J_index = -1;

    // 依次对顶点数组的顶点删除弧节点
    for(int i = 0; i < G->VertexNum; i++){
        DeletePtr = G->Vertex_Type[i].Firstedge;
        G->Vertex_Type[i].Firstedge = NULL;

        while(DeletePtr != NULL){
            // 找到要删除的节点连接的下两个节点, 暂存并断开连接
            if(DeletePtr->IVex == i){
                if(DeletePtr->ILink != NULL){
                    DeleteNextPtr = DeletePtr->ILink;
                    // 断开要删除的节点与其他节点在目标方向连接
                    DeletePtr->ILink = NULL;
                }
                else
                    DeleteNextPtr = NULL;

                // 暂存下一条边方向和节点, 并断开要删除的弧与另一个防线的下一条边的关系
                J_index = DeletePtr->JVex;

                if(DeletePtr->JLink != NULL){
                    SetNullPtr_N = DeletePtr->JLink;
                    DeletePtr->JLink = NULL;
                }
                else
                    SetNullPtr_N = NULL;
            }
            else if(DeletePtr->JVex == i){
                if(DeletePtr->JLink != NULL){
                    DeleteNextPtr = DeletePtr->JLink;
                    
                    // 断开要删除的节点与其他节点在目标方向连接
                    DeletePtr->JLink = NULL;
                }
                else
                    DeleteNextPtr = NULL;

                // 暂存下一条边方向和节点, 并断开要删除的弧与另一个方向的下一条边的关系
                J_index = DeletePtr->IVex;

                if(DeletePtr->ILink != NULL){
                    SetNullPtr_N = DeletePtr->ILink;
                    DeletePtr->ILink = NULL;
                }
                else
                    SetNullPtr_N = NULL;    
            }
            else
                printf("怎么可能\n");
            

            // 断开另一个非本轮目标的节点方向上的连接, 将前一个节点直接连接后一个节点，绕开要删除的节点
            if(G->Vertex_Type[J_index].Firstedge == DeletePtr){
                G->Vertex_Type[J_index].Firstedge = SetNullPtr_N;
                SetNullPtr = NULL;
            }
            else{
                SetNullPtr = G->Vertex_Type[J_index].Firstedge;

                while(SetNullPtr->ILink != NULL || SetNullPtr->JLink != NULL){
                    if(SetNullPtr->ILink != NULL){
                        // 如果找到弧, 则将其连接到要删除的弧的下一个节点上
                        if(SetNullPtr->ILink == DeletePtr){
                            SetNullPtr->ILink = SetNullPtr_N;
                            break;
                        }
                        // 没找到则顺着Jindex找下一个
                        else{
                            if(SetNullPtr->IVex == J_index)
                                SetNullPtr = SetNullPtr->ILink;
                        }
                    }
                    
                    if(SetNullPtr->JLink != NULL){
                        // 如果找到弧, 则将其连接到要删除的弧的下一个节点上
                        if(SetNullPtr->JLink == DeletePtr){
                            SetNullPtr->JLink = SetNullPtr_N;
                            break;
                        }                        
                        // 没找到则顺着Jindex找下一个
                        else{
                            if(SetNullPtr->JVex == J_index)
                                SetNullPtr = SetNullPtr->JLink;
                        }
                    }
                }
            }
            
            // 释放要删除的弧
            free(DeletePtr);
            // 删除弧指向下一个要删除的弧
            DeletePtr = DeleteNextPtr;
        }
    }
    //图节点数设为0
    G->VertexNum = 0;
    //图类型树设为未设置
    G->Kind = NotSet;
}
