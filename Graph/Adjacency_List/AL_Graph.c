#include "AL_Graph.h"

//创建邻接表形式的图
void Create_ALGraph(Graph *G,
                    const VertexData VXList[VERTEX_NUM],
                    const VertexData AdjastVXChart[VERTEX_NUM][VERTEX_NUM],
                    const int vxnum,
                    const GraphKind kind)
{
    ArcNode *SearchArc=NULL;         //声明辅助搜索弧节点指针

    //初始化弧节点个数为0
    G->ArcNum=0;

    //写入顶点个数
    G->VertexNum=vxnum;

    //写入图类型
    G->Kind=kind;
    
    //将顶点数据写入图的顶点数组
    for(int i=0;i<vxnum;i++)
    {
        //写入数据
        G->Vertex[i].VD=VXList[i];
        //为写入邻接顶点分配空间
        G->Vertex[i].FirstAdj=(ArcNode*)malloc(sizeof(ArcNode));
        //初始化数据
        G->Vertex[i].FirstAdj->AVD='\0';
        G->Vertex[i].FirstAdj->ArcNodeIndex=-1;
        G->Vertex[i].FirstAdj->NextAdj=NULL;
    }

    //根据邻接顶点二维表循环生成图的邻接链表

    //大循环,按行循环邻接顶点二维表
    for(int i=0;i<vxnum;i++)
    { 
        //将搜索弧指针先指向顶点数组第i列首邻接点
        SearchArc=G->Vertex[i].FirstAdj;

        //小循环,按列循环邻接顶点二维表
        for(int j=0;j<vxnum;j++)
        {
            //如果邻接顶点二维表Aij元素在A到Z范围内且不等于本顶点,则判断能否定位到该顶点
            if('A'<=AdjastVXChart[i][j]&&AdjastVXChart[i][j]<='Z'&&AdjastVXChart[i][j]!=G->Vertex[i].VD)
            {    
                //如果定位不到到该顶点,报错,退出程序
                if(Locate_ALNode(G,AdjastVXChart[i][j])==-1)
                {
                    printf("无此节点\n");
                    exit(0);
                }
                //如果定位到该节点,写入数据到指针SearchArc指向的空间
                else
                {    
                    //写入邻接顶点数据
                    SearchArc->AVD=AdjastVXChart[i][j];
                    //写入邻接顶点在顶点数组的下标
                    SearchArc->ArcNodeIndex=Locate_ALNode(G,AdjastVXChart[i][j]);
                    //为下一个邻接顶点分配空间
                    SearchArc->NextAdj=(ArcNode*)malloc(sizeof(ArcNode));
                    //搜索弧指针指向下一个邻接弧
                    SearchArc=SearchArc->NextAdj;
                    //初始化数据
                    SearchArc->AVD='\0';
                    SearchArc->ArcNodeIndex=-1;
                    SearchArc->NextAdj=NULL;

                    //弧个数加1
                    G->ArcNum++;
                }
            }
            //如果邻接顶点二维表Aij元素不符合要求,跳出小循环
            else break;
        }
    }
}

//定位顶点在图的顶点数组的位置,成功返回下标,失败返回-1
int Locate_ALNode(Graph *G,VertexData VX)
{
    //对图的顶点数组遍历查找
    for(int VIndex=0;VIndex<G->VertexNum;VIndex++)
        if(G->Vertex[VIndex].VD==VX)
            return VIndex;

    //未找到返回-1
    return -1;
}

//遍历邻接表形式的图
void Traverse_ALGraph(Graph *G)
{
    ;
}

//添加顶点
void Add_ALNode(Graph *G,VertexData NodeData)
{
    ;
}

//删除顶点
void Delete_ALNode(Graph *G,VertexData NodeData)
{
    ;
}

//添加弧
void Add_ALArc(Graph *G,VertexData Head,VertexData Tail)
{
    ;
}

//删除弧
void Delete_ALArc(Graph *G,VertexData Head,VertexData Tail)
{
    ;
}

//删除图
void Destroy_ALGraph(Graph *G)
{
    ArcNode *DeleteArc;           //声明辅助删除弧节点指针

    //依次对图的顶点数组的元素释放内存
    for(int i=0;i<G->VertexNum;i++)
    {
        //释放弧节点直到首弧节点为空
        while(G->Vertex[i].FirstAdj!=NULL)
        {
            //指向顶点的首弧节点
            DeleteArc=G->Vertex[i].FirstAdj;

            //将删除弧指针指向最后一个弧节点
            while(DeleteArc->NextAdj!=NULL)
                DeleteArc=DeleteArc->NextAdj;

            //释放弧节点
            free(DeleteArc);
        }
    }

    //将弧节点数设为0
    G->ArcNum=0;
}