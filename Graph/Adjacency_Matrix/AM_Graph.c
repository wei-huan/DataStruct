#include "AM_Graph.h"

//创建邻接矩阵形式的图
void Create_AMGraph(Graph *G,const VertexData VXList[VERTEX_NUM],const VertexData AdjastVXChart[VERTEX_NUM][VERTEX_NUM],const int vxnum,const GraphKind kind)
{
    int location;           //声明定位邻接顶点二维表数据下标的变量

    //写入顶点个数
    G->VertexNum=vxnum;

    //写入图类型
    G->Kind=kind;
    
    //将顶点数据写入图的顶点数组
    for(int i=0;i<vxnum;i++)
        G->Vertex[i]=VXList[i];

    //初始化二维数组全部数据为NotAdj
    for(int i=0;i<vxnum;i++)
        for(int j=0;j<vxnum;j++)
            G->ArcNodeMatrix[i][j]=NotAdj;

    //根据邻接顶点二维表循环生成图的邻接矩阵

    //大循环,按行循环邻接顶点二维表
    for(int i=0;i<vxnum;i++)
        //小循环,按列循环邻接顶点二维表
        for(int j=0;j<vxnum;j++)
        {
            //如果本行邻接数据已经读取完了,跳出循环
            if(AdjastVXChart[i][j]==0)
                break;

            //定位邻接点的下标
            location=Locate_AMNode(G,AdjastVXChart[i][j]);

            //如果定位不到到该顶点,报错,退出程序
            if(location==-1)
            {
                printf("无此节点\n");
                exit(0);
            }

            //如果邻接顶点二维表Aij不等于本顶点,写入数据
            if(AdjastVXChart[i][j]!=G->Vertex[i])
            { 
                G->ArcNodeMatrix[i][location]=Adj;
                //弧个数加1
                G->ArcNum++;
            }
            //如果邻接顶点二维表Aij元素不符合要求,跳出小循环
            else break;
        }
}

//定位顶点在图的顶点数组的位置,成功返回下标,失败返回-1
int Locate_AMNode(Graph *G,VertexData VX)
{
    //对图的顶点数组遍历查找
    for(int VIndex=0;VIndex<G->VertexNum;VIndex++)
        if(G->Vertex[VIndex]==VX)
            return VIndex;

    //未找到返回-1
    return -1;
}

//遍历邻接矩阵形式的图
void Traverse_AMGraph(Graph *G)
{
    ;
}//太简单了吧就不写了

//添加顶点
void Add_AMNode(Graph *G,VertexData NodeData)
{
    ;
}//太简单了吧就不写了

//删除顶点
void Delete_AMNode(Graph *G,VertexData NodeData)
{
    ;
}//太简单了吧就不写了

//添加弧
void Add_AMArc(Graph *G,VertexData Head,VertexData Tail)
{
    ;
}//太简单了吧就不写了

//删除弧
void Delete_AMArc(Graph *G,VertexData Head,VertexData Tail)
{
    ;
}//太简单了吧就不写了