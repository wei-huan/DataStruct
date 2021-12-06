typedef int datatype;

typedef struct AVLNode{
   datatype data;
   int height;
   int bf;               // 平衡因子
   struct AVLNode *parent;          
   struct AVLNode *left;
   struct AVLNode *right;
}AVLNode, *AVLTree;
