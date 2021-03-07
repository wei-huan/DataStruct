#include "BiTree.h"
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
    FILE *fp;                               //声明文件指针
    BiTree BT;                              //声明二叉树树根
    bool flag;                              //声明布尔标志
    char BTData[MAX_Read_Num];              //声明创建二叉树的数据数组
    int length=0,count=0;                   //声明数据数组可用于创建二叉树的数据个数,以及计数二叉树的节点个数

    //打开储存生成二叉树的数据文件
    fp=fopen("bitree.txt","r");

    //若文件打开失败，打印错误并结束程序，否则继续程序
    if(fp==NULL)
    {
        printf("文件打开失败");
        EOL;
        exit(0);
    }

    //从bitree.txt文件中一行一行读取数据
    while(fgets(BTData,MAX_Read_Num,fp)!=NULL)
    {
        //去除BTData最后的换行符
        length=strlen(BTData);
        BTData[length-1]='\0';

        //初始化二叉树
        Init_BT(&BT);

        //为二叉树写入数据
        flag=Creat_Complt_BT(BT,BTData);
    
        //如果写入失败，打印错误，结束程序；若成功继续
        if(flag==false)
        {    
            printf("创建二叉树失败");
            EOL;
            exit(0);
        }    
        else
        {
            // //测试搜索节点函数
            // if(Get_Node_Parent(BT,'E',&N)==true)
            //     printf("true,find %c\n",N->Data);

            // //测试添加节点函数
            // Add_Node_LChild(BT,'D','H');
            // Add_Node_LChild(BT,'H','I');

            // //测试添加节点后搜索节点函数是否正常
            // if(Get_Node_Parent(BT,'I',&N)==true)
            //     printf("true,find %c\n",N->Data);
            
            // //测试删除节点函数
            // Del_Node(BT,'I');

            //三种顺序遍历二叉树，打印数据
            //递归方式
            DLR_Traverse_BT(BT,print);
            EOL;
            //栈方式
            DLR_Traverse_BT_Stack(BT,print);
            EOL;
            //递归方式
            LDR_Traverse_BT(BT,print);
            EOL;
            //栈方式
            LDR_Traverse_BT_Stack(BT,print);
            EOL;
            //递归方式
            LRD_Traverse_BT(BT,print);
            EOL;
            //栈方式
            LRD_Traverse_BT_Stack(BT,print);
            EOL;
            
            //测试二叉树深度函数
            printf("二叉树深度为%d\n",Get_Height(BT));
            
            //测试节点计数函数
            Count_Node(BT,&count);
            printf("二叉树节点个数为%d\n",count);

        }

        //删除二叉树，释放内存空间
        Destroy_BT(BT);
        BT=NULL;
    }

    //关闭文件
    fclose(fp);

    return 0;
}