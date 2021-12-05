#include "AVLTree.h"
#include <string.h>

//宏定义换行
#define EOL putchar('\n')

//回调函数CALLBACK参数函数,打印节点数据
extern int nest;
void print(AVLNode node)
{
    for(int i = nest; i > 1; i--)
        printf("  ");

    printf("%d: h: %d bf: %d\n", node.data, node.height, node.bf);
}

int main(){
    //声明二叉树树根
    AVLTree AVLT = NULL;                       

    //初始化二叉树
    Creat_AVLT(&AVLT);

    // Add_Node(&AVLT, 5);
    // // 遍历二叉树
    // DLR_Traverse_AVLT(AVLT, print);
    // EOL;

    // Add_Node(&AVLT, 4);
    // // 遍历二叉树
    // DLR_Traverse_AVLT(AVLT, print);
    // EOL;

    // Add_Node(&AVLT, 6);
    // // 遍历二叉树
    // DLR_Traverse_AVLT(AVLT, print);
    // EOL;

    // Add_Node(&AVLT, 3);
    // // 遍历二叉树
    // DLR_Traverse_AVLT(AVLT, print);
    // EOL;

    // Add_Node(&AVLT, 7);
    // // 遍历二叉树
    // DLR_Traverse_AVLT(AVLT, print);
    // EOL;

    // Add_Node(&AVLT, 8);
    // // 遍历二叉树
    DLR_Traverse_AVLT(AVLT, print);
    EOL;

    //删除二叉树，释放内存空间
    Destroy_AVLT(AVLT);

    return 0;
}