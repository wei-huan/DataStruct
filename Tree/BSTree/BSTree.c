#include "BSTree.h"
#include <string.h>

BSNode* Allocate_Node(){
    BSNode* node = (BSNode*)malloc(sizeof(BSNode));
    return node;
}

// 创建二叉排序树
BSTree Creat_BST(){
    
    char str[100];
    int node_val;
    printf("创建二叉排序树, 请输入节点的值(整形), 输入q或者quit完成创建\n");

    while(1){
        printf("请输入节点的值: ");
        scanf("%s", str);

        if(!strcmp(str, "quit") || !strcmp(str, "q"))
            break;

        node_val = atoi(str);
    }
}

//清除二叉树的所有节点，不包括根节点，即回到初始化后状态
void Clear_BST(BSTree root)
{
    Destroy_BST(root->LeftChild);
    Destroy_BST(root->RightChild);
    root->Data='.';

    return ;
}

//后序递归删除二叉树
void Destroy_BST(BSTree root)
{
    if(root==NULL)
        return ;
    
    Destroy_BST(root->LeftChild);
    Destroy_BST(root->RightChild);
    free(root);

    return ;
}

//检查树是否为空树
bool is_BST_Empty(BSTree root)
{
    if(root==NULL)
        return true;
    else 
        return false;
}

//检查节点是否为叶节点
bool is_Node_Leaf(BSTree root,const datatype data)
{
    if(IF_LEAF(root)==true)
        return true;

    return false;
}

//添加第一个数据为data的节点的左孩子
bool Add_Node_LChild(BSTree root,const datatype data,const datatype add_data)
{
    BSTree getnode;

    //调用GET_Node函数先找到该节点,如果没找到,报错,返回false
    if(Get_Node(root,data,&getnode)==false)
    {
        printf("二叉树无此节点\n");
        return false;
    }

    //如果该节点的左子节点不为空,报错,返回false
    if(getnode->LeftChild!=NULL)
    {
        printf("二叉树此节点%c已有左孩子\n",data);
        return false;
    }   

    //如果该节点的左子节点为空,则为其分配空间
    getnode->LeftChild=(BSNode*)malloc(sizeof(BSNode));

    //左子节点赋值给指针getnode
    getnode=getnode->LeftChild;

    //为getnode写入数据
    getnode->Data=add_data;
    getnode->LeftChild=NULL;
    getnode->RightChild=NULL;

    return true;
}

//添加第一个数据为data的节点的右孩子
bool Add_Node_RChild(BSTree root,const datatype data,const datatype add_data)
{   
    //声明一个节点指针
    BSTree getnode;
    
    //调用GET_Node函数先找到该节点,如果没找到,报错,返回false
    if(Get_Node(root,data,&getnode)==false)
    {
        printf("二叉树无此节点\n");
        return false;
    }

    //如果该节点的右子节点不为空,报错,返回false
    if(getnode->RightChild!=NULL)
    {
        printf("二叉树此节点%c已有右孩子\n",data);
        return false;
    }   

     //如果该节点的右子节点为空,则为其分配空间
    getnode->RightChild=(BSNode*)malloc(sizeof(BSNode));

    //右子节点赋值给指针getnode
    getnode=getnode->RightChild;

    //为getnode写入数据
    getnode->Data=add_data;
    getnode->LeftChild=NULL;
    getnode->RightChild=NULL;

    return true;
}

//删除一个节点及其子节点
bool Del_Node(BSTree root,const datatype data)
{
    //声明一个节点指针,一个辅助指针,辅助指针用于断开需删除节点与父节点的联系
    BSTree getnode,aidnode;

    //调用Get_Node函数,如果不存在该节点,报错,返回false
    if(Get_Node(root,data,&getnode)==false)
    {
        printf("二叉树无此节点\n");
        return false;
    }

    //调用Get_Node_Parent函数,如果不存在,报错,返回false
    if(Get_Node_Parent(root,data,&aidnode)==false)
    {
        printf("二叉树无此父节点\n");
        return false;
    }
    
    //要删除的节点断开和父节点的关系
    if(aidnode->LeftChild==getnode)
        aidnode->LeftChild=NULL;
    else
        aidnode->RightChild=NULL;

    //调用Destroy_BST删除以getnode为根的二叉树
    Destroy_BST(getnode);

    return true;
}

//删除一个节点的左孩子及其子节点
bool Del_Node_LChild(BSTree root,const datatype data)
{
    //声明一个节点指针,一个辅助指针,辅助指针用于断开需删除节点与父节点的联系
    BSTree getnode,aidnode;

    //调用Get_Node函数,如果不存在该节点,报错,返回false
    if(Get_Node(root,data,&getnode)==false)
    {
        printf("二叉树无此节点\n");
        return false;
    }

    //要删除的节点断开和父节点的关系
    aidnode=getnode->LeftChild;
    getnode->LeftChild=NULL;

    //调用Destroy_BST删除以getnode左孩子为根的二叉树
    Destroy_BST(aidnode);

    return true;
}

//删除一个节点的右孩子及其子节点
bool Del_Node_RChild(BSTree root,const datatype data)
{
    //声明一个节点指针,一个辅助指针,辅助指针用于断开需删除节点与父节点的联系
    BSTree getnode,aidnode;

    //调用Get_Node函数,如果不存在该节点,报错,返回false
    if(Get_Node(root,data,&getnode)==false)
    {
        printf("二叉树无此节点\n");
        return false;
    }

    //要删除的节点断开和父节点的关系
    aidnode=getnode->RightChild;
    getnode->RightChild=NULL;

    //调用Destroy_BST删除以getnode左孩子为根的二叉树
    Destroy_BST(aidnode);

    return true;
}

//先序遍历二叉树,调用回调函数访问节点数据
void DLR_Traverse_BST(BSTree root,CALLBACK visit)
{
    if(root==NULL||root->Data=='.')
        return ;

    visit(root->Data);
    DLR_Traverse_BST(root->LeftChild,visit);
    DLR_Traverse_BST(root->RightChild,visit);

    return ;
}

//带调用回调函数筛选条件的先序遍历二叉树,调用回调函数访问节点数据
void DLR_Traverse_BST_IF(BSTree root,CALLBACK visit,PREDICATE judge)
{
    if(root==NULL)
        return ;

    if(judge(root)==true)
        visit(root->Data);

    DLR_Traverse_BST_IF(root->LeftChild,visit,judge);
    DLR_Traverse_BST_IF(root->RightChild,visit,judge);

    return ;
}

//中序遍历二叉树,调用回调函数访问节点数据
void LDR_Traverse_BST(BSTree root,CALLBACK visit)
{
    if(root==NULL||root->Data=='.')
        return ;

    LDR_Traverse_BST(root->LeftChild,visit);
    visit(root->Data);
    LDR_Traverse_BST(root->RightChild,visit);
}

//带调用回调函数筛选条件的中序遍历二叉树,调用回调函数访问节点数据
void LDR_Traverse_BST_IF(BSTree root,CALLBACK visit,PREDICATE judge)
{
    if(root==NULL)
        return ;
    
    LDR_Traverse_BST_IF(root->LeftChild,visit,judge);

    if(judge(root)==true)
        visit(root->Data);

    LDR_Traverse_BST_IF(root->RightChild,visit,judge);

    return ;
}

//后序遍历二叉树,调用回调函数访问节点数据
void LRD_Traverse_BST(BSTree root,CALLBACK visit)
{   
    if(root==NULL||root->Data=='.')
        return ;
    
    LRD_Traverse_BST(root->LeftChild,visit);
    LRD_Traverse_BST(root->RightChild,visit);
    visit(root->Data);
}

//带调用回调函数筛选条件的后序遍历二叉树,调用回调函数访问节点数据
void LRD_Traverse_BST_IF(BSTree root,CALLBACK visit,PREDICATE judge)
{
    if(root==NULL)
        return ;
    
    LRD_Traverse_BST_IF(root->LeftChild,visit,judge);
    LRD_Traverse_BST_IF(root->RightChild,visit,judge);

    if(judge(root)==true)
        visit(root->Data);

    return ;
}

//检查节点是否为叶节点，可作为PREDICATE回调函数的参数
bool IF_LEAF(BSNode *node)
{
    if(node->LeftChild==NULL&&node->RightChild==NULL)
        return true;
    else 
        return false;
}

//检查节点是否为所需数据，可作为PREDICATE回调函数的参数
bool IF_DATA(BSTree root,const datatype data)
{
    if(root->Data==data)
        return true;
    else 
        return false;
}

//先序遍历,返回第一个数据为data的节点
bool Get_Node(BSTree root,const datatype data,BSTree* getnode)
{
    //如果节点为空,返回false,对应情况可能是树为空或者遍历节点到尽头了，返回false并不会使函数提前停止
    if(root==NULL) 
        return false;

    //如果数据匹配,将节点赋给指针参数,并返回true
    if(root->Data==data)
    {
        *getnode=root;
        return true;
    }

    //如果节点既不为空,也没有取得想要的节点,则继续递归子节点
    if(Get_Node(root->LeftChild,data,getnode)==true)
        return true;
    if(Get_Node(root->RightChild,data,getnode)==true)
        return true;
}

//先序遍历,返回一个节点的父节点
bool Get_Node_Parent(BSTree root,const datatype data,BSTree *getnode)
{
    //如果节点为空,返回false,对应情况可能是树为空或者遍历节点到尽头了，返回false并不会使函数提前停止
    if(root==NULL||(root->LeftChild==NULL&&root->RightChild==NULL)) 
        return false;

    //如果左子节点数据匹配,将本级节点赋给指针参数,并返回true
    if(root->LeftChild!=NULL&&root->LeftChild->Data==data)
    {
        *getnode=root;
        return true;
        
    }
    
    //如果右子节点数据匹配,将本级节点赋给指针参数,并返回true
    if(root->RightChild!=NULL&&root->RightChild->Data==data)
    {
        *getnode=root;
        return true;
        
    }

    //如果节点既不为空,也没有取得想要的节点,则继续递归子节点
    if(Get_Node_Parent(root->LeftChild,data,getnode)==true)
        return true;
    if(Get_Node_Parent(root->RightChild,data,getnode)==true)
        return true;
}

//先序遍历,返回一个节点的左孩子
bool Get_Node_LChild(BSTree root,const datatype data,BSTree *getnode)
{
    //调用GET_Node函数先找到该节点
    if(Get_Node(root,data,getnode)==true)
    {    
        //如果该节点无左子节点,返回false,否则继续执行
        if((*getnode)->LeftChild==NULL)
            return false;
        
        //将getnode指向其左子节点,返回true
        *getnode=(*getnode)->LeftChild;
        return true;
    }
    
    //如果得不到改节点则返回false
    return false;
}

//先序遍历,返回一个节点的右孩子
bool Get_Node_RChild(BSTree root,const datatype data,BSTree *getnode)
{
    //调用GET_Node函数先找到该节点
    if(Get_Node(root,data,getnode)==true)
    {    
        //如果该节点无左子节点,返回false,否则继续执行
        if((*getnode)->RightChild==NULL)
            return false;
        
        //将getnode指向其右子节点,返回true
        *getnode=(*getnode)->RightChild;

        return true;
    }
    
    //如果得不到改节点则返回false
    return false;
}

//递归返回二叉树高度
int Get_Height(BSTree root)
{
    //如果二叉树为空,返回0
    if(root==NULL)
        return 0;
    
    //如果二叉树左子树比右子树高，返回左子树高度加上本级高度1
    if(Get_Height(root->LeftChild)>=Get_Height(root->RightChild))
        return Get_Height(root->LeftChild)+1;
    //如果二叉树右子树比左子树高，返回右子树高度加上本级高度1
    else
        return Get_Height(root->RightChild)+1;
}

//先序遍历计算节点数,count要提前初始化为0
void Count_Node(BSTree root,int* count)
{
    //如果节点为空，直接返回
    if(root==NULL||root->Data=='.')
        return ;

    //如果不为空,计数加1
    (*count)++;
    //统计左子树节点
    Count_Node(root->LeftChild,count);
    //统计右子树节点
    Count_Node(root->RightChild,count);

    return ;
}
