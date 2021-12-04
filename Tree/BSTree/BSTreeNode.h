typedef int datatype;

typedef struct BSNode
{
   datatype Data;
   struct BSNode *LeftChild;
   struct BSNode *RightChild; 
}BSNode,*BSTree;
