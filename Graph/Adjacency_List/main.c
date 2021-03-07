#include "AL_Graph.h"

int main()
{
    Graph G;                                                    //声明图
    int vxnum=5;                                                //声明并初始化图顶点为5
    GraphKind kind=DG;                                          //声明图类型并初始化为有向图
    VertexData VXList[5]={'A','G','H','K','M'};                 //声明并初始化构造图顶点的数组
    VertexData AdjastVXChart[5][5]={{'G','H', 0 , 0 , 0 },      //声明并初始化构造图弧的二维数组
                                    { 0 , 0 , 0 , 0 , 0 },
                                    {'K','M', 0 , 0 , 0 },
                                    {'A','G','H', 0 , 0 },
                                    {'K', 0 , 0 , 0 , 0 }}; 

    //创建图
    Create_ALGraph(&G,VXList,AdjastVXChart,vxnum,kind);
    
    printf("%c\n",G.Vertex[3].FirstAdj->NextAdj->AVD);
    //遍历图
    Traverse_ALGraph(&G);
    //删除图
    Destroy_ALGraph(&G);

}