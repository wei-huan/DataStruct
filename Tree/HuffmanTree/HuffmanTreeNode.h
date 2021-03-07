#define MAX_LEAF_NUM    20
#define MAX_NODE_NUM    (2*MAX_LEAF_NUM-1)

typedef struct HTNode
{
    int weight;
    int parent,LeftChild,RightChild;
}HTNode,HuffmanTree[MAX_NODE_NUM+1];
