typedef char datatype;

typedef struct BiNode
{
   datatype Data;
   struct BiNode *LeftChild;
   struct BiNode *RightChild; 
}BiNode,*BiTree;
