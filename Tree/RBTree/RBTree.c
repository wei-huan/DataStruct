#include "RBTree.h"
#include <string.h>
#include <math.h>

#define MAX(A, B) (A >= B ? A : B)

const char red[4] = "Red";
const char black[6] = "Black";

// 向树中添加节点
void Add_Node(RBTree* root, const datatype data){

    RBNode* node = (RBNode*) malloc(sizeof(RBNode));
    node->left = node->right = node->parent = NULL;
    node->color = red;
    node->data = data;

    // 首节点
    if(!(*root)){
        node->color = black;
        *root = node;
    }
    else{
        // 设置遍历树查找合适位置的指针及其父节点
        RBNode *tra = *root, *ftra = NULL;

        // 找到要插入的位置
        while(tra){
            ftra = tra;

            if(tra->data <= data)
                tra = tra->right;
            else
                tra = tra->left;
        }

        // 插入
        tra = node;
        node->parent = ftra;
        if(ftra->data <= data)
            ftra->right = node;
        else
            ftra->left = node;

        // 祖宗节点
        RBNode* fftra;

        // 检查是否需要改色或旋转
        while(ftra && ftra->color == red){
            fftra = ftra->parent;

            if(fftra && fftra->color == black){
                // 叔辈节点
                RBNode* unc = (fftra->left == ftra)? fftra->right: fftra->left;

                // 第一种情况, cur为红, parent为红, pParent为黑, uncle存在且为红
                if(unc && unc->color == red){
                    ftra->color = unc->color = black;

                    if(fftra != *root)
                        fftra->color = red;

                    tra = ftra->parent;

                    if(fftra->parent)
                        ftra = fftra->parent;
                    else
                        ftra = NULL;

                    if(fftra->parent && fftra->parent->parent)
                            fftra = fftra->parent->parent;
                    else
                        fftra = NULL;
                }
                else{
                    // 第二种情况, cur为红, parent为红, pParent为黑, uncle不存在/u为黑, parent为pParent的左孩子, cur为parent的左孩子, 则进行右单旋转
                    // 第三种情况, cur为红, parent为红, pParent为黑, uncle不存在/u为黑, parent为pParent的左孩子, cur为parent的右孩子，则针对p做左单旋转
                    if(!unc){
                        if(ftra == fftra->left && tra == ftra->left){
                            fftra->left = NULL;
                            ftra->right = fftra;

                            ftra->color = black;
                            fftra->color = red;

                            if(fftra == *root)
                                *root = ftra;
                            else if(fftra == fftra->parent->right)
                                fftra->parent->right = ftra;
                            else
                                fftra->parent->left = ftra;

                            ftra->parent = fftra->parent;
                            fftra->parent = ftra;
                        }
                        else if(ftra == fftra->right && tra == ftra->right){
                            fftra->right = NULL;
                            ftra->left = fftra;

                            ftra->color = black;
                            fftra->color = red;

                            if(fftra == *root)
                                *root = ftra;
                            else if(fftra == fftra->parent->right)
                                fftra->parent->right = ftra;
                            else
                                fftra->parent->left = ftra;

                            ftra->parent = fftra->parent;
                            fftra->parent = ftra;
                        }
                        else if(ftra == fftra->left && tra == ftra->right){
                            ftra->right = NULL;
                            tra->left = ftra;
                            fftra->left = NULL;
                            tra->right = fftra;

                            ftra->parent = tra;
                            ftra = tra;

                            if(fftra == *root)
                                *root = ftra;
                            else if(fftra == fftra->parent->right)
                                fftra->parent->right = ftra;
                            else
                                fftra->parent->left = ftra;

                            
                            tra->parent = fftra->parent;
                            fftra->parent = tra;

                            tra->color = black;
                            fftra->color = red;
                        }
                        else{
                            ftra->left = NULL;
                            tra->right = ftra;
                            fftra->right = NULL;
                            tra->left = fftra;

                            ftra->parent = tra;
                            ftra = tra;

                            if(fftra == *root)
                                *root = ftra;
                            else if(fftra == fftra->parent->right)
                                fftra->parent->right = ftra;
                            else
                                fftra->parent->left = ftra;

                            tra->parent = fftra->parent;
                            fftra->parent = tra;

                            tra->color = black;
                            fftra->color = red;
                        }
                    }
                    else if(unc && unc->color == black){
                        if(ftra == fftra->left && tra == ftra->left){

                            ftra->color = black;
                            fftra->color = red;
                            unc->color = black;

                            if(fftra == *root){
                                *root = ftra;
                                ftra->parent = NULL;
                            }
                            else if(fftra == fftra->parent->right){
                                fftra->parent->right = ftra;
                                ftra->parent = fftra->parent;
                            }
                            else{
                                fftra->parent->left = ftra;
                                ftra->parent = fftra->parent;
                            }

                            if(ftra->right)
                                ftra->right->parent = fftra;

                            fftra->left = ftra->right;
                            ftra->right = fftra;
                            fftra->parent = ftra;                            
                        }
                        else if(ftra == fftra->right && tra == ftra->right){

                            ftra->color = black;
                            fftra->color = red;
                            unc->color = black;

                            if(fftra == *root){
                                *root = ftra;
                                ftra->parent = NULL;
                            }
                            else if(fftra == fftra->parent->right){
                                fftra->parent->right = ftra;
                                ftra->parent = fftra->parent;
                            }
                            else{
                                fftra->parent->left = ftra;
                                ftra->parent = fftra->parent;
                            }

                            if(ftra->left)
                                ftra->left->parent = fftra;

                            fftra->right = ftra->left;
                            ftra->left = fftra;
                            fftra->parent = ftra;
                        }
                        else if(ftra == fftra->left && tra == ftra->right){
                            ftra->right = tra->left;
                            if(tra->left)
                                tra->left->parent = ftra;
                            tra->left = ftra;

                            fftra->left = tra->right;
                            if(tra->right)
                                tra->right->parent = fftra;
                            tra->right = fftra;

                            tra->color = black;
                            fftra->color = red;

                            ftra->parent = tra;
                            ftra = tra;

                            if(fftra == *root){
                                *root = ftra;
                                ftra->parent = NULL;
                            }
                            else if(fftra == fftra->parent->right){
                                fftra->parent->right = ftra;
                                ftra->parent = fftra->parent;
                            }
                            else{
                                fftra->parent->left = ftra;
                                ftra->parent = fftra->parent;
                            }

                            fftra->parent = tra;
                        }
                        else{
                            ftra->left = tra->right;
                            if(tra->right)
                                tra->right->parent = ftra;
                            tra->right = ftra;
                            
                            fftra->right = tra->left;
                            if(tra->left)
                                tra->left->parent = fftra;
                            tra->left = fftra;

                            tra->color = black;
                            fftra->color = red; 

                            ftra->parent = tra;
                            ftra = tra;

                            if(fftra == *root){
                                *root = ftra;
                                ftra->parent = NULL;
                            }
                            else if(fftra == fftra->parent->right){
                                fftra->parent->right = ftra;
                                ftra->parent = fftra->parent;
                            }
                            else{
                                fftra->parent->left = ftra;
                                ftra->parent = fftra->parent;
                            }

                            fftra->parent = tra;
                        }
                    }
                    else
                        printf("有错, 叔辈节点的颜色不正确\n");
                }
            }
        }
    }
}

// 创建红黑树
void Creat_RBT(RBTree* root){
    char str[100];
    int node_val;

    printf("创建红黑树, 请输入节点的值(整形), 输入q完成创建\n");

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

// 后序递归删除红黑树
void Destroy_RBT(RBTree root)
{
    if(root==NULL)
        return ;
    
    Destroy_RBT(root->left);
    Destroy_RBT(root->right);
    free(root);

    return ;
}

//检查树是否为空树
bool is_RBT_Empty(RBTree root)
{
    if(root==NULL)
        return true;
    else 
        return false;
}

//检查节点是否为叶节点
bool is_Node_Leaf(RBTree root,const datatype data)
{
    if(IF_LEAF(root)==true)
        return true;

    return false;
}

// 删除一个节点及其子节点
bool Del_Node(RBTree root,const datatype data)
{
    //声明一个节点指针,一个辅助指针,辅助指针用于断开需删除节点与父节点的联系
    RBTree getnode,aidnode;

    //调用Get_Node函数,如果不存在该节点,报错,返回false
    if(Get_Node(root,data,&getnode)==false)
    {
        printf("红黑树无此节点\n");
        return false;
    }
    
    //要删除的节点断开和父节点的关系
    if(aidnode->left==getnode)
        aidnode->left=NULL;
    else
        aidnode->right=NULL;

    //调用Destroy_RBT删除以getnode为根的红黑树
    Destroy_RBT(getnode);

    return true;
}

int nest = 0;
//先序遍历红黑树,调用回调函数访问节点数据
void DLR_Traverse_RBT(RBTree root,CALLBACK visit)
{
    if(root == NULL)
        return ;

    nest++;

    visit(*root);
    DLR_Traverse_RBT(root->left, visit);
    DLR_Traverse_RBT(root->right, visit);

    nest--;
    return ;
}

//带调用回调函数筛选条件的先序遍历红黑树,调用回调函数访问节点数据
void DLR_Traverse_RBT_IF(RBTree root,CALLBACK visit,PREDICATE judge)
{
    if(root==NULL)
        return ;

    if(judge(root)==true)
        visit(*root);

    DLR_Traverse_RBT_IF(root->left,visit,judge);
    DLR_Traverse_RBT_IF(root->right,visit,judge);

    return ;
}

//中序遍历红黑树,调用回调函数访问节点数据
void LDR_Traverse_RBT(RBTree root,CALLBACK visit)
{
    if(root==NULL)
        return ;

    LDR_Traverse_RBT(root->left,visit);
    visit(*root);
    LDR_Traverse_RBT(root->right,visit);
}

//带调用回调函数筛选条件的中序遍历红黑树,调用回调函数访问节点数据
void LDR_Traverse_RBT_IF(RBTree root,CALLBACK visit,PREDICATE judge)
{
    if(root==NULL)
        return ;
    
    LDR_Traverse_RBT_IF(root->left,visit,judge);

    if(judge(root)==true)
        visit(*root);

    LDR_Traverse_RBT_IF(root->right,visit,judge);

    return ;
}

//后序遍历红黑树,调用回调函数访问节点数据
void LRD_Traverse_RBT(RBTree root,CALLBACK visit)
{   
    if(root==NULL)
        return ;
    
    LRD_Traverse_RBT(root->left,visit);
    LRD_Traverse_RBT(root->right,visit);
    visit(*root);
}

//带调用回调函数筛选条件的后序遍历红黑树,调用回调函数访问节点数据
void LRD_Traverse_RBT_IF(RBTree root,CALLBACK visit,PREDICATE judge)
{
    if(root==NULL)
        return ;
    
    LRD_Traverse_RBT_IF(root->left,visit,judge);
    LRD_Traverse_RBT_IF(root->right,visit,judge);

    if(judge(root)==true)
        visit(*root);

    return ;
}

//检查节点是否为叶节点，可作为PREDICATE回调函数的参数
bool IF_LEAF(RBNode *node)
{
    if(node->left==NULL&&node->right==NULL)
        return true;
    else 
        return false;
}

//检查节点是否为所需数据，可作为PREDICATE回调函数的参数
bool IF_DATA(RBTree root,const datatype data)
{
    if(root->data==data)
        return true;
    else 
        return false;
}

//先序遍历,返回第一个数据为data的节点
bool Get_Node(RBTree root,const datatype data,RBTree* getnode)
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
bool Get_Node_Parent(RBTree root,const datatype data,RBTree *getnode)
{
    //如果节点为空,返回false,对应情况可能是树为空或者遍历节点到尽头了，返回false并不会使函数提前停止
    if(root==NULL||(root->left==NULL&&root->right==NULL)) 
        return false;

    return true;
}

//先序遍历,返回一个节点的左孩子
bool Get_Node_LChild(RBTree root,const datatype data,RBTree *getnode)
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
bool Get_Node_RChild(RBTree root,const datatype data,RBTree *getnode)
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

//递归返回红黑树高度
int Get_Height(RBTree root)
{
    //如果红黑树为空,返回0
    if(root==NULL)
        return 0;
    
    //如果红黑树左子树比右子树高，返回左子树高度加上本级高度1
    if(Get_Height(root->left)>=Get_Height(root->right))
        return Get_Height(root->left)+1;
    //如果红黑树右子树比左子树高，返回右子树高度加上本级高度1
    else
        return Get_Height(root->right)+1;
}

//先序遍历计算节点数,count要提前初始化为0
void Count_Node(RBTree root,int* count)
{
    //如果节点为空，直接返回
    if(root==NULL)
        return ;

    //如果不为空,计数加1
    (*count)++;
    //统计左子树节点
    Count_Node(root->left,count);
    //统计右子树节点
    Count_Node(root->right,count);

    return ;
}