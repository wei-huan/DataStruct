#include "BSTree.h"
#include <string.h>

// 向树中添加一个节点
// void Add_Node(BSTree* root, const datatype data){
//     BSTree node;

//     if(!(*root)){
//         node = (BSNode*)malloc(sizeof(BSNode));
//         node->data = data;
//         node->left = node->right = NULL;
//         *root = node;
//     }
//     else if((*root)->data < data)
//         Add_Node(&((*root)->right), data);
//     else
//         Add_Node(&((*root)->left), data);
// }

// 向树中添加节点, 非递归
void Add_Node(BSTree* root, const datatype data){
    BSTree rt = *root;

    // 首节点
    if(!rt){
        rt = (BSNode*) malloc(sizeof(BSNode));
        rt->left = NULL;
        rt->right  =NULL;
        rt->data = data;
        *root = rt;
    }
    else{
        while(1){            
            if(rt->data <= data){
                
                if(rt->right)
                    rt = rt->right;
                else{
                    rt->right = (BSNode*) malloc(sizeof(BSNode));
                    rt->right->left = NULL;
                    rt->right->right  =NULL;
                    rt->right->data = data;
                    break;
                }
            }
            else{

                if(rt->left)
                    rt = rt->left;
                else{
                    rt->left = (BSNode*) malloc(sizeof(BSNode));
                    rt->left->left = NULL;
                    rt->left->right  =NULL;
                    rt->left->data = data;
                    break;
                }
            }
        }
    }
}

// 创建二叉排序树
void Creat_BST(BSTree* root){
    char str[100];
    int node_val;

    printf("创建二叉排序树, 请输入节点的值(整形), 输入q完成创建\n");

    while(1){
        printf("请输入节点的值或q结束: ");
        scanf("%s", str);

        if(!strcmp(str, "quit") || !strcmp(str, "q"))
            break;

        node_val = atoi(str);
        Add_Node(root, node_val);
    }

    printf("创建完成\n");
}

//后序递归删除二叉树
void Destroy_BST(BSTree root)
{
    if(root==NULL)
        return ;
    
    Destroy_BST(root->left);
    Destroy_BST(root->right);
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

//删除一个节点
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
    if(aidnode->left==getnode)
        aidnode->left=NULL;
    else
        aidnode->right=NULL;

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
    aidnode=getnode->left;
    getnode->left=NULL;

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
    aidnode=getnode->right;
    getnode->right=NULL;

    //调用Destroy_BST删除以getnode左孩子为根的二叉树
    Destroy_BST(aidnode);

    return true;
}

int nest = 0;
//先序遍历二叉树,调用回调函数访问节点数据
void DLR_Traverse_BST(BSTree root,CALLBACK visit)
{
    if(root == NULL)
        return ;

    nest++;
    visit(root->data);
    DLR_Traverse_BST(root->left, visit);
    DLR_Traverse_BST(root->right, visit);

    nest--;
    return ;
}

//带调用回调函数筛选条件的先序遍历二叉树,调用回调函数访问节点数据
void DLR_Traverse_BST_IF(BSTree root,CALLBACK visit,PREDICATE judge)
{
    if(root==NULL)
        return ;

    if(judge(root)==true)
        visit(root->data);

    DLR_Traverse_BST_IF(root->left,visit,judge);
    DLR_Traverse_BST_IF(root->right,visit,judge);

    return ;
}

//中序遍历二叉树,调用回调函数访问节点数据
void LDR_Traverse_BST(BSTree root,CALLBACK visit)
{
    if(root==NULL||root->data=='.')
        return ;

    LDR_Traverse_BST(root->left,visit);
    visit(root->data);
    LDR_Traverse_BST(root->right,visit);
}

//带调用回调函数筛选条件的中序遍历二叉树,调用回调函数访问节点数据
void LDR_Traverse_BST_IF(BSTree root,CALLBACK visit,PREDICATE judge)
{
    if(root==NULL)
        return ;
    
    LDR_Traverse_BST_IF(root->left,visit,judge);

    if(judge(root)==true)
        visit(root->data);

    LDR_Traverse_BST_IF(root->right,visit,judge);

    return ;
}

//后序遍历二叉树,调用回调函数访问节点数据
void LRD_Traverse_BST(BSTree root,CALLBACK visit)
{   
    if(root==NULL||root->data=='.')
        return ;
    
    LRD_Traverse_BST(root->left,visit);
    LRD_Traverse_BST(root->right,visit);
    visit(root->data);
}

//带调用回调函数筛选条件的后序遍历二叉树,调用回调函数访问节点数据
void LRD_Traverse_BST_IF(BSTree root,CALLBACK visit,PREDICATE judge)
{
    if(root==NULL)
        return ;
    
    LRD_Traverse_BST_IF(root->left,visit,judge);
    LRD_Traverse_BST_IF(root->right,visit,judge);

    if(judge(root)==true)
        visit(root->data);

    return ;
}

//检查节点是否为叶节点，可作为PREDICATE回调函数的参数
bool IF_LEAF(BSNode *node)
{
    if(node->left==NULL&&node->right==NULL)
        return true;
    else 
        return false;
}

//检查节点是否为所需数据，可作为PREDICATE回调函数的参数
bool IF_DATA(BSTree root,const datatype data)
{
    if(root->data==data)
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
    if(root->data==data)
    {
        *getnode=root;
        return true;
    }

    //如果节点既不为空,也没有取得想要的节点,则继续递归子节点
    if(Get_Node(root->left,data,getnode)==true)
        return true;
    if(Get_Node(root->right,data,getnode)==true)
        return true;
}

//先序遍历,返回一个节点的父节点
bool Get_Node_Parent(BSTree root,const datatype data,BSTree *getnode)
{
    //如果节点为空,返回false,对应情况可能是树为空或者遍历节点到尽头了，返回false并不会使函数提前停止
    if(root==NULL||(root->left==NULL&&root->right==NULL)) 
        return false;

    //如果左子节点数据匹配,将本级节点赋给指针参数,并返回true
    if(root->left!=NULL&&root->left->data==data)
    {
        *getnode=root;
        return true;
        
    }
    
    //如果右子节点数据匹配,将本级节点赋给指针参数,并返回true
    if(root->right!=NULL&&root->right->data==data)
    {
        *getnode=root;
        return true;
        
    }

    //如果节点既不为空,也没有取得想要的节点,则继续递归子节点
    if(Get_Node_Parent(root->left,data,getnode)==true)
        return true;
    if(Get_Node_Parent(root->right,data,getnode)==true)
        return true;
}

//先序遍历,返回一个节点的左孩子
bool Get_Node_LChild(BSTree root,const datatype data,BSTree *getnode)
{
    //调用GET_Node函数先找到该节点
    if(Get_Node(root,data,getnode)==true)
    {    
        //如果该节点无左子节点,返回false,否则继续执行
        if((*getnode)->left==NULL)
            return false;
        
        //将getnode指向其左子节点,返回true
        *getnode=(*getnode)->left;
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
        if((*getnode)->right==NULL)
            return false;
        
        //将getnode指向其右子节点,返回true
        *getnode=(*getnode)->right;

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
    if(Get_Height(root->left)>=Get_Height(root->right))
        return Get_Height(root->left)+1;
    //如果二叉树右子树比左子树高，返回右子树高度加上本级高度1
    else
        return Get_Height(root->right)+1;
}

//先序遍历计算节点数,count要提前初始化为0
void Count_Node(BSTree root,int* count)
{
    //如果节点为空，直接返回
    if(root==NULL||root->data=='.')
        return ;

    //如果不为空,计数加1
    (*count)++;
    //统计左子树节点
    Count_Node(root->left,count);
    //统计右子树节点
    Count_Node(root->right,count);

    return ;
}
