#include "BSTree.h"
#include <string.h>

//宏定义换行
#define EOL putchar('\n')

//回调函数CALLBACK参数函数,打印节点数据
extern int nest;
void print(datatype e)
{
    for(int i = nest; i > 1; i--)
        printf("  ");

    printf("%d\n",e);
}

int main(){
    //声明二叉树树根
    BSTree BST = NULL;                       

    //初始化二叉树
    Creat_BST(&BST);

    // 插入节点
    Add_Node(&BST, 4);

    // 遍历二叉树
    DLR_Traverse_BST(BST, print);

    //删除二叉树，释放内存空间
    Destroy_BST(BST);

    return 0;
}