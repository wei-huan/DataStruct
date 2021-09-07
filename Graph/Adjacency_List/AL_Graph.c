#include "AL_Graph.h"

#define EOL putchar('\n')
SrchMark_Type S_Array[MAX_VERTEX_NUM];
Queue_Type Arc_Queue;

// 创建邻接表形式的图
void Create_ALGraph(ALGraphPtr_Type G){
    // 声明辅助搜索弧节点指针
    ArcNodePtr_Type AddArc, CheckArc;        
    VertexData_Type IV, JV;
    int I_Index, J_Index;
    char ArcStr[8];

    // 写入顶点个数
    printf("请输入顶点个数: ");
    scanf("%d", &(G->VertexNum));

    // 写入图类型
    printf("\r\n图的类型:\r\n");
    printf("1, 有向图 2, 无向图 3, 有向网 4, 无向网\n");
    printf("\033[40;31m输入格式为数字序号\033[0m\n");
    printf("\n请输入图的类型(1-4): ");
    scanf("%d", (int*)(&G->Kind));
    EOL;

    // 将顶点数据写入图的顶点数组
    for(int vi = 0; vi < G->VertexNum; vi++){
        setbuf(stdin, NULL);
        printf("请输入第%d个顶点名称: ",(vi + 1));
        scanf(" %c", &G->Vertex[vi].VD);
        G->Vertex[vi].FirstAdj = NULL;
    }

    printf("\n节点输入完毕, 输入个数为%d, 依次为\n", G->VertexNum);
    for(int vi = 0; vi < G->VertexNum; vi++)
        printf("%c ", G->Vertex[vi].VD);
    EOL;
    
    // 根据输入生成图的邻接链表
    printf("\n接下来输入弧, 有向图/网格式为:尾节点-->头节点, 无向图/网格式为:节点I--节点J\n");
    printf("例如:A-->B 或 M--K\n");

    if(G->Kind == DG || G->Kind == DN){
        printf("本图为\033[40;31m有向图/网\033[0m, 请以以下格式输入\n");
        printf("A-->B\n");
    }
    else{
        printf("本图为\033[40;31m无向图/网\033[0m, 请以以下格式输入\n");
        printf("M--K\n");
    }

    fgets(ArcStr, 8, stdin);
    while(1){
        setbuf(stdin, NULL);
        printf("请输入弧, 或者输入end结束添加弧: ");
        fgets(ArcStr, 8, stdin);

        if(ArcStr[0] == 'e' && ArcStr[1] == 'n' && ArcStr[2] == 'd' )
            break;
        else{
            if(G->Kind == DG || G->Kind == DN){
                IV = ArcStr[0]; JV = ArcStr[4];
            }
            else{
                IV = ArcStr[0]; JV = ArcStr[3];
            }

            I_Index = Locate_ALNode(G, IV);

            if(I_Index == -1)
                printf("图中不存在节点%c, 请重新输入\n", IV);
            else{
                J_Index = Locate_ALNode(G, JV);

                if(J_Index == -1)
                    printf("图中不存在节点%c, 请重新输入\n", JV);
                else{
                    CheckArc = G->Vertex[I_Index].FirstAdj;

                    while(CheckArc != NULL){
                        if(CheckArc->ANIdx == J_Index){
                            if(G->Kind == DG || G->Kind == DN)
                                printf("弧%c-->%c重复, 请重新输入\n", IV, JV);
                            else
                                printf("弧%c--%c重复, 请重新输入\n", IV, JV);

                            break;
                        }
                        else
                            CheckArc = CheckArc->NextAdj;
                    }
    
                    if(CheckArc == NULL){
                        AddArc = (ArcNodePtr_Type)malloc(sizeof(ArcNode_Type));
                        
                        if(G->Kind == DN){
                            printf("请输入弧%c-->%c的权重, 格式为\033[40;31m正整数\033[0m: ", IV, JV);
                            scanf(" %d", &(AddArc->AW));
                            // printf("AW: %d\n", AddArc->AW);
                        }
                        else if(G->Kind == UDN){
                            printf("请输入弧%c--%c的权重, 格式为\033[40;31m正整数\033[0m: ", IV, JV);
                            scanf(" %d", &(AddArc->AW));
                            // printf("AW: %d\n", AddArc->AW);
                        }
                        else
                            AddArc->AW = 0;

                        AddArc->AVD = JV;
                        AddArc->ANIdx = J_Index;
                        AddArc->NextAdj = G->Vertex[I_Index].FirstAdj;

                        G->Vertex[I_Index].FirstAdj = AddArc;
                        G->ArcNum++;
                        AddArc = NULL;
                    }
                }
            }
        }
    }
}

// 创建邻接表形式的有向图的逆向图
void Greate_Inverse_ALGraph(ALGraphPtr_Type G, ALGraphPtr_Type AG){
    ArcNodePtr_Type G_Arc, AG_Arc;

    if(G->Kind == UDG || G->Kind == UDN){
        printf("该图是无向图/网, 不需要生成逆向图");
        return ;
    }

    AG->ArcNum = G->ArcNum;
    AG->VertexNum = G->VertexNum;
    AG->Kind = G->Kind;
    
    for(int vi = 0; vi < G->VertexNum; vi++){
        AG->Vertex[vi].VD = G->Vertex[vi].VD;
        AG->Vertex[vi].FirstAdj = NULL;
    }

    for(int vi = 0; vi < G->VertexNum; vi++){
        G_Arc = G->Vertex[vi].FirstAdj;

        while(G_Arc != NULL){
            AG_Arc = (ArcNodePtr_Type)malloc(sizeof(ArcNode_Type));

            AG_Arc->ANIdx = vi;
            AG_Arc->AVD = G->Vertex[vi].VD;
            if(AG->Kind == DN)
                AG_Arc->AW = G_Arc->AW;

            AG_Arc->NextAdj = AG->Vertex[G_Arc->ANIdx].FirstAdj;
            AG->Vertex[G_Arc->ANIdx].FirstAdj = AG_Arc;

            G_Arc = G_Arc->NextAdj;
        }
    }
}

// 定位顶点在图的顶点数组的位置,成功返回下标,失败返回-1
int Locate_ALNode(ALGraphPtr_Type G, VertexData_Type VX){
    //对图的顶点数组遍历查找
    for(int VIndex = 0;VIndex < G->VertexNum; VIndex++)
        if(G->Vertex[VIndex].VD == VX)
            return VIndex;

    //未找到返回-1
    return -1;
}

// 定位弧在图的位置,成功返回指针,失败返回NULL
ArcNodePtr_Type Locate_Arc(ALGraphPtr_Type G, VertexData_Type SV, VertexData_Type EV){
    return NULL;
}

// 广度优先遍历邻接表形式的图
void Traverse_BFS_ALGraph(ALGraphPtr_Type G){

    for(int vi = 0; vi < G->VertexNum; vi++)
        S_Array[vi] = No;

    init_queue(&Arc_Queue);

    for(int vi = 0; vi < G->VertexNum; vi++)
        if(S_Array[vi] == No)
            BFS_ALGraph(G, vi);    
}

void BFS_ALGraph(ALGraphPtr_Type G, int VIndex){
    ArcNodePtr_Type S_Arc;
    ArcNode_Type Arc;

    if(S_Array[VIndex] == No){
        S_Array[VIndex] = Yes;
        // printf("visit_node: %c\n", G->Vertex[VIndex].VD);
    }

    S_Arc = G->Vertex[VIndex].FirstAdj;

    while(S_Arc != NULL){
        if(S_Array[S_Arc->ANIdx] == No){
            S_Array[S_Arc->ANIdx] = Yes;
            // printf("visit_node: %c\n", G->Vertex[S_Arc->ANIdx].VD);
            enter_queue(&Arc_Queue, *S_Arc);
        }
        S_Arc = S_Arc->NextAdj;
    }
    exit_queue(&Arc_Queue, &Arc);

    if(is_empty(&Arc_Queue) == false)
        BFS_ALGraph(G, Arc.ANIdx);
}

// 深度优先遍历邻接表形式的图
void Traverse_DFS_ALGraph(ALGraphPtr_Type G){
    for(int vi = 0; vi < G->VertexNum; vi++)
        S_Array[vi] = No;

    for(int vi = 0; vi < G->VertexNum; vi++)
        if(S_Array[vi] == No)
            DFS_ALGraph(G, vi);
}

void DFS_ALGraph(ALGraphPtr_Type G,int VIndex){
    ArcNodePtr_Type S_Arc;
    
    S_Array[VIndex] = Yes;
    printf("visit_node: %c\n", G->Vertex[VIndex].VD);

    S_Arc = G->Vertex[VIndex].FirstAdj;

    while(S_Arc != NULL){
        if(S_Array[S_Arc->ANIdx] == No)
            DFS_ALGraph(G, S_Arc->ANIdx);

        S_Arc = S_Arc->NextAdj;
    }
}

// 统计有向图某节点入度
int Count_Node_Indegree(ALGraphPtr_Type G, VertexData_Type NodeData){
    ArcNodePtr_Type Srch_Arc;
    int V_Index = 0, Indgree_Num = 0;

    V_Index = Locate_ALNode(G, NodeData);
    if(V_Index == -1)
        return -1;

    for(int vi = 0; vi < G->VertexNum; vi++){
        Srch_Arc = G->Vertex[vi].FirstAdj;

        while(Srch_Arc != NULL){
            if(Srch_Arc->ANIdx == V_Index)
                Indgree_Num++;

            Srch_Arc = Srch_Arc->NextAdj;
        }
    }

    return Indgree_Num;
}

// 统计有向图全部节点入度
void Count_All_Indegree(ALGraphPtr_Type G, int Indgree_Arr[]){
    for(int vi = 0; vi < G->VertexNum; vi++){
        Indgree_Arr[vi] = Count_Node_Indegree(G, G->Vertex[vi].VD);
        // printf("%c indgree: %d\n", G->Vertex[vi].VD, Indgree_Arr[vi]);
    }
}

// 统计有向图某节点入度
int Count_Node_Outdegree(ALGraphPtr_Type G, VertexData_Type NodeData){
    ArcNodePtr_Type Srch_Arc;
    int V_Index = 0, Outdgree_Num = 0;

    V_Index = Locate_ALNode(G, NodeData);
    if(V_Index == -1)
        return -1;
    
    Srch_Arc = G->Vertex[V_Index].FirstAdj;

    while(Srch_Arc != NULL){
        Outdgree_Num++;
        Srch_Arc = Srch_Arc->NextAdj;
    }

    return Outdgree_Num;
}

// 统计有向图全部节点入度
void Count_All_Outdegree(ALGraphPtr_Type G, int Outgree_Arr[]){
    for(int vi = 0; vi < G->VertexNum; vi++){
        Outgree_Arr[vi] = Count_Node_Outdegree(G, G->Vertex[vi].VD);
        // printf("%c outdegree: %d\n", G->Vertex[vi].VD, Outgree_Arr[vi]);
    }    
}

// 用顶点表示活动, 用有向弧表示活动间的优先关系的有向无环图称为顶点表示活动的网(Activity On Vertex Network AOV)

// 拓扑排序, 如果是正确的有向无环图(Directed Acyclic Graph DAG), 输出序列, 若为有环图, 打印错误提示
void TopoSort_ALGraph(ALGraphPtr_Type G){
    int Ind_Array[MAX_VERTEX_NUM] = {0};
    int visit_count = 0, v_idx = 0;
    ArcNodePtr_Type Topo_Arc;

    Count_All_Indegree(G, Ind_Array);

    putchar('(');

    do{
        v_idx = -1;

        // 查找第一个入度为0的节点
        for(int vi = 0; vi < G->VertexNum; vi++)
            if(Ind_Array[vi] == 0){
                v_idx = vi;
                Ind_Array[vi] = -1;
                break;
            }

        // 若找到入度为0的节点, 更新该节点相关联的其他节点的入度, 即-1
        if(v_idx != -1){
            
            Topo_Arc = G->Vertex[v_idx].FirstAdj;
            while(Topo_Arc != NULL){
                Ind_Array[Topo_Arc->ANIdx]--;
                Topo_Arc = Topo_Arc->NextAdj;
            }

            printf("%c ", G->Vertex[v_idx].VD);
            visit_count++;
        }

    }while(v_idx != -1);

    putchar(')');
    EOL;

    if(visit_count < G->VertexNum)
        printf("图/网是有环图, 无法给出拓扑序列\n");
}

// 用顶点表示事件, 用有向弧表示活动, 权表示活动时间的有向无环图称为边表示活动的网(Activity On Edge Network AOE)

// 修改的拓扑排序, 可以同时得到AOE网的每个事件的最早发生时间;
int TopoOrder_ALGraph(ALGraphPtr_Type G, int erly_t_array[], int topo_sris[]){
    int indg_array[MAX_VERTEX_NUM] = {0};
    int visit_count = 0, v_idx = 0, zero_id_count = 0;
    ArcNodePtr_Type Topo_Arc;

    Count_All_Indegree(G, indg_array);
    
    // 检查该有向网是否只有一个源点
    for(int vi = 0; vi < G->VertexNum; vi++)
        if(indg_array[vi] == 0){
            zero_id_count++;
            // 初始化关键路径节点最早发生时间表
            erly_t_array[vi] = 0;
        }
        else
            // 初始化关键路径节点最早发生时间表
            erly_t_array[vi] = -1;

    if(zero_id_count != 1){
        printf("该有向网有%d个源点, 不是AOE网\n", zero_id_count);
        return -1;
    }

    // 生成拓扑序列, 同时生成最早发生时间表
    do{
        v_idx = -1;

        // 查找第一个入度为0的节点
        for(int vi = 0; vi < G->VertexNum; vi++)
            if(indg_array[vi] == 0){
                v_idx = vi;
                indg_array[vi] = -1;
                break;
            }

        // 若找到入度为0的节点, 更新该节点的后继节点的入度, 即减1, 同时更新后继节点的最早发生时间
        if(v_idx != -1){
            Topo_Arc = G->Vertex[v_idx].FirstAdj;

            while(Topo_Arc != NULL){
                // 更新该节点的后继节点的入度
                indg_array[Topo_Arc->ANIdx]--;
                
                // 更新后继节点的最早发生时间            
                if(erly_t_array[Topo_Arc->ANIdx] < erly_t_array[v_idx] + Topo_Arc->AW)
                    erly_t_array[Topo_Arc->ANIdx] = erly_t_array[v_idx] + Topo_Arc->AW;
                    
                Topo_Arc = Topo_Arc->NextAdj;
            }
            topo_sris[visit_count] = v_idx;

            visit_count++;
        }

    }while(v_idx != -1);

    if(visit_count < G->VertexNum){
        printf("图/网是有环图, 无法给出拓扑序列\n");
        return -1;
    }

    return 0;
}

// 逆向AOE网的拓扑排序, 可以同时得到正向AOE网的每个事件的最晚发生时间;
int TopoOrder_Inverse_ALGraph(ALGraphPtr_Type AG, int late_t_array[]){
    int outdg_array[MAX_VERTEX_NUM] = {0};
    int v_idx = 0, zero_od_count = 0;
    ArcNodePtr_Type Topo_Arc;

    // 检查正向图是否只有一个汇点
    Count_All_Indegree(AG, outdg_array);

    for(int vi = 0; vi < AG->VertexNum; vi++){
        if(outdg_array[vi] == 0)
            zero_od_count++;
    }

    if(zero_od_count != 1){
        printf("该有向网有%d个源点, 不是AOE网\n", zero_od_count);
        return -1;
    }

    // 生成逆拓扑序列, 同时生成最晚发生时间表
    do{
        v_idx = -1;

        // 查找第一个出度为0的节点
        for(int vi = 0; vi < AG->VertexNum; vi++)
            if(outdg_array[vi] == 0){
                v_idx = vi;
                outdg_array[vi] = -1;
                break;
            }

        // 若找到入度为0的节点, 更新该节点的后继节点的入度, 即减1, 同时更新后继节点的最早发生时间
        if(v_idx != -1){
            Topo_Arc = AG->Vertex[v_idx].FirstAdj;

            while(Topo_Arc != NULL){
                // 更新该节点的后继节点的入度
                outdg_array[Topo_Arc->ANIdx]--;
                
                // 更新后继节点的最早发生时间            
                if(late_t_array[Topo_Arc->ANIdx] > late_t_array[v_idx] - Topo_Arc->AW)
                    late_t_array[Topo_Arc->ANIdx] = late_t_array[v_idx] - Topo_Arc->AW;
                    
                Topo_Arc = Topo_Arc->NextAdj;
            }
        }

    }while(v_idx != -1);

    return 0;
}

// 求AOE网的关键路径
int Critical_Path(ALGraphPtr_Type G){
    Graph_Type AG;
    int erly_t_array[MAX_VERTEX_NUM] = {0};
    int late_t_array[MAX_VERTEX_NUM] = {0};
    int topo_sris[MAX_VERTEX_NUM] = {0};
    int des_node_t = 0;

    // 检查图的类型
    if(G->Kind != DN){
        printf("此图不是有向网, 更不是AOE网, 不能生成关键路径\n");
        return -1; 
    }

    // 创建逆向图
    Greate_Inverse_ALGraph(G, &AG);

    // 拓扑排序, 生成拓扑序列和最早发生时间表
    TopoOrder_ALGraph(G, erly_t_array, topo_sris);
    
    // 初始化关键路径节点最晚发生时间为汇点的发生时间
    for(int vi = 0; vi < AG.VertexNum; vi++)
        if(erly_t_array[vi] > des_node_t)
            des_node_t = erly_t_array[vi];

    for(int vi = 0; vi < AG.VertexNum; vi++)
        late_t_array[vi] = des_node_t;
    
    // 拓扑排序, 生成逆拓扑序列和最晚发生时间表
    TopoOrder_Inverse_ALGraph(&AG, late_t_array);

    // 从时间小到大生成关键路径
    printf("关键路径: ");
    for(int vi = 0; vi < AG.VertexNum; vi++)
        if(late_t_array[topo_sris[vi]] == erly_t_array[topo_sris[vi]])
            printf("%c ", G->Vertex[topo_sris[vi]].VD);
    EOL;

    // 删除逆向图
    Destroy_ALGraph(&AG);

    return 0;
}

// 迪杰斯特拉算法求解最短路径
void Dijkstra(ALGraphPtr_Type G, VertexData_Type src_node){
    // 检查图的类型
    if(G->Kind != DN && G->Kind != UDN){
        printf("此图不是网, 没有路径长度\n");
        return ; 
    }

    if(Locate_ALNode(G, src_node) == -1){
        printf("没有该起始节点%c\n", src_node);
        return ;
    }

    Dijkstra_Array_Type adjct_arry[MAX_VERTEX_NUM] = {0};
    ArcNodePtr_Type Comp_Arc;
    int nxt_add_idx = 0;
    int shrtst_wght = 0;
    int shrtst_idx = -1;

    // 初始化辅助数组
    for(int vi = 0; vi < G->VertexNum; vi++){
        if(G->Vertex[vi].VD != src_node){
            adjct_arry[vi].dis = INFINITY;
            adjct_arry[vi].prev_idx = -1;
            adjct_arry[vi].isAdd = No;
        }
        else{
            adjct_arry[vi].dis = 0;
            adjct_arry[vi].prev_idx = vi;
            adjct_arry[vi].isAdd = Yes;
            nxt_add_idx = vi;
        }
    }

    // 广度优先搜索
    for(int i = 1; i <= G->VertexNum; i++){
        Comp_Arc = G->Vertex[nxt_add_idx].FirstAdj;
        shrtst_wght = INFINITY;

        // 更新已搜索的节点与邻接点的距离
        while(Comp_Arc != NULL){
            if(Comp_Arc->AW + adjct_arry[nxt_add_idx].dis < adjct_arry[Comp_Arc->ANIdx].dis){
                adjct_arry[Comp_Arc->ANIdx].dis = Comp_Arc->AW + adjct_arry[nxt_add_idx].dis;
                adjct_arry[Comp_Arc->ANIdx].prev_idx = nxt_add_idx;
            }

            Comp_Arc = Comp_Arc->NextAdj;
        }

        // 将最短的路径添加到与起始路径一起
        for(int vi = 0; vi < G->VertexNum; vi++){
            if(adjct_arry[vi].dis <= shrtst_wght && adjct_arry[vi].isAdd == No){
                shrtst_idx = vi;
                shrtst_wght = adjct_arry[vi].dis;
            }
        }

        adjct_arry[shrtst_idx].isAdd = Yes;
        nxt_add_idx = shrtst_idx;
    }

    for(int vi = 0; vi < G->VertexNum; vi++)
        printf("%c-->%c: %d\n", src_node, G->Vertex[vi].VD, adjct_arry[vi].dis);
}

// 弗洛伊德算法求解最短路径
void Floyd(ALGraphPtr_Type G, VertexData_Type src_node){
    int dist[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    ArcNodePtr_Type Init_Arc;

    // 初始化节点间距离为两点的直接距离
    for(int i = 0; i < G->VertexNum; i++)
        for(int j = 0; j < G->VertexNum; j++)
            if(i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INFINITY;

    for(int vi = 0; vi < G->VertexNum; vi++){
        Init_Arc = G->Vertex[vi].FirstAdj;

        while(Init_Arc != NULL){
            dist[vi][Init_Arc->ANIdx] = Init_Arc->AW;
            Init_Arc = Init_Arc->NextAdj;
        }
    }

    // 进行n次比较和修正
    for(int i = 0; i < G->VertexNum; i++){
        for(int j = 0; j < G->VertexNum; j++){
            for(int k = 0; k < G->VertexNum; k++){
                if(dist[j][k] > dist[j][i] + dist[i][k])
                   dist[j][k] = dist[j][i] + dist[i][k];
            }
        }
    }

    for(int i = 0; i < G->VertexNum; i++){
        for(int j = 0; j < G->VertexNum; j++)
            printf("%c-->%c: %d", G->Vertex[i].VD, G->Vertex[j].VD, dist[i][j]);
        EOL;
    }
}

// 添加顶点
void Add_ALNode(ALGraphPtr_Type G, VertexData_Type NodeData){
    // 检查是否超出限制大小
    if(G->VertexNum == MAX_VERTEX_NUM){
        printf("图中节点数目达到限定范围, 无法添加节点\n");
        return ;
    }
    // 检查是否重复
    if(Locate_ALNode(G, NodeData) != -1){
        printf("图中已存在此节点\n");
        return ;
    }

    G->Vertex[G->VertexNum++].VD = NodeData;
}

// 删除顶点
void Delete_ALNode(ALGraphPtr_Type G, VertexData_Type NodeData){
    if(Locate_ALNode(G, NodeData) == -1){
        printf("图中不存在此节点\n");
        return ;
    }
    for(int vi = 0; vi < G->VertexNum; vi++){
        if(G->Vertex[vi].VD != NodeData)
            Delete_ALArc(G, G->Vertex[vi].VD, NodeData);
        // 删除以顶点为头节点的全部弧
        else{

        }     
    }
    
    G->VertexNum--;
}

//添加弧, 如果不是网的话, 权重写0即可
void Add_ALArc(ALGraphPtr_Type G, VertexData_Type Head, VertexData_Type Tail, ArcWeight_Type AW){
    ArcNodePtr_Type AddArc, CheckArc;
    int I_Index, J_Index;
    
    // 检查节点是否存在
    if((I_Index = Locate_ALNode(G, Head)) == -1){
        printf("图中不存在节点%c\n", Head);
        return ;
    }

    if((J_Index = Locate_ALNode(G, Tail)) == -1){
        printf("图中不存在节点%c\n", Tail);
        return ;
    }

    // 检查弧是否存在
    CheckArc = G->Vertex[I_Index].FirstAdj;

    while(CheckArc != NULL){
        if(CheckArc->ANIdx == J_Index){
            if(G->Kind == UDG || G->Kind == UDN)
                printf("图中已存在该弧%c--%c\n", Head, Tail);
            else
                printf("图中已存在该弧%c-->%c\n", Head, Tail);
            return ;
        }
        CheckArc = CheckArc->NextAdj;
    }

    // 如果是无向图/网的话要双向检查
    if(G->Kind == UDG || G->Kind == UDN){
        CheckArc = G->Vertex[J_Index].FirstAdj;

        while(CheckArc != NULL){
            if(CheckArc->ANIdx == I_Index){
                printf("图中已存在该弧%c--%c\n", Head, Tail);
                return ;
            }
            CheckArc = CheckArc->NextAdj;
        }
    }

    // 添加弧
    AddArc = (ArcNodePtr_Type)malloc(sizeof(ArcNode_Type));
    AddArc->AVD = Tail;
    AddArc->AW = AW;
    AddArc->ANIdx = J_Index;
    AddArc->NextAdj = G->Vertex[I_Index].FirstAdj;
    G->Vertex[I_Index].FirstAdj = AddArc;

    G->ArcNum++;
}

// 搜索弧
ArcNodePtr_Type Search_ALArc(ALGraphPtr_Type G, VertexData_Type Head, VertexData_Type Tail){
    ArcNodePtr_Type Srch_Arc;
    int V_Index;

    V_Index = Locate_ALNode(G, Head);
    Srch_Arc = G->Vertex[V_Index].FirstAdj;

    while(Srch_Arc != NULL){
        if(Srch_Arc->AVD == Tail)
            return Srch_Arc;
        else
            Srch_Arc = Srch_Arc->NextAdj;
    }

    // 无向图/网还需要从尾端开始查找
    if(G->Kind == UDG || G->Kind == UDN){
        V_Index = Locate_ALNode(G, Tail);
        Srch_Arc = G->Vertex[V_Index].FirstAdj;

        while(Srch_Arc != NULL){
            if(Srch_Arc->AVD == Head)
                return Srch_Arc;
            else
                Srch_Arc = Srch_Arc->NextAdj;
        }   
    }

    return NULL;
}

// 删除弧
void Delete_ALArc(ALGraphPtr_Type G, VertexData_Type Head, VertexData_Type Tail){
    ArcNodePtr_Type DltArc, DltPrevArc;
    bool dlt_flag = false;
    int I_Index, J_Index;

    if((I_Index = Locate_ALNode(G, Head)) == -1){
        printf("图中不存在节点%c\n", Head);
        return ;
    }

    if((J_Index = Locate_ALNode(G, Tail)) == -1){
        printf("图中不存在节点%c\n", Tail);
        return ;
    }

    // 删除弧
    DltArc = G->Vertex[I_Index].FirstAdj;
    DltPrevArc = G->Vertex[I_Index].FirstAdj;

    while(DltArc != NULL){
        if(DltArc->ANIdx == J_Index){
            if(DltArc == G->Vertex[I_Index].FirstAdj)
                G->Vertex[I_Index].FirstAdj = NULL;
                
            DltPrevArc->NextAdj = DltArc->NextAdj;
            DltArc->NextAdj = NULL;
            dlt_flag = true;
            free(DltArc);
            G->ArcNum--;
            break;
        }
        DltPrevArc = DltArc;
        DltArc = DltArc->NextAdj;
    }

    // 如果是无向图/网要双边删除
    if(G->Kind == UDG || G->Kind == UDN){
        DltArc = G->Vertex[J_Index].FirstAdj;
        DltPrevArc = G->Vertex[J_Index].FirstAdj;

        while(DltArc != NULL){
            if(DltArc->ANIdx == I_Index){
                if(DltArc == G->Vertex[J_Index].FirstAdj)
                    G->Vertex[J_Index].FirstAdj = NULL;

                DltPrevArc->NextAdj = DltArc->NextAdj;
                DltArc->NextAdj = NULL;
                dlt_flag = true;
                free(DltArc);
                G->ArcNum--;
                break;
            }
            DltPrevArc = DltArc;
            DltArc = DltArc->NextAdj;
        }
    }

    // 如果在没有删除弧, 说明图中不存在该弧
    if(dlt_flag != true){
        if(G->Kind == UDG || G->Kind == UDN)
            printf("不存在弧%c--%c\n", Head, Tail);
        else
            printf("不存在弧%c-->%c\n", Head, Tail);
    }
}

// 普里姆算法得到连通图的最小生成树
void MiniSpanTree_Prim(ALGraphPtr_Type G, VertexData_Type Start_V){
    ArcNodePtr_Type SrchArc;
    Closedge_Type MiniumEdge;
    Closedge_Type closedge[MAX_VERTEX_NUM]; 
    int Start_V_Index, MiniumEdge_Index;

    // 初始化
    Start_V_Index = Locate_ALNode(G, Start_V);
    closedge[Start_V_Index].W = 0;

    for(int vi = 0; vi < G->VertexNum; vi++){
        if(G->Vertex[vi].VD != Start_V){
            SrchArc = Search_ALArc(G, Start_V, G->Vertex[vi].VD);
            
            if(SrchArc != NULL){
                closedge[vi].W = SrchArc->AW;
                closedge[vi].adjver_Index = Start_V_Index;
            }
            else{
                closedge[vi].W = INFINITY;
                closedge[vi].adjver_Index = Start_V_Index;
            }
        }
    }

    // 找n-1条边
    for(int e = 0; e < G->VertexNum - 1; e++){
        // 查找最短的边
        MiniumEdge.adjver_Index = -1;
        MiniumEdge.W = INFINITY;

        for(int vi = 0; vi < G->VertexNum; vi++)
            if (closedge[vi].W < MiniumEdge.W && closedge[vi].W != 0){
                MiniumEdge_Index = vi;
                MiniumEdge = closedge[vi];
            }

        // 如果找到边, 将边加入生成树中
        if(MiniumEdge.W != INFINITY){
            closedge[MiniumEdge_Index].W = 0;
            printf("SpanTreeArc: %c--%c\n", G->Vertex[closedge[MiniumEdge_Index].adjver_Index].VD, G->Vertex[MiniumEdge_Index].VD);

            // 更新权重
            for(int vi = 0; vi < G->VertexNum; vi++){
                SrchArc = Search_ALArc(G, G->Vertex[MiniumEdge_Index].VD, G->Vertex[vi].VD);
                if(SrchArc != NULL){
                    if(SrchArc->AW < closedge[vi].W){
                        closedge[vi].W = SrchArc->AW;
                        closedge[vi].adjver_Index = MiniumEdge_Index;
                    }
                }
            }
        }        
    }
}

// 克鲁斯卡尔算法得到连通图的最小生成树
void MiniSpanTree_Kerus(ALGraphPtr_Type G){
    // 从小到大排序
}

// 删除图
void Destroy_ALGraph(ALGraphPtr_Type G){
    ArcNodePtr_Type DeleteArc;           //声明删除弧节点指针

    // 依次对图的顶点数组的元素释放内存
    for(int vi = 0; vi < G->VertexNum; vi++){       
        // 指向顶点的首弧节点
        DeleteArc = G->Vertex[vi].FirstAdj;

        // 释放弧节点直到首弧节点为空
        if(DeleteArc != NULL){
            while(DeleteArc->NextAdj != NULL){
                // 删除指针指向辅助删除指针指向的节点
                G->Vertex[vi].FirstAdj = DeleteArc->NextAdj;
                DeleteArc->NextAdj = NULL;

                // 释放弧节点
                free(DeleteArc);
                DeleteArc = G->Vertex[vi].FirstAdj;
            }
            free(G->Vertex[vi].FirstAdj);
        }
    }
    // 将弧节点数设为0
    G->ArcNum = 0;
    // 删除图的类型
    G->Kind = NotSet;
}
