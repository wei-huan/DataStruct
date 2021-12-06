#include "AVLTree.h"
#include <string.h>
#include <math.h>

#define MAX(A, B) (A >= B ? A : B)

// 向树中添加节点
void Add_Node(AVLTree* root, const datatype data){

    AVLNode* node = (AVLNode*) malloc(sizeof(AVLNode));
    node->left = NULL; node->right = NULL;
    node->height = 1;
    node->bf = 0;
    node->data = data;

    // 首节点
    if(!(*root))
        *root = node;
    else{

        AVLNode *tra = *root, *ftra = NULL;
        // 指向离插入位置最近的不平衡位置(bf = -1 / 1)的指针和其父指针
        AVLNode *A = *root, *FA = NULL;

        while(tra){
            if(tra->bf != 0){
                A = tra;
                FA = ftra;
            }

            ftra = tra;
            if(tra->data <= data)
                    tra = tra->right;
            else
                    tra = tra->left;
        }

        // 插入子节点
        if(ftra->data <= data)
            ftra->right = node;
        else
            ftra->left = node;

        // 确定节点B, 修改A的平衡因子和高度
        AVLNode* B;
        if(data >= A->data){
            B = A->right;
            A->bf = A->bf - 1;
        }
        else{
            B = A->left;
            A->bf = A->bf + 1;
        }

        if(!A->left && !A->right)
            A->height = 1;
        else if(!A->left && A->right)
            A->height = A->right->height + 1;
        else if(A->left && !A->right)
            A->height = A->left->height + 1;
        else
            A->height = MAX(A->left->height, A->right->height) + 1;

        // 修改B到插入位置的各个节点的平衡因子
        tra = B; 
        while(tra != node){
            tra->height = tra->height + 1;

            if(data >= tra->data){
                tra->bf = -1;
                tra = tra->right;
            }
            else{
                tra->bf = 1;
                tra = tra->left;
            }
        }

        /* LL */
        if(A->bf == 2 && A->left->bf == 1){
            A->left = B->right;
            B->right = A;
            
            // 更新新的右子树A的高度和平衡因子
            A->bf = 0;
            if(!A->left && !A->right)
                A->height = 1;
            else if(!A->left && A->right)
                A->height = A->right->height + 1;
            else if(A->left && !A->right)
                A->height = A->left->height + 1;
            else
                A->height = MAX(A->left->height, A->right->height) + 1;

            // 更新新的子树父节点B的高度和平衡因子
            B->bf = 0;
            B->height = MAX(B->left->height, B->right->height) + 1;

            if(FA == NULL)
                (*root) = B;
            else if(FA->left == A)
                FA->left = B;
            else
                FA->right = B;

            printf("LL, new root: %d\n", (*root)->data);
        }
        /* RR */
        else if(A->bf == -2 && A->right->bf == -1){
            A->right = B->left;
            B->left = A;
            
            // 更新新的左子树A的高度和平衡因子
            A->bf = 0;
            if(!A->left && !A->right)
                A->height = 1;
            else if(!A->left && A->right)
                A->height = A->right->height + 1;
            else if(A->left && !A->right)
                A->height = A->left->height + 1;
            else
                A->height = MAX(A->left->height, A->right->height) + 1;

            // 更新新的子树父节点B的高度和平衡因子
            B->bf = 0;
            B->height = MAX(B->left->height, B->right->height) + 1;

            if(FA == NULL)
                (*root) = B;
            else if(FA->left == A)
                FA->left = B;
            else
                FA->right = B;

            printf("RR, new root: %d\n", (*root)->data);
        }
        /* LR */
        else if(A->bf == 2 && A->left->bf == -1){
            AVLNode* C = B->right;

            B->right = C->left;
            C->left = B;
            A->left = C->right;
            C->right = A;

            if(data > C->data){
                A->bf = 0;
                B->bf = 1;
                C->bf = 0;
            }
            else if(data < C->data){
                A->bf = -1;
                B->bf = 0;
                C->bf = 0;
            }
            else{
                A->bf = 0;
                B->bf = 0;
            }

            B->height = B->height - 1;
            A->height = MAX(A->height - 2, 1);
            C->height = C->height + 1;

            if(FA == NULL)
                (*root) = C;
            else if(FA->left == A)
                FA->left = C;
            else
                FA->right = C;

            printf("LR, new root: %d\n", (*root)->data);
        }
        /* RL */
        else if(A->bf == -2 && A->right->bf == 1){
            AVLNode* C = B->left;

            B->left = C->right;
            C->right = B;
            A->right = C->left;
            C->left = A;

            if(data > C->data){
                A->bf = 1;
                B->bf = 0;
                C->bf = 0;
            }
            else if(data < C->data){
                A->bf = 0;
                B->bf = -1;
                C->bf = 0;
            }
            else{
                A->bf = 0;
                B->bf = 0;
            }

            B->height = B->height - 1;
            A->height =  MAX(A->height - 2, 1);
            C->height = C->height + 1;

            if(FA == NULL)
                (*root) = C;
            else if(FA->left == A)
                FA->left = C;
            else
                FA->right = C;

            printf("RL, new root: %d\n", (*root)->data);
        }
        /* Balance */
        else{
//            printf("balance\n");
        }
    }
}

// 创建平衡二叉查找树
void Creat_AVLT(AVLTree* root){
    char str[100];
    int node_val;

    printf("创建平衡二叉查找树, 请输入节点的值(整形), 输入q完成创建\n");

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

// 后序递归删除二叉树
void Destroy_AVLT(AVLTree root)
{
    if(root==NULL)
        return ;
    
    Destroy_AVLT(root->left);
    Destroy_AVLT(root->right);
    free(root);

    return ;
}

//检查树是否为空树
bool is_AVLT_Empty(AVLTree root)
{
    if(root==NULL)
        return true;
    else 
        return false;
}

//检查节点是否为叶节点
bool is_Node_Leaf(AVLTree root,const datatype data)
{
    if(IF_LEAF(root)==true)
        return true;

    return false;
}

// 删除一个节点及其子节点
bool Del_Node(AVLTree root,const datatype data)
{
    //声明一个节点指针,一个辅助指针,辅助指针用于断开需删除节点与父节点的联系
    AVLTree getnode,aidnode;

    //调用Get_Node函数,如果不存在该节点,报错,返回false
    if(Get_Node(root,data,&getnode)==false)
    {
        printf("二叉树无此节点\n");
        return false;
    }

    //调用Get_Node_Parent函数,如果不存在,报错,返回false
    if(Get_Node_Parent(root, data, &aidnode)==false)
    {
        printf("二叉树无此父节点\n");
        return false;
    }
    
    //要删除的节点断开和父节点的关系
    if(aidnode->left==getnode)
        aidnode->left=NULL;
    else
        aidnode->right=NULL;

    //调用Destroy_AVLT删除以getnode为根的二叉树
    Destroy_AVLT(getnode);

    return true;
}

int nest = 0;
//先序遍历二叉树,调用回调函数访问节点数据
void DLR_Traverse_AVLT(AVLTree root,CALLBACK visit)
{
    if(root == NULL)
        return ;

    nest++;
    visit(*root);
    DLR_Traverse_AVLT(root->left, visit);
    DLR_Traverse_AVLT(root->right, visit);

    nest--;
    return ;
}

//带调用回调函数筛选条件的先序遍历二叉树,调用回调函数访问节点数据
void DLR_Traverse_AVLT_IF(AVLTree root,CALLBACK visit,PREDICATE judge)
{
    if(root==NULL)
        return ;

    if(judge(root)==true)
        visit(*root);

    DLR_Traverse_AVLT_IF(root->left,visit,judge);
    DLR_Traverse_AVLT_IF(root->right,visit,judge);

    return ;
}

//中序遍历二叉树,调用回调函数访问节点数据
void LDR_Traverse_AVLT(AVLTree root,CALLBACK visit)
{
    if(root==NULL||root->data=='.')
        return ;

    LDR_Traverse_AVLT(root->left,visit);
    visit(*root);
    LDR_Traverse_AVLT(root->right,visit);
}

//带调用回调函数筛选条件的中序遍历二叉树,调用回调函数访问节点数据
void LDR_Traverse_AVLT_IF(AVLTree root,CALLBACK visit,PREDICATE judge)
{
    if(root==NULL)
        return ;
    
    LDR_Traverse_AVLT_IF(root->left,visit,judge);

    if(judge(root)==true)
        visit(*root);

    LDR_Traverse_AVLT_IF(root->right,visit,judge);

    return ;
}

//后序遍历二叉树,调用回调函数访问节点数据
void LRD_Traverse_AVLT(AVLTree root,CALLBACK visit)
{   
    if(root==NULL||root->data=='.')
        return ;
    
    LRD_Traverse_AVLT(root->left,visit);
    LRD_Traverse_AVLT(root->right,visit);
    visit(*root);
}

//带调用回调函数筛选条件的后序遍历二叉树,调用回调函数访问节点数据
void LRD_Traverse_AVLT_IF(AVLTree root,CALLBACK visit,PREDICATE judge)
{
    if(root==NULL)
        return ;
    
    LRD_Traverse_AVLT_IF(root->left,visit,judge);
    LRD_Traverse_AVLT_IF(root->right,visit,judge);

    if(judge(root)==true)
        visit(*root);

    return ;
}

//检查节点是否为叶节点，可作为PREDICATE回调函数的参数
bool IF_LEAF(AVLNode *node)
{
    if(node->left==NULL&&node->right==NULL)
        return true;
    else 
        return false;
}

//检查节点是否为所需数据，可作为PREDICATE回调函数的参数
bool IF_DATA(AVLTree root,const datatype data)
{
    if(root->data==data)
        return true;
    else 
        return false;
}

//先序遍历,返回第一个数据为data的节点
bool Get_Node(AVLTree root,const datatype data,AVLTree* getnode)
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
bool Get_Node_Parent(AVLTree root,const datatype data,AVLTree *getnode)
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
bool Get_Node_LChild(AVLTree root,const datatype data,AVLTree *getnode)
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
bool Get_Node_RChild(AVLTree root,const datatype data,AVLTree *getnode)
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
int Get_Height(AVLTree root)
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
void Count_Node(AVLTree root,int* count)
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
