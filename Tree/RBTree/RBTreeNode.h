typedef int datatype;
typedef int keytype;

typedef struct RBNode{
   datatype data;
   keytype key;
   char* color;
   struct RBNode *parent;          
   struct RBNode *left;
   struct RBNode *right;
}RBNode, *RBTree;
