#include "HuffmanTree.h"

//创建一个哈夫曼树,返回值为哈夫曼树节点个数
int Creat_HT(HuffmanTree HT,const int* HuffmanWeight,const int WeightNum)
{
    //初始化哈夫曼树,将1到WeightNum号设置对应权值,作为叶节点;
    for(int i=1;i<=WeightNum;i++)
    {    
        HT[i].weight=HuffmanWeight[i];
        HT[i].LeftChild=HT[i].parent=HT[i].RightChild=0;
    }

    //哈夫曼树最终会有2n-1个节点
    int HTNodeNum=2*WeightNum-1;

    //将WeightNum之后节点权值暂时设为0
    for(int i=WeightNum+1;i<=HTNodeNum;i++)
        HT[i].LeftChild=HT[i].RightChild=HT[i].weight=HT[i].parent=0;

    //构造哈夫曼树
    for(int i=1;i<=WeightNum-1;i++)
    {
        int minweight=0,secondminweight=0;
        HT[0].weight=INFINITY;

        //选出森林中权重最小的根
        for(int j=1;j<=WeightNum+i-1;j++)
        {
            if(HT[j].weight<HT[minweight].weight&&HT[j].parent==0)
                minweight=j;
        }

        //选出森林中权重第二小的根
        for(int j=1;j<=WeightNum+i-1;j++)
        {
            if(HT[j].weight<HT[secondminweight].weight&&HT[j].parent==0&&j!=minweight)
                secondminweight=j;
        }

        //构造新的根节点和树
        HT[i+WeightNum].weight=HT[minweight].weight+HT[secondminweight].weight;
        HT[i+WeightNum].LeftChild=minweight;
        HT[i+WeightNum].RightChild=secondminweight;

        //设置叶节点的父节点
        HT[minweight].parent=HT[secondminweight].parent=i+WeightNum;
    }

    //返回哈夫曼树节点个数
    return HTNodeNum;
}

//调用回调函数遍历哈夫曼树
void Traverse_HT(const HuffmanTree HT,const int NodeNum,CALLBACK visitnode)
{
    //先输出哈夫曼树项目
    printf(" 权重  父节点  左子节点 右子节点\n");

    //调用回调函数visitnode,遍历每一个哈夫曼树节点
    for(int i=1;i<=NodeNum;i++)
    {
        visitnode(HT[i]);
    }
}

//调用先序递归,根据哈夫曼树创建哈夫曼编码
void Creat_HuffmanCode(const HuffmanTree HT,HuffmanCodeTable HCTable,const int CodeNum)
{

    static int TableIndex=13;               //声明哈夫曼表下标
    static char Code[6+1]={0};              //声明并0初始化某一维的哈夫曼代码
    static int CharIndex=0;                 //声明哈夫曼代码数组下标

    //如果哈夫曼表下标小于等于哈夫曼代码个数,说明已经到达叶节点,将哈夫曼代码写入哈夫曼表对应位置
    if(TableIndex<=CodeNum)
    {
        Code[CharIndex]='\0';
        strcpy(HCTable[TableIndex],Code);

        //改回下标退回上一级
        CharIndex--;
        TableIndex=HT[TableIndex].parent;
        return ;
    }

    //若未达到叶节点,则依次递归左右子树

    //将本深度节点对应位数的哈夫曼代码设为0,并转入左子树
    Code[CharIndex]='0';
    
    //深度加1,下标加1
    CharIndex++;
    //递归左子树
    TableIndex=HT[TableIndex].LeftChild;
    Creat_HuffmanCode(HT,HCTable,CodeNum);

    
    //将本深度节点对应位数的哈夫曼代码设为1,并转入右子树
    Code[CharIndex]='1';

    //深度加1,下标加1
    CharIndex++;
    //递归左子树
    TableIndex=HT[TableIndex].RightChild;
    Creat_HuffmanCode(HT,HCTable,CodeNum);

    //改回下标退回上一级
    CharIndex--;
    TableIndex=HT[TableIndex].parent;
    return ;
}

//遍历哈夫曼编码
void Traverse_HCTable(const HuffmanTree HT,const HuffmanCodeTable HCTable,const int CodeNum)
{
    for(int i=1;i<=CodeNum;i++)
        printf("%d权重的数据哈夫曼编码为%s\n",HT[i].weight,HCTable[i]);
}