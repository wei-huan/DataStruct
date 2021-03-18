#include "AML_Graph.h"

void printarc(VertexData i,VertexData j)
{
    printf("%c---->%c\n",i,j);
}

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
    Create_AMLGraph(&G,VXList,AdjastVXChart,vxnum,kind);
    //遍历图
    Traverse_AMLGraph(&G);
    //测试画图
    Test_Draw(&G,printarc);
    //删除图
    Delete_AMLGraph(&G);

    return 0;
}