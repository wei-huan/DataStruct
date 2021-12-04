#include "BSTree.h"
#include <string.h>

//宏定义换行
#define EOL putchar('\n')
//宏定义获取二叉树生成的数据文件的数组长度和读取二叉树生成的数据文件的最大长度
#define MAX_Read_Num 100+1

//回调函数CALLBACK参数函数,打印节点数据
void print(datatype e)
{
    printf("%c",e);
}

int main()
{
    BSTree BST = NULL;                       //声明二叉树树根
    int length=0,count=0;                   //声明数据数组可用于创建二叉树的数据个数,以及计数二叉树的节点个数

    //初始化二叉树
    BST = Creat_BST();

    //删除二叉树，释放内存空间
    Destroy_BST(BST);
    return 0;
}