#include "AL_Graph.h"

int main(){
    Graph_Type G;

    // 创建图
    Create_ALGraph(&G);
    // 迪杰斯特拉算法求最短路径
    Dijkstra(&G, G.Vertex[0].VD);
    // 佛洛依德算法求最短路径
    Floyd(&G, G.Vertex[0].VD);
    // 删除图
    Destroy_ALGraph(&G);

    return 0;
}