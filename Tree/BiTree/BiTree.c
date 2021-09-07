#include "BiTree.h"

//初始化一个二叉树，为根节点分配内存空间
void Init_BT(BiTree *root)
{
    *root=(BiTree)malloc(sizeof(BiNode));

    return ;
}

//检查数据是否符合完全二叉树规范,即第i个非根节点数据的双亲结点必须存在,并且确认data长度，data长度不可以为0
bool is_Complt_BT_Data(const datatype *data,int* length)
{   
    while(data[*length]!='\0')
    {   
        if(*length>0)
        {   
            //有数据的节点的父节点不能无数据
            if(data[*length]!='.'&&data[(*length-1)/2]=='.')    
            {    
                printf("数据不符合完全二叉树规范\n");
                return false;
            }
        }

        //统计data长度
        (*length)++;
    }

    //data长度不能小于1
    if(*length<=0)
        return false;

    return true;
}

//使用先序递归排列一个完全二叉树,第i个元素的左孩子为第2i个元素,右孩子为第2i+1个元素
bool Arrange_Complt_BT(BiTree *root,const datatype *data,const int length,int *i)
{
    //如果某节点数据为空,子节点设为NULL
    if(data[*i]=='.')
    {   
        (*root)->Data='.';
        (*root)->LeftChild=NULL;
        (*root)->RightChild=NULL;

        //退回父节点，深度减1,写入二叉树数据成功，返回true
        *i=(*i+1)/2-1;
        return false;
    }
    //如果不为空,写入数据,并判断子节点是否超出数据数组长度
    else
    {     
        (*root)->Data=data[*i];

        //判断左子节点
        *i=2*(*i+1)-1;
        //不超出,则递归进入子节点,深度加1
        if(*i<length)
        {
            (*root)->LeftChild=(BiNode*)malloc(sizeof(BiNode));
            Arrange_Complt_BT(&((*root)->LeftChild),data,length,i);
        }
        //超出,子节点设为NULL,i变回本节点对应数组下标
        else
        {
            (*root)->LeftChild=NULL;
            *i=(*i+1)/2-1;
        }

        //判断右子节点    
        *i=2*(*i+1);
        //不超出,则递归进入子节点,深度加1
        if(*i<length)
        {
            (*root)->RightChild=(BiNode*)malloc(sizeof(BiNode));
            Arrange_Complt_BT(&((*root)->RightChild),data,length,i);
        }
        //超出,子节点设为NULL,i变回本节点对应数组下标
        else
        {
            (*root)->RightChild=NULL;
            *i=(*i+1)/2-1;
        }
        //退回父节点,深度减1,写入二叉树数据成功,返回true
        *i=(*i+1)/2-1;
        return true;
    }
}

//使用先序递归创建一个完全二叉树
bool Creat_Complt_BT(BiTree root,const datatype *data)
{
    int *length,L=0,i=0;
    length=&L;
    
    //检查数据是否符合创建完全二叉树规范
    if(is_Complt_BT_Data(data,length)==false)
        return false;

    //排除长度小于等于0的数组
    if(length<=0)                                           
        return false;
    else
    {    
        printf("数据数组节点个数为%d\n",*length);
        printf("可用于构造二叉树节点个数为\n");
    }

    //创建完全二叉树
    if(Arrange_Complt_BT(&root,data,L,&i)==true)
        return true;
    else
        return false;

}

//使用先序递归创建一个一般二叉树
bool Creat_Common_BT(BiTree root,const datatype* data,int *i)
{
    //如果二叉树数组数据不超界，查看数据
    if(data[*i]!='\0')
    {  
        //如果数据为空,节点设为空，返回false
        if(data[*i]=='.')
        {   
            root->Data='.';
            root->LeftChild=NULL;
            root->RightChild=NULL;

            return false;
        }
        //如果数据不为空，写入数据
        else
        {
            root->Data=data[*i];
            
            //如果下一个数据不为空，分配空间
            (*i)++;
            if(data[*i]!='\0')
            {
                root->LeftChild=(BiNode*)malloc(sizeof(BiNode));
                Creat_Common_BT(root->LeftChild,data,i);
            }
            //如果下一个数据为空，左子树设为NULL
            else
            {
                root->LeftChild=NULL;
                (*i)--;
            }

            (*i)++;
            //如果下一个数据不为空，分配空间
            if(data[*i]!='\0')
            {
                root->RightChild=(BiNode*)malloc(sizeof(BiNode));
                Creat_Common_BT(root->RightChild,data,i);
            }
            //如果下一个数据为空，右子树设为NULL
            else
            {
                root->RightChild=NULL;
                (*i)--;
            }

            return true;
        }
    }
    //如果二叉树数组数据超界，节点设为NULL，返回false
    else
    {   
        (*i)--;
        root=NULL;
        return false;
    }
}   

//清除二叉树的所有节点，不包括根节点，即回到初始化后状态
void Clear_BT(BiTree root)
{
    Destroy_BT(root->LeftChild);
    Destroy_BT(root->RightChild);
    root->Data='.';

    return ;
}

//后序递归删除二叉树
void Destroy_BT(BiTree root)
{
    if(root==NULL)
        return ;
    
    Destroy_BT(root->LeftChild);
    Destroy_BT(root->RightChild);
    free(root);

    return ;
}

//检查树是否为空树
bool is_BT_Empty(BiTree root)
{
    if(root==NULL)
        return true;
    else 
        return false;
}

//检查节点是否为叶节点
bool is_Node_Leaf(BiTree root,const datatype data)
{
    if(IF_LEAF(root)==true)
        return true;

    return false;
}

//添加第一个数据为data的节点的左孩子
bool Add_Node_LChild(BiTree root,const datatype data,const datatype add_data)
{
    BiTree getnode;

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
    getnode->LeftChild=(BiNode*)malloc(sizeof(BiNode));

    //左子节点赋值给指针getnode
    getnode=getnode->LeftChild;

    //为getnode写入数据
    getnode->Data=add_data;
    getnode->LeftChild=NULL;
    getnode->RightChild=NULL;

    return true;
}

//添加第一个数据为data的节点的右孩子
bool Add_Node_RChild(BiTree root,const datatype data,const datatype add_data)
{   
    //声明一个节点指针
    BiTree getnode;
    
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
    getnode->RightChild=(BiNode*)malloc(sizeof(BiNode));

    //右子节点赋值给指针getnode
    getnode=getnode->RightChild;

    //为getnode写入数据
    getnode->Data=add_data;
    getnode->LeftChild=NULL;
    getnode->RightChild=NULL;

    return true;
}

//删除一个节点及其子节点
bool Del_Node(BiTree root,const datatype data)
{
    //声明一个节点指针,一个辅助指针,辅助指针用于断开需删除节点与父节点的联系
    BiTree getnode,aidnode;

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

    //调用Destroy_BT删除以getnode为根的二叉树
    Destroy_BT(getnode);

    return true;
}

//删除一个节点的左孩子及其子节点
bool Del_Node_LChild(BiTree root,const datatype data)
{
    //声明一个节点指针,一个辅助指针,辅助指针用于断开需删除节点与父节点的联系
    BiTree getnode,aidnode;

    //调用Get_Node函数,如果不存在该节点,报错,返回false
    if(Get_Node(root,data,&getnode)==false)
    {
        printf("二叉树无此节点\n");
        return false;
    }

    //要删除的节点断开和父节点的关系
    aidnode=getnode->LeftChild;
    getnode->LeftChild=NULL;

    //调用Destroy_BT删除以getnode左孩子为根的二叉树
    Destroy_BT(aidnode);

    return true;
}

//删除一个节点的右孩子及其子节点
bool Del_Node_RChild(BiTree root,const datatype data)
{
    //声明一个节点指针,一个辅助指针,辅助指针用于断开需删除节点与父节点的联系
    BiTree getnode,aidnode;

    //调用Get_Node函数,如果不存在该节点,报错,返回false
    if(Get_Node(root,data,&getnode)==false)
    {
        printf("二叉树无此节点\n");
        return false;
    }

    //要删除的节点断开和父节点的关系
    aidnode=getnode->RightChild;
    getnode->RightChild=NULL;

    //调用Destroy_BT删除以getnode左孩子为根的二叉树
    Destroy_BT(aidnode);

    return true;
}

//先序遍历二叉树,调用回调函数访问节点数据
void DLR_Traverse_BT(BiTree root,CALLBACK visit)
{
    if(root==NULL||root->Data=='.')
        return ;

    visit(root->Data);
    DLR_Traverse_BT(root->LeftChild,visit);
    DLR_Traverse_BT(root->RightChild,visit);

    return ;
}

//带调用回调函数筛选条件的先序遍历二叉树,调用回调函数访问节点数据
void DLR_Traverse_BT_IF(BiTree root,CALLBACK visit,PREDICATE judge)
{
    if(root==NULL)
        return ;

    if(judge(root)==true)
        visit(root->Data);

    DLR_Traverse_BT_IF(root->LeftChild,visit,judge);
    DLR_Traverse_BT_IF(root->RightChild,visit,judge);

    return ;
}

//利用栈,非递归先序遍历二叉树,调用回调函数访问节点数据
void DLR_Traverse_BT_Stack(BiTree root,CALLBACK visit)
{
    Stack TS;               //声明栈
    BiNode *data=root;      //声明暂存节点
    bool flag;              //声明布尔标志,标注栈是否为空

    //初始化栈
    InitStack(&TS);

    //将根节点压栈
    Push(&TS,data);

    //标志表示栈是否为空
    flag=is_Stack_Empty(&TS);

    //如果栈非空,进入循环
    while(flag!=true)
    {
        //出栈,打印节点数据
        data=Pop(&TS);
        visit(data->Data);

        //如果右子节点非空,对右子节点压栈
        if(data->RightChild!=NULL)
            Push(&TS,data->RightChild);

        //如果左子节点非空,对左子节点压栈
        if(data->LeftChild!=NULL) 
            Push(&TS,data->LeftChild);
        
        //设定栈空标志
        flag=is_Stack_Empty(&TS);
    }
}

//中序遍历二叉树,调用回调函数访问节点数据
void LDR_Traverse_BT(BiTree root,CALLBACK visit)
{
    if(root==NULL||root->Data=='.')
        return ;

    LDR_Traverse_BT(root->LeftChild,visit);
    visit(root->Data);
    LDR_Traverse_BT(root->RightChild,visit);
}

//带调用回调函数筛选条件的中序遍历二叉树,调用回调函数访问节点数据
void LDR_Traverse_BT_IF(BiTree root,CALLBACK visit,PREDICATE judge)
{
    if(root==NULL)
        return ;
    
    LDR_Traverse_BT_IF(root->LeftChild,visit,judge);

    if(judge(root)==true)
        visit(root->Data);

    LDR_Traverse_BT_IF(root->RightChild,visit,judge);

    return ;
}

//利用栈,非递归中序遍历二叉树,调用回调函数访问节点数据          
void LDR_Traverse_BT_Stack(BiTree root,CALLBACK visit)
{
    Stack TS;                   //声明栈
    BiNode* data;               //声明访问节点
    bool flag;                  //声明布尔标志,标注栈是否为空

    //初始化栈
    InitStack(&TS);
    
    //初始化暂存节点为root
    data=root;

    //标志表示栈是否为空
    flag=is_Stack_Empty(&TS);
    
    //如果栈非空或者节点非空,进入循环
    while(flag!=true||data!=NULL)
    {
        //如果节点非空,压栈,并转到左子节点
        if(data!=NULL)
        {
            Push(&TS,data);

            data=data->LeftChild; 
        }
        //若节点为空,出栈,打印节点数据,并判断出栈节点的右子树是否为空
        else
        {
            data=Pop(&TS);
            visit(data->Data);
            
            data=data->RightChild;
        }

        //设定栈空标志
        flag=is_Stack_Empty(&TS);
    }

}

//后序遍历二叉树,调用回调函数访问节点数据
void LRD_Traverse_BT(BiTree root,CALLBACK visit)
{   
    if(root==NULL||root->Data=='.')
        return ;
    
    LRD_Traverse_BT(root->LeftChild,visit);
    LRD_Traverse_BT(root->RightChild,visit);
    visit(root->Data);
}

//带调用回调函数筛选条件的后序遍历二叉树,调用回调函数访问节点数据
void LRD_Traverse_BT_IF(BiTree root,CALLBACK visit,PREDICATE judge)
{
    if(root==NULL)
        return ;
    
    LRD_Traverse_BT_IF(root->LeftChild,visit,judge);
    LRD_Traverse_BT_IF(root->RightChild,visit,judge);

    if(judge(root)==true)
        visit(root->Data);

    return ;
}

//利用栈,非递归后序遍历二叉树,调用回调函数访问节点数据
void LRD_Traverse_BT_Stack(BiTree root,CALLBACK visit)
{
    Stack TS;                                   //声明栈
    BiNode *data,*popnode;                      //声明暂存节点
    bool flag;                                  //声明布尔标志,标注栈是否为空

    //初始化栈
    InitStack(&TS);

    //初始化data为根节点,popnode为NULL
    data=root;
    popnode=NULL;

    //标志表示栈是否为空
    flag=is_Stack_Empty(&TS);

    //如果栈非空,进入循环
    while(flag!=true||data!=NULL)
    {   
        //如果节点非空,压栈,并转到左子节点
        if(data!=NULL)
        {
            Push(&TS,data);

            data=data->LeftChild; 
        }
        //若节点为空,出栈,打印节点数据,并判断出栈节点的右子树是否为空
        else
        {
            data=TS.elem[Get_Stack_Top(&TS)];

            if(data->RightChild==popnode||data->RightChild==NULL)
            {
                visit(data->Data);
                popnode=data;
                Pop(&TS);
                data=NULL;
            }
            else
                data=data->RightChild;
        }
        //设定栈空标志
        flag=is_Stack_Empty(&TS);
    }

}

//检查节点是否为叶节点，可作为PREDICATE回调函数的参数
bool IF_LEAF(BiNode *node)
{
    if(node->LeftChild==NULL&&node->RightChild==NULL)
        return true;
    else 
        return false;
}

//检查节点是否为所需数据，可作为PREDICATE回调函数的参数
bool IF_DATA(BiTree root,const datatype data)
{
    if(root->Data==data)
        return true;
    else 
        return false;
}

//先序遍历,返回第一个数据为data的节点
bool Get_Node(BiTree root,const datatype data,BiTree* getnode)
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
bool Get_Node_Parent(BiTree root,const datatype data,BiTree *getnode)
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
bool Get_Node_LChild(BiTree root,const datatype data,BiTree *getnode)
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
bool Get_Node_RChild(BiTree root,const datatype data,BiTree *getnode)
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
int Get_Height(BiTree root)
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
void Count_Node(BiTree root,int* count)
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

// void Get_BT_from_Traverse(BiTree root)
// {
//     char midorder[100],preorder[100];
    
// }