#include "RBTree.h"
#include <string.h>
#include <math.h>

#define MAX(A, B) (A >= B ? A : B)

const char red[4] = "Red";
const char black[6] = "Black";

// 左旋 node_f为父节点, node_s为子节点
void Rotate_Left(RBTree* root, RBNode* node_f, RBNode* node_s){
    node_f->right = node_s->left;

    if(node_s->left)
        node_s->left->parent = node_f;

    node_s->left = node_f;
    node_s->parent = node_f->parent;

    if(!node_f->parent)
        (*root) = node_s;
    else if(node_f->parent->left == node_f)
        node_f->parent->left = node_s;
    else
        node_f->parent->right = node_s;
    
    node_f->parent = node_s;
}

// 右旋 node_s为子节点, node_f为父节点
void Rotate_Right(RBTree* root, RBNode* node_s, RBNode* node_f){
    node_f->left = node_s->right;

    if(node_s->right)
        node_s->right->parent = node_f;

    node_s->right = node_f;
    node_s->parent = node_f->parent;

    if(!node_f->parent)
        (*root) = node_s;
    else if(node_f->parent->left == node_f)
        node_f->parent->left = node_s;
    else
        node_f->parent->right = node_s;

    node_f->parent = node_s;
}

// 交换两个指针的指向
void Swap(RBNode* node1, RBNode* node2){
    RBNode* node_s = node1;
    node1 = node2;
    node2 = node_s;
}

// 交换两个指针指向的结点在树中的位置
void Swap_Node(RBNode* node1, RBNode* node2){
    if(!node1 || !node2)
        return ;

    RBNode *node1_tmp = node1;
    datatype node1_dtmp = node1->data;

    node1->data = node2->data;
    node2->data = node1_dtmp;

    node1 = node2;
    node2 = node1_tmp;
}

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
        RBNode* fftra = ftra->parent;

        while(fftra && ftra->color == red){
            // 叔辈节点
            RBNode* unc = (fftra->left == ftra)? fftra->right: fftra->left;

            // 检查是否需要改色或旋转
            if(unc && unc->color == red){
                // printf("here\n");

                ftra->color = unc->color = black;

                if(fftra != *root)
                    fftra->color = red;

                tra = ftra->parent;

                if(fftra->parent){
                    ftra = fftra->parent;

                    if(fftra->parent->parent)
                        fftra = fftra->parent->parent;
                    else
                        fftra = NULL;
                }
                else{
                    ftra = NULL;
                    fftra = NULL;
                }    
            }
            else if(ftra == fftra->left && tra == ftra->left && (!unc || (unc && unc->color == black))){
                // printf("here1\n");
                Rotate_Right(root, ftra, fftra);

                ftra->color = black;
                fftra->color = red;

                break;
            }
            else if(ftra == fftra->right && tra == ftra->right && (!unc || (unc && unc->color == black))){
                // printf("here2\n");
                Rotate_Left(root, fftra, ftra);

                ftra->color = black;
                fftra->color = red;

                break;
            }
            else if(ftra == fftra->left && tra == ftra->right && (!unc || (unc && unc->color == black))){
                // printf("here3\n");

                // ftra 和 tra 左旋
                Rotate_Left(root, ftra, tra);

                // ftra 和 tra 交换
                Swap(ftra, tra);

                // fftra 和 tra 右旋
                Rotate_Right(root, tra, fftra);

                // 重置颜色
                tra->color = black;
                ftra->color = red;
                fftra->color = red;

                break;
            }
            else if(ftra == fftra->right && tra == ftra->left && (!unc || (unc && unc->color == black))){
                // printf("here4\n");

                // ftra 和 tra 右旋
                Rotate_Right(root, tra, ftra);

                // ftra 和 tra 交换
                Swap(ftra, tra);

                // fftra 和 tra 左旋
                Rotate_Left(root, fftra, tra);

                // 重置颜色
                tra->color = black;
                ftra->color = red;
                fftra->color = red;

                break;
            }
            else
                printf("不该到的分支\n");
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

// 得到平衡树中节点的前驱节点
bool Get_Prev(const RBNode* const node, RBNode** getnode){
    if(!node){
        printf("要搜索前驱的节点不存在\n");
        *getnode = NULL;
        return false;
    }

    *getnode = node->left;

    if(!(*getnode)){
        printf("要搜索节点的前驱不存在\n");
        *getnode = NULL;
        return false;      
    }

    while((*getnode)->right)
        (*getnode) = (*getnode)->right;

    return true;
}

// 得到平衡树中节点的后继节点
bool Get_Next(const RBNode* const node, RBNode** getnode){
    if(!node){
        printf("要搜索后继的节点不存在\n");
       *getnode = NULL;
       return false;
    }

    *getnode = node->right;

    if(!(*getnode)){
        printf("要搜索节点的后继不存在\n");
        *getnode = NULL;
        return false;    
    }

    while((*getnode)->left)
        (*getnode) = (*getnode)->left;

    return true;
}

// 删除红黑树的一个节点
bool Del_Node(RBTree* root,const datatype data)
{
    // 声明查找结点
    RBNode *tra, *ftra;

    //调用Get_Node函数,如果不存在该节点,报错,返回false
    if(!Get_Node(*root, data, &tra)){
        printf("红黑树无此节点\n");
        return false;
    }

    // 如果删除的是根结点, 且左右子树都为空的话
    if(tra == *root && !tra->left && !tra->right){
        free(tra);
        *root = NULL;
        return true;
    }

    // 如果要删除的结点有左右子节点, 则将要删除的结点和前驱节点调换位置变成叶节点
    RBNode* prev;
    if(tra->left && tra->right){
        Get_Prev(tra, &prev);
        Swap_Node(tra, prev);
        tra = prev;
    }

    ftra = tra->parent;
    // 如果要删除的结点是红叶节点, 则直接删除, 红非叶节点一定有两个孩子, 在上一步被消灭了
    if(tra->color == red){
        
        if(ftra->left == tra)
            ftra->left = NULL;
        else
            ftra->right = NULL;

        tra->parent = NULL;
        free(tra);
        tra = NULL;
    }
    // 如果要删除的节点是黑节点, 则得判读是否有子树
    else{
        // 有子树
        if(tra->left || tra->right){
            RBNode* stra;

            if(tra->left)
                stra = tra->left;
            else
                stra = tra->right;

            // 黑节点的子树是红节点子树, 直接用红节点子树替换要删除的节点并把颜色换成黑色
            tra->left = tra->right = tra->parent = NULL;
            
            if(tra == ftra->left)
                ftra->left = stra;
            else
                ftra->right = stra;

            stra->parent = ftra;
            stra->color = black;
            
            free(tra);
            tra = NULL;
        }
        // 无子树, 删除叶节点, 要根据父节点, 兄弟节点, 侄节点分情况讨论
        else{
            // 声明兄弟节点
            RBNode *btra;

            while(1){
                ftra = tra->parent;

                if(ftra->left == tra)
                    btra = ftra->right;
                else
                    btra = ftra->left;

                // 情况1 如果父节点是黑色, 兄弟节点是红色, 把兄弟结点旋上来并与原父节点对调颜色, 然后变成情况4
                if(ftra->color == black && btra && btra->color == red){
                    printf("情况1\n");
                    ftra->color = red;
                    btra->color = black;

                    if(ftra->right == btra)
                        Rotate_Left(root, ftra, btra);
                    else
                        Rotate_Right(root, btra, ftra);

                    goto case4;
                }

                RBNode *rm_c_tra;   // 声明远侄子节点
                if(btra == ftra->right)
                    rm_c_tra = btra->right;
                else
                    rm_c_tra = btra->left;

                // 情况2, 如果兄弟节点是黑色, 远侄节点是红色
                if(btra->color == black && rm_c_tra && rm_c_tra->color == red){
                    printf("情况2\n");
                    btra->color = ftra->color;
                    ftra->color = black;
                    rm_c_tra->color = black;

                    if(ftra->right == btra)
                        Rotate_Left(root, ftra, btra);
                    else
                        Rotate_Right(root, btra, ftra);

                    tra->left = tra->right = tra->parent = NULL;
                    if(tra == ftra->left)
                        ftra->left = NULL;
                    else
                        ftra->right = NULL;

                    free(tra);
                    tra = NULL;

                    return true;
                }
                // 情况3, 如果兄弟节点是黑色, 远侄节点是黑色或空, 则进一步判断近侄节点
                else if(btra->color == black && ((rm_c_tra && rm_c_tra->color == black) || !rm_c_tra)){
                    printf("情况3\n");

                    RBNode *cl_c_tra;   // 声明近侄子节点
                    if(rm_c_tra == btra->right)
                        cl_c_tra = btra->left;
                    else
                        cl_c_tra = btra->right;

                    // 如果近侄节点是红色, 旋转, 改色后变成情况2, 按照情况2的方式处理
                    if(cl_c_tra && cl_c_tra->color == red){
                        btra->color = red;
                        cl_c_tra->color = black;

                        if(cl_c_tra == btra->left){
                            Rotate_Right(root, cl_c_tra, btra);

                            // // 情况2处理
                            // btra->color = ftra->color;
                            // ftra->color = black;
                            // Rotate_Left(root, ftra, btra);
                            // cl_c_tra->color = black;
                        }
                        else{
                            Rotate_Left(root, btra, cl_c_tra);

                            // // 情况2处理
                            // btra->color = ftra->color;
                            // ftra->color = black;
                            // Rotate_Right(root, btra, ftra);
                            // cl_c_tra->color = black;
                        }
                    }
                    else{
                        printf("woc, 如何处理\n");
                    }
                }

                // 情况4, 如果父节点是红色, 自己和兄弟节点是黑色, 直接删除自己并把父节点改成黑色, 兄弟结点改成红色
                if(ftra->color == red && ((btra && btra->color == black) || !btra)){
case4:
                    printf("情况4\n");
                    if(ftra->left && ftra->left == tra){
                        ftra->left = NULL;
                        btra = ftra->right;                
                    }
                    else{
                        ftra->right = NULL;
                        btra = ftra->left;
                    }

                    tra->left = tra->right = tra->parent = NULL;
                    free(tra);
                    tra = NULL;

                    btra->color = red;
                    ftra->color = black;

                    return true;
                }
                // 情况5, 如果父结点和兄弟结点全是黑色, 则将兄弟结点变红, 然后删除本节点, 同时向上接着调整
                else if(ftra->color == black && (!btra || (btra && btra->color == black))){
                    printf("情况5\n");
                    btra->color = red;

                    if(ftra->left && ftra->left == tra)
                        ftra->left = NULL;
                    else
                        ftra->right = NULL;

                    tra->left = tra->right = tra->parent = NULL;
                    free(tra);
                    tra = ftra;

                    break;       
                }
            }
        }
    }
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
    if(!root) 
        return false;

    //如果数据匹配,将节点赋给指针参数,并返回true
    if(root->data == data)
    {
        *getnode = root;
        return true;
    }

    //如果节点既不为空,也没有取得想要的节点,则继续递归子节点
    return (Get_Node(root->left, data, getnode) || Get_Node(root->right, data, getnode));
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
