#include "AML_Graph.h"

//创建邻接多重表形式的图
void Create_AMLGraph(Graph *G,
                     const VertexData VXList[VERTEX_NUM],
                     const VertexData AdjastVXChart[VERTEX_NUM][VERTEX_NUM],
                     const int vxnum,
                     const GraphKind kind)
{
    ArcNode *AddArc=NULL,*SearchAidArc=NULL,*DeleteArc=NULL;             //声明添加弧节点指针和辅助搜索指针
    int JIndex=-1;                                                       //声明并初始化弧头顶点对应下标                    

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
        //顶点邻接弧节点先设为NULL
        G->Vertex[i].Firstedge=NULL;
    }

    //根据邻接顶点二维表循环生成图的邻接多重表

    //大循环,按行循环邻接顶点二维表
    for(int i=0;i<vxnum;i++)
    { 
        //将搜索弧指针先指向顶点数组第i列首弧节点
        AddArc=G->Vertex[i].Firstedge;

        //如果首弧节点不为空,指向链表尾
        while(AddArc!=NULL)
        {
            //下一个指向取决于邻接点数据放在I位置还是J位置
            if(i==AddArc->IVex)
                AddArc=AddArc->ILink;
            else
                AddArc=AddArc->JLink;
        }
                  
        //小循环,按列循环邻接顶点二维表
        for(int j=0;j<vxnum;j++)
        {
            //如果邻接顶点二维表Aij元素在A到Z范围内且不等于本顶点,则判断能否定位到该顶点
            if('A'<=AdjastVXChart[i][j]&&AdjastVXChart[i][j]<='Z'&&AdjastVXChart[i][j]!=G->Vertex[i].VD)
            {    
                //获取要写入的邻接点在顶点数组的下标
                JIndex=Locate_AMLNode(G,AdjastVXChart[i][j]);

                //如果定位不到到该顶点,报错,退出程序
                if(JIndex==-1)
                {
                    printf("无此节点\n");
                    exit(0);
                }
                //如果定位到该节点,写入数据到指针AddArc指向的空间
                else
                {   
                    //为邻接顶点分配空间
                    AddArc=(ArcNode*)malloc(sizeof(ArcNode));

                    //写入弧头顶点对应下标
                    AddArc->JVex=JIndex;
                    //写入弧尾顶点对应下标
                    AddArc->IVex=i;
                    //搜索标志初始为No
                    AddArc->SMark=No;

                    //写入弧头顶点对应顶点数组的首弧节点的链表
                    SearchAidArc=G->Vertex[JIndex].Firstedge;
                    //找到链表的尾部
                    while(SearchAidArc!=NULL)
                    {
                        //如果有重复弧,跳出循环
                        if(SearchAidArc->IVex==AddArc->JVex&&SearchAidArc->JVex==AddArc->IVex)
                            break;
                        
                        //下一个指向取决于邻接点数据放在I位置还是J位置
                        if(JIndex==SearchAidArc->IVex)
                            SearchAidArc=SearchAidArc->ILink;
                        else
                            SearchAidArc=SearchAidArc->JLink;
                    }

                    //如果搜索辅助弧指针不为空,说明从while循环跳出,有重复弧,不链接,删除此弧
                    if(SearchAidArc!=NULL)
                    {
                        //将删除弧指针指向添加弧指针
                        DeleteArc=AddArc;

                        //将添加弧指针指向要删除的弧节点前一个节点
                        AddArc=G->Vertex[i].Firstedge;

                        //如果首弧节点不为空,指向链表尾
                        while(AddArc->ILink!=DeleteArc&&AddArc->JLink!=DeleteArc)
                        {
                            //下一个指向取决于邻接点数据放在I下标还是J下标
                            if(i==AddArc->IVex)
                                AddArc=AddArc->ILink;
                            else
                                AddArc=AddArc->JLink;
                        }  

                        //添加弧断开与要删除的弧的连接
                        if(AddArc->ILink==DeleteArc)
                            AddArc->ILink=NULL;
                        else
                            AddArc->JLink=NULL;

                        //释放删除弧
                        free(DeleteArc);
                    }
                    //无重复弧,则链接         
                    else
                    {   
                        //链接
                        SearchAidArc=AddArc;

                        //暂设同头弧节点为空
                        AddArc->ILink=NULL;
                        //暂设同尾弧节点为空
                        AddArc->JLink=NULL;

                        //搜索弧指向下一个同下标弧节点
                        AddArc=AddArc->ILink;
                    
                        //弧个数加1
                        G->ArcNum++;
                    }
                }
            }

            //如果邻接顶点二维表Aij元素不符合要求,跳出小循环
            else break;
        }
    }
}

//定位顶点在图的顶点数组的位置,成功返回下标,失败返回-1
int Locate_AMLNode(Graph *G,VertexData VX)
{
    //对图的顶点数组遍历查找
    for(int VIndex=0;VIndex<G->VertexNum;VIndex++)
        if(G->Vertex[VIndex].VD==VX)
            return VIndex;

    //未找到返回-1
    return -1;
}

//遍历邻接多重表形式的图
void Traverse_AMLGraph(Graph *G)
{
    ;
}

void Test_Draw(Graph *G,CALLBACK visit)
{
    ArcNodePtr SearchArc;

    SearchArc=G->Vertex[0].Firstedge;

    while(SearchArc!=NULL)
    {
        visit(G->Vertex[SearchArc->IVex].VD,G->Vertex[SearchArc->JVex].VD);
        SearchArc=SearchArc->ILink;
    }
}

//添加顶点
void Add_AMLNode(Graph *G,VertexData NodeData)
{
    ;
}

//删除顶点
void Delete_AMLNode(Graph *G,VertexData NodeData)
{
    ;
}

//添加弧
void Add_AMLArc(Graph *G,VertexData Head,VertexData Tail)
{
    ;
}

//删除弧
void Delete_AMLArc(Graph *G,VertexData Head,VertexData Tail)
{
    ;
}

//删除图
void Delete_AMLGraph(Graph *G)
{
    ArcNodePtr DeletePtr,SetNullPtr;                 //声明删除弧指针和设空弧指针

    //依次对顶点数组的顶点删除弧节点
    for(int i=0;i<G->VertexNum;i++)
    {
        //删除弧指针指向某行顶点的首弧节点
        DeletePtr=G->Vertex[i].Firstedge;
        //首弧节点指针与弧结构体断开连接
        G->Vertex[i].Firstedge=NULL;

        //以首弧节点为起始,以包含G->Vertex[i].VD的弧方向为线索,删除邻接的弧
        while(DeletePtr!=NULL)
        {
            //释放本弧节点之前要断开另一个方向的连接

            //如果J下标对应数组顶点的首弧节点为要删除的弧,直接断开连接
            if(G->Vertex[DeletePtr->JVex].Firstedge==DeletePtr)
                G->Vertex[DeletePtr->JVex].Firstedge=NULL;
            //如果I下标对应数组顶点的首弧节点为要删除的弧,直接断开连接
            else if(G->Vertex[DeletePtr->IVex].Firstedge==DeletePtr)
                G->Vertex[DeletePtr->IVex].Firstedge=NULL;
            //否则根据另一方向查找要删除的节点前一位
            else
            {
                //设空弧指针指向弧连的另一个顶点对应顶点数组的首弧节点
                if(i==DeletePtr->IVex)
                    SetNullPtr=G->Vertex[DeletePtr->JVex].Firstedge;
                else if(i==DeletePtr->JVex)
                    SetNullPtr=G->Vertex[DeletePtr->IVex].Firstedge;

                //如果查找的本级弧节点不指向要删除的弧节点,继续查找
                while (SetNullPtr->ILink!=DeletePtr&&SetNullPtr->JLink!=DeletePtr&&SetNullPtr!=NULL)
                {
                    //如果i下标在要删除弧的I方向,设空弧应该查找对应删除弧的J方向
                    if(i==DeletePtr->IVex)
                    {
                        if(SetNullPtr->IVex==DeletePtr->JVex)
                            SetNullPtr=SetNullPtr->ILink;
                        else if(SetNullPtr->JVex==DeletePtr->JVex)
                            SetNullPtr=SetNullPtr->JLink;
                    }
                    //如果i下标在要删除弧的J方向,设空弧应该查找对应删除弧的I方向
                    else
                    {
                        if(SetNullPtr->IVex==DeletePtr->IVex)
                            SetNullPtr=SetNullPtr->ILink;
                        else if(SetNullPtr->JVex==DeletePtr->IVex)
                            SetNullPtr=SetNullPtr->JLink;
                    }
                }
                
                //找到要断开的弧节点,如果是I方向连接,断开I方向的指针
                if(SetNullPtr->ILink==DeletePtr)
                    SetNullPtr->ILink=NULL;
                //否则断开J方向
                else if(SetNullPtr->JLink==DeletePtr)
                    SetNullPtr->JLink=NULL;
            }
            
            //设空弧指针暂存要删除弧
            if(i==DeletePtr->IVex)
                SetNullPtr=DeletePtr->ILink;
            else if(i==DeletePtr->JVex)
                SetNullPtr=DeletePtr->JLink;

            //释放要删除的弧
            free(DeletePtr);

            //删除弧指向下一个要删除的弧
            DeletePtr=SetNullPtr;
        }
    }

    //图节点数设为0
    G->VertexNum=0;
    //图类型树设为未设置
    G->Kind=NotSet;
}