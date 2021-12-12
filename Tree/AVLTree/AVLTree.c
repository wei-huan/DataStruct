#include "AVLTree.h"
#include <string.h>
#include <math.h>

#define MAX(A, B) (A >= B ? A : B)

// 左旋 node_f为父节点, node_s为子节点
void Rotate_Left(AVLTree* root, AVLNode* node_f, AVLNode* node_s){
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
void Rotate_Right(AVLTree* root, AVLNode* node_s, AVLNode* node_f){
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

// 交换两个节点在树中的位置, 实际就是对调两个节点的值
void Swap(AVLNode* node1, AVLNode* node2){
    datatype swap = node1->data;
    node1->data = node2->data;
    node2->data = swap;
}

// 更新节点的高度, 前提是子树的高度都是正确的
void Update_Node_Height(AVLNode* node){
    if(!node->left && !node->right)
        node->height = 1;
    else if(!node->left && node->right)
        node->height = node->right->height + 1;
    else if(node->left && !node->right)
        node->height = node->left->height + 1;
    else
        node->height = MAX(node->left->height, node->right->height) + 1;
}

// 更新节点的平衡因子, 前提是子树的高度都是正确的
void Update_Node_BF(AVLNode* node){
    if(!node->left && !node->right)
        node->bf = 0;
    else if(!node->left && node->right)
        node->bf = 0 - node->right->height;
    else if(node->left && !node->right)
        node->bf = node->left->height;
    else
        node->bf = node->left->height - node->right->height;
}

// 向树中添加节点
void Add_Node(AVLTree* root, const datatype data){

    AVLNode* node = (AVLNode*) malloc(sizeof(AVLNode));
    node->left = NULL; node->right = NULL; node->parent = NULL;
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
        if(ftra->data <= data){
            ftra->right = node;
            node->parent = ftra;
        }
        else{
            ftra->left = node;
            node->parent = ftra;
        }

        // 确定节点B, 修改A的平衡因子
        AVLNode* B;
        if(data >= A->data){
            B = A->right;
            A->bf = A->bf - 1;
        }
        else{
            B = A->left;
            A->bf = A->bf + 1;
        }

        // 修改B到插入位置的各个节点的平衡因子
        tra = B; 
        while(tra != node){
            // tra->height = tra->height + 1;

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

            // 更新Bl的高度
            while(ftra != B){
                Update_Node_Height(ftra);
                ftra = ftra->parent;
            }

            // 右旋
            Rotate_Right(root, B, A);

            // 更新新的右子树A的高度和平衡因子
            A->bf = 0;
            Update_Node_Height(A);

            // 更新新的子树父节点B的高度和平衡因子
            B->bf = 0;
            Update_Node_Height(B);
        }
        /* RR */
        else if(A->bf == -2 && A->right->bf == -1){
            // 更新Br的高度
            while(ftra != B){
                Update_Node_Height(ftra);
                ftra = ftra->parent;
            }

            // 左旋
            Rotate_Left(root, A, B);
            
            // 更新新的左子树A的高度和平衡因子
            A->bf = 0;
            Update_Node_Height(A);

            // 更新新的子树父节点B的高度和平衡因子
            B->bf = 0;
            Update_Node_Height(B);
        }
        /* LR */
        else if(A->bf == 2 && A->left->bf == -1){
            AVLNode* C = B->right;

            // 更新C的子树高度
            while(ftra && ftra != C && ftra != B){
                Update_Node_Height(ftra);
                ftra = ftra->parent;
            }

            // 左旋
            Rotate_Left(root, B, C);

            // 右旋
            Rotate_Right(root, C, A);

            // 更新A B C高度和平衡因子
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

            Update_Node_Height(B);
            A->height = MAX(A->height - 1, 1);
            C->height = MAX(A->height, B->height) + 1;
        }
        /* RL */
        else if(A->bf == -2 && A->right->bf == 1){
            AVLNode* C = B->left;

            // 更新C的子树高度
            while(ftra && ftra != C && ftra != B){
                Update_Node_Height(ftra);
                ftra = ftra->parent;
            }

            // 右旋
            Rotate_Right(root, C, B);

            // 左旋
            Rotate_Left(root, A, C);

            // 更新A B C高度和平衡因子
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

            Update_Node_Height(B);
            A->height = MAX(A->height - 1, 1);
            C->height = MAX(A->height, B->height) + 1;
        }
        /* Balance */
        else{
            // 更新从插入位置到根节点的高度
            while (ftra){
                Update_Node_Height(ftra);
                ftra = ftra->parent;
            }
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
    if(!root)
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

// //宏定义换行
// #define EOL putchar('\n')

// //回调函数CALLBACK参数函数,打印节点数据
// extern int nest;
// void print(AVLNode node)
// {
//     for(int i = nest; i > 1; i--)
//         printf("  ");

//     if(node.parent)
//         printf("%d: h: %d bf: %d par: %d\n", node.data, node.height, node.bf, node.parent->data);
//     else
//         printf("%d: h: %d bf: %d\n", node.data, node.height, node.bf);
// }

// 释放一个节点的内存
void Destroy_Node(AVLNode* node){
    if(!node)
        return;

    node->left = node->right = node->parent = NULL;
    free(node);
}

// 删除一个节点及其子节点
// 仍然有bug
bool Del_Node(AVLTree* root,const datatype data){
    // // 遍历二叉树
    // DLR_Traverse_AVLT(*root, print);
    // EOL;

    AVLNode *tra = *root, *ftra = NULL;
    // 指向删除节点的左右子节点
    AVLNode *tra_l = NULL;
    AVLNode* tra_r = NULL;

    while(tra && tra->data != data){
        ftra = tra;
        if(tra->data <= data)
                tra = tra->right;
        else
                tra = tra->left;
    }
    
    // 找不到该节点
    if(!tra){
        printf("平衡树中无此节点\n");
        return false;
    }

    // 根据要删除节点的子树情况处理

    // 如果左右子树都存在, 找到节点的前驱节点(后继也可以), 交换位置, 并根据交换后要删除的节点是否有左子树调整
    if(tra->left && tra->right){
        // tra的前驱节点
        AVLNode* prev;
        Get_Prev(tra, &prev);

        // 交换两个节点的位置, 把要删除的节点替换到前驱的位置上
        Swap(tra, prev);
        tra = prev;
        ftra = prev->parent;
        prev = NULL;
        
        if(tra->left){
            if(ftra->left == tra)
                ftra->left = tra->left;
            else
                ftra->right = tra->left;

            tra->left->parent = ftra;
        }
        else{
            if(ftra->left == tra)
                ftra->left = NULL;
            else
                ftra->right = NULL;
        }

        if(tra->parent)
            printf("%d: h: %d bf: %d par: %d\n", tra->data, tra->height, tra->bf, tra->parent->data);
        else
            printf("%d: h: %d bf: %d\n", tra->data, tra->height, tra->bf);
    }
    // 如果仅左子树存在, 直接把左子树接到父节点上, 并向上调整
    else if(tra->left && !tra->right){
        // 如果父节点存在, 直接删除
        if(ftra){
            if(ftra->data <= data){
                ftra->right = tra->left;
                tra->left->parent = ftra;
            }
            else{
                ftra->left = tra->left;
                tra->left->parent = ftra;
            }
        }
        // 如果父节点不存在, 说明删除的是根节点
        else{
            (*root) = tra->left;
            tra->left->parent = NULL;
        }
    }
    // 如果仅右子树存在, 直接把右子树接到父节点上, 并向上调整
    else if(!tra->left && tra->right){
        // 如果父节点存在, 直接删除
        if(ftra){
            if(ftra->data <= data){
                ftra->right = tra->right;
                tra->right->parent = ftra;
            }
            else{
                ftra->left = tra->right;
                tra->right->parent = ftra;
            }
        }
        // 如果父节点不存在, 说明删除的是根节点
        else{
            (*root) = tra->right;
            tra->right->parent = NULL;
        }
    }
    // 如果左右子树均不存在, 直接删除并向上调整
    else if(!tra->left && !tra->right){
        if(ftra){
            if(ftra->data <= data)
                ftra->right = NULL;
            else
                ftra->left = NULL;
        }
        else{
            (*root) = NULL;
        }
    }
    else
        printf("不可能出现的情况, 有bug\n");

    Destroy_Node(tra);

    tra = ftra;
    while(tra){
        ftra = tra->parent;

        Update_Node_Height(tra);
        Update_Node_BF(tra);

        // LRE
        if(tra->bf == 2 && tra->left && tra->left->bf == -1){
            printf("LR\n");
            AVLNode* A = tra;
            AVLNode* B = tra->left;
            AVLNode* C = tra->left->right;

            // 左旋
            Rotate_Left(root, B, C);
            // 右旋
            Rotate_Right(root, C, A);

            // 更新A B C高度和平衡因子
            Update_Node_Height(B);
            Update_Node_Height(A);
            C->height = MAX(A->height, B->height) + 1;
            Update_Node_BF(B);
            Update_Node_BF(A);
            Update_Node_BF(C);
        }
        // ERL
        else if(tra->bf == -2 && tra->right && tra->right->bf == 1){
            printf("RL\n");
            AVLNode* A = tra;
            AVLNode* B = tra->right;
            AVLNode* C = tra->right->left;

            // 右旋
            Rotate_Right(root, C, B);

            // 左旋
            Rotate_Left(root, A, C);

            // 更新A B C高度和平衡因子
            Update_Node_Height(B);
            Update_Node_Height(A);
            C->height = MAX(A->height, B->height) + 1;
            Update_Node_BF(B);
            Update_Node_BF(A);
            Update_Node_BF(C);
        }
        // LL / LLE
        else if(tra->bf == 2){
            printf("LL\n");
            // 右旋
            Rotate_Right(root, tra->left, tra);
            // printf("右旋\n");

            // 更新新的右子树tra的高度和平衡因子
            Update_Node_Height(tra);
            Update_Node_BF(tra);

            // 更新新的子树父节点tra->parent的高度和平衡因子
            AVLNode* newsubroot = tra->parent;
            Update_Node_Height(newsubroot);
            Update_Node_BF(newsubroot);
        }
        // RR / ERR
        else if(tra->bf == -2){
            printf("RR\n");
            // 左旋
            Rotate_Left(root, tra, tra->right);
            // printf("左旋\n");

            // 更新新的左子树tra的高度和平衡因子
            Update_Node_Height(tra);
            Update_Node_BF(tra);

            // 更新新的子树父节点tra->parent的高度和平衡因子
            AVLNode* newsubroot = tra->parent;
            Update_Node_Height(newsubroot);
            Update_Node_BF(newsubroot);
        }
        // Balance
        else
            printf("平衡, 不需要旋转\n");

        tra = ftra;
    }
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
bool Get_Node(AVLTree root, const datatype data, AVLNode** getnode)
{
    //如果节点为空,返回false,对应情况可能是树为空或者遍历节点到尽头了，返回false并不会使函数提前停止
    if(root==NULL) 
        return false;

    //如果数据匹配,将节点赋给指针参数,并返回true
    if(root->data==data){
        *getnode=root;
        return true;
    }

    //如果节点既不为空,也没有取得想要的节点,则继续递归子节点
    if(Get_Node(root->left, data, getnode)==true)
        return true;
    if(Get_Node(root->right, data, getnode)==true)
        return true;
}

// 得到平衡树中节点的前驱节点
bool Get_Prev(const AVLNode* const node, AVLNode** getnode){
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
bool Get_Next(const AVLNode* const node, AVLNode** getnode){
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

//先序遍历,返回一个节点的父节点
bool Get_Node_Parent(AVLTree root, const datatype data, AVLNode**getnode)
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
bool Get_Node_LChild(AVLTree root,const datatype data, AVLNode**getnode)
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


// 删除一个节点及其子节点
// bool Del_Node(AVLTree* root,const datatype data){
//     // 遍历二叉树
//     DLR_Traverse_AVLT(*root, print);
//     EOL;

//     AVLNode *tra = *root, *ftra = NULL;
//     // 指向删除节点的左右子节点
//     AVLNode *tra_l = NULL;
//     AVLNode* tra_r = NULL;

//     while(tra && tra->data != data){
//         ftra = tra;
//         if(tra->data <= data)
//                 tra = tra->right;
//         else
//                 tra = tra->left;
//     }
    
//     // 找不到该节点
//     if(!tra){
//         printf("某喔\n");
//         return false;
//     }

//     // 重新排列要删除节点的左右子树, 把矮的子树接到高的子树上
//     tra_l = tra->left;
//     tra_r = tra->right;
    
//     AVLNode* son = NULL;
//     AVLNode* tra_l_tra = tra->left;
//     AVLNode* tra_r_tra = tra->right;

//     if(!tra_l && !tra_r){
//         printf("左右子树不存在, 不需要接_0\n");
//     }
//     else if(!tra_l && tra_r){
//         son = tra_r;
//     }
//     else if(tra_l && !tra_r){
//         son = tra_l;
//     }
//     else{
//         if(tra_l->height >= tra_r->height){
//             // 查找要删除节点的左子树接上右子树的节点
//             while(tra_l_tra->right)
//                 tra_l_tra = tra_l_tra->right;

//             tra_l_tra->right = tra_r;
//             tra_r->parent = tra_l_tra;

//             son = tra_l;
//         }
//         else{
//             // 查找要删除节点的左子树接上右子树的节点
//             while(tra_r_tra->left)
//                 tra_r_tra = tra_r_tra->left;

//             tra_r_tra->left = tra_l;
//             tra_l->parent = tra_r_tra;

//             son = tra_r;
//         }
//     }

//     // 删除子节点, 并且将要删除的节点的左右子树接到父节点上;
//     // 如果父节点存在, 直接删除
//     if(ftra){    
//         if(ftra->data <= data){
//             ftra->right = son;

//             if(son)
//                 son->parent = ftra;
//         }
//         else{
//             ftra->left = son;

//             if(son)
//                 son->parent = ftra;
//         }
//     }
//     // 如果父节点不存在, 说明删除的是根节点
//     else{
//         (*root) = son;

//         if(son)
//             son->parent = NULL;
//     }

//     tra->left = tra->right = tra->parent = NULL;
//     free(tra);
//     tra = NULL;

//     // 从插入右子树的位置的父节点开始向上调整高度和平衡因子, 直到根节点
//     // 如果右子树不存在, 直接从删除节点的父节点开始调整
//     if(!son)
//         tra = ftra;
//     else if(tra_r && !tra_l)
//         tra = tra_r;
//     else if(!tra_r && tra_l)
//         tra = tra_l;
//     else if(tra_r && tra_l){
//         if(tra_l->height >= tra_r->height)
//             tra = tra_l_tra;
//         else
//             tra = tra_r_tra;
//     }
//     else{
//         printf("不应该到的分支2\n");
//     }

//     while(tra){
//         ftra = tra->parent;

//         Update_Node_Height(tra);
//         Update_Node_BF(tra);

//         // if(!tra->left && !tra->right){
//         //     tra->height = 1;
//         //     tra->bf = 0;
//         // }
//         // else if(!tra->left && tra->right){
//         //     tra->height = tra->right->height + 1;
//         //     tra->bf = 0 - tra->right->height;
//         // }
//         // else if(tra->left && !tra->right){
//         //     tra->height = tra->left->height + 1;
//         //     tra->bf = tra->left->height;
//         // }
//         // else{
//         //     tra->height = MAX(tra->left->height, tra->right->height) + 1;
//         //     tra->bf = tra->left->height - tra->right->height;
//         // }

//         // LL
//         if((tra->bf == 2 && tra->left->bf == 1) || (tra->bf == 2 && !tra->right)){
//             // 右旋
//             Rotate_Right(root, tra->left, tra);
//             printf("右旋\n");

//             // 更新新的右子树tra的高度和平衡因子
//             Update_Node_Height(tra);
//             Update_Node_BF(tra);

//             // if(!tra->left && !tra->right){
//             //     tra->height = 1;
//             //     tra->bf = 0;
//             // }
//             // else if(!tra->left && tra->right){
//             //     tra->height = tra->right->height + 1;
//             //     tra->bf = 0 - tra->right->height;
//             // }
//             // else if(tra->left && !tra->right){
//             //     tra->height = tra->left->height + 1;
//             //     tra->bf = tra->left->height;
//             // }
//             // else{
//             //     tra->height = MAX(tra->left->height, tra->right->height) + 1;
//             //     tra->bf = tra->left->height - tra->right->height;
//             // }

//             AVLNode* newsubroot = tra->parent;

//             // 更新新的子树父节点tra->parent的高度和平衡因子
//             Update_Node_Height(newsubroot);
//             Update_Node_BF(newsubroot);

//             // if(!newsubroot->left && !newsubroot->right){
//             //     newsubroot->height = 1;
//             //     newsubroot->bf = 0;
//             // }
//             // else if(!newsubroot->left && newsubroot->right){
//             //     newsubroot->height = newsubroot->right->height + 1;
//             //     newsubroot->bf = 0 - newsubroot->right->height;
//             // }
//             // else if(newsubroot->left && !newsubroot->right){
//             //     newsubroot->height = newsubroot->left->height + 1;
//             //     newsubroot->bf = newsubroot->left->height;
//             // }
//             // else{
//             //     newsubroot->height = MAX(newsubroot->left->height, newsubroot->right->height) + 1;
//             //     newsubroot->bf = newsubroot->left->height - newsubroot->right->height;
//             // }
//         }
//         // RR
//         else if((tra->bf == -2 && tra->right->bf == -1) || (tra->bf == -2 && !tra->left)){
//             // 左旋
//             Rotate_Left(root, tra, tra->right);
//             printf("左旋\n");

//             // 更新新的左子树tra的高度和平衡因子
//             Update_Node_Height(tra);
//             Update_Node_BF(tra);

//             // if(!tra->left && !tra->right){
//             //     tra->height = 1;
//             //     tra->bf = 0;
//             // }
//             // else if(!tra->left && tra->right){
//             //     tra->height = tra->right->height + 1;
//             //     tra->bf = 0 - tra->right->height;
//             // }
//             // else if(tra->left && !tra->right){
//             //     tra->height = tra->left->height + 1;
//             //     tra->bf = tra->left->height;
//             // }
//             // else{
//             //     tra->height = MAX(tra->left->height, tra->right->height) + 1;
//             //     tra->bf = tra->left->height - tra->right->height;
//             // }

//             AVLNode* newsubroot = tra->parent;

//             // 更新新的子树父节点tra->parent的高度和平衡因子
//             Update_Node_Height(newsubroot);
//             Update_Node_BF(newsubroot);

//             // if(!newsubroot->left && !newsubroot->right){
//             //     newsubroot->height = 1;
//             //     newsubroot->bf = 0;
//             // }
//             // else if(!newsubroot->left && newsubroot->right){
//             //     newsubroot->height = newsubroot->right->height + 1;
//             //     newsubroot->bf = 0 - newsubroot->right->height;
//             // }
//             // else if(newsubroot->left && !newsubroot->right){
//             //     newsubroot->height = newsubroot->left->height + 1;
//             //     newsubroot->bf = newsubroot->left->height;
//             // }
//             // else{
//             //     newsubroot->height = MAX(newsubroot->left->height, newsubroot->right->height) + 1;
//             //     newsubroot->bf = newsubroot->left->height - newsubroot->right->height;
//             // }
//         }
//         // LR
//         else if(tra->bf == 2 && tra->left->bf == -1){
//             printf("LR\n");
//             AVLNode* A = tra;
//             AVLNode* B = tra->left;
//             AVLNode* C = tra->left->right;

//             // 左旋
//             Rotate_Left(root, B, C);

//             // 右旋
//             Rotate_Right(root, C, A);

//             // 更新A B C高度和平衡因子
//             if(data > C->data){
//                 A->bf = 0;
//                 B->bf = 1;
//                 C->bf = 0;
//             }
//             else if(data < C->data){
//                 A->bf = -1;
//                 B->bf = 0;
//                 C->bf = 0;
//             }
//             else{
//                 A->bf = 0;
//                 B->bf = 0;
//             }

//             Update_Node_Height(B);
//             // if(!B->left && !B->right)
//             //     B->height = 1;
//             // else if(!B->left && B->right)
//             //     B->height = B->right->height + 1;
//             // else if(B->left && !B->right)
//             //     B->height = B->left->height + 1;
//             // else
//             //     B->height = MAX(B->left->height, B->right->height) + 1;

//             Update_Node_Height(A);
//             // if(!A->left && !A->right)
//             //     A->height = 1;
//             // else if(!A->left && A->right)
//             //     A->height = A->right->height + 1;
//             // else if(A->left && !A->right)
//             //     A->height = A->left->height + 1;
//             // else
//             //     A->height = MAX(A->left->height, A->right->height) + 1;

//             C->height = MAX(A->height, B->height) + 1;
//         }
//         // RL
//         else if(tra->bf == -2 && tra->right->bf == 1){
//             printf("RL\n");
//             AVLNode* A = tra;
//             AVLNode* B = tra->right;
//             AVLNode* C = tra->right->left;

//             // 右旋
//             Rotate_Right(root, C, B);

//             // 左旋
//             Rotate_Left(root, A, C);

//             // 更新A B C高度和平衡因子
//             if(data > C->data){
//                 A->bf = 1;
//                 B->bf = 0;
//                 C->bf = 0;
//             }
//             else if(data < C->data){
//                 A->bf = 0;
//                 B->bf = -1;
//                 C->bf = 0;
//             }
//             else{
//                 A->bf = 0;
//                 B->bf = 0;
//             }

//             Update_Node_Height(B);
//             // if(!B->left && !B->right)
//             //     B->height = 1;
//             // else if(!B->left && B->right)
//             //     B->height = B->right->height + 1;
//             // else if(B->left && !B->right)
//             //     B->height = B->left->height + 1;
//             // else
//             //     B->height = MAX(B->left->height, B->right->height) + 1;

//             Update_Node_Height(A);
//             // if(!A->left && !A->right)
//             //     A->height = 1;
//             // else if(!A->left && A->right)
//             //     A->height = A->right->height + 1;
//             // else if(A->left && !A->right)
//             //     A->height = A->left->height + 1;
//             // else
//             //     A->height = MAX(A->left->height, A->right->height) + 1;

//             C->height = MAX(A->height, B->height) + 1;
//         }
//         // Balance
//         else{
//             Update_Node_Height(tra);
//             printf("基本平衡, 不需要旋转\n");
//         }
        
//         tra = ftra;

//         // 遍历二叉树
//         DLR_Traverse_AVLT(*root, print);
//         EOL;
//     }

//     return true;
// }