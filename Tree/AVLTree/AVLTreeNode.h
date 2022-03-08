typedef int datatype;

typedef struct AVLNode{
   int bf;               // 平衡因子
   int height;
   datatype data;
   struct AVLNode *left;
   struct AVLNode *right;
   struct AVLNode *parent;
}AVLNode, *AVLTree;
