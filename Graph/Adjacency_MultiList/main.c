#include "AML_Graph.h"

void printarc(VertexData_Type i,VertexData_Type j){
    printf("%c--%c\n",i,j);
}

int main(){
    AMLGraph_Type G;                                                    //声明图
    int vxnum = 6;                                                //声明并初始化图顶点为5
    GraphKind_Type kind = UDG;                                          //声明图类型并初始化为有向图
    VertexData_Type VXList[5] = {'A','G','H','K','M'};                 //声明并初始化构造图顶点的数组
    VertexData_Type AdjastVXChart[5][5] = {{'G','H', 0 , 0 , 0 },      //声明并初始化构造图弧的二维数组
                                      { 0 , 0 , 0 , 0 , 0 },
                                      {'K','M', 0 , 0 , 0 },
                                      {'A','G', 0, 0 , 0 },
                                      {'K', 0 , 0 , 0 , 0 }};

    //创建图
    Create_AMLGraph(&G,VXList,AdjastVXChart,vxnum,kind);
    //遍历图
    Traverse_DFS_AMLGraph(&G);
    // Traverse_BFS_AMLGraph(&G);
    //删除图
    Delete_AMLGraph(&G);

    return 0;
}