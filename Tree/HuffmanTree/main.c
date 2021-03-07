#include "HuffmanTree.h"

#define EOL putchar('\n')
#define WeightNum 7

//打印哈夫曼树节点
void printnode(HTNode data)
{
    printf("%4d%8d%10d%10d",data.weight,data.parent,data.LeftChild,data.RightChild);
    EOL;
}

int main()
{
    int HTWeight[WeightNum+1]={-1,88,2,5,12,65,54,32};
    int HTNodeNum=WeightNum*2+1;
    int CodeNum=WeightNum;
    HuffmanTree HT;
    HuffmanCodeTable HCTable;

    //创建哈夫曼树
    HTNodeNum=Creat_HT(HT,HTWeight,7);
    //遍历哈夫曼树
    Traverse_HT(HT,HTNodeNum,printnode);
    
    //根据哈夫曼树创建哈夫曼代码表
    Creat_HuffmanCode(HT,HCTable,CodeNum);
    //遍历哈夫曼代码表
    Traverse_HCTable(HT,HCTable,CodeNum);
    return 0;
}
