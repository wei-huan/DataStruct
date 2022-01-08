#include "RBTree.h"
#include <string.h>

//宏定义换行
#define EOL putchar('\n')

//回调函数CALLBACK参数函数,打印节点数据
extern int nest;
void print(RBNode node){

    if(node.color == red){
        for(int i = nest; i > 1; i--)
            printf("\033[40;31m  \033[0m");
        
        if(node.parent)
            printf("\033[40;31m%d: par: %d\n\033[0m", node.data, node.parent->data);
        else
            printf("\033[40;31m%d\n\033[0m", node.data);
    }
    else{
        for(int i = nest; i > 1; i--)
            printf("\033[47;30m  \033[0m");

        if(node.parent)
            printf("\033[47;30m%d: par: %d\n\033[0m", node.data, node.parent->data);
        else
            printf("\033[47;30m%d\n\033[0m", node.data);
    }
}

int main(){
    //声明二叉树树根
    RBTree RBT = NULL;                       

    //初始化二叉树
    Creat_RBT(&RBT);

    DLR_Traverse_RBT(RBT, print);
    EOL;
    
    // 删除结点
    char str[100];
    int node_val;

    while(1){
        printf("请输入要删除节点的值或q结束: ");
        scanf("%s", str);

        if(!strcmp(str, "quit") || !strcmp(str, "q"))
            break;

        node_val = atoi(str);
        Del_Node(&RBT, node_val);
        DLR_Traverse_RBT(RBT, print);
        EOL;
    }


    //删除二叉树，释放内存空间
    Destroy_RBT(RBT);

    return 0;
}
