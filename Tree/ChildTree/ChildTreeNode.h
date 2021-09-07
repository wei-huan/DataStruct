typedef char CTNodeData;

#define MAX_NUM 100

typedef struct ChildNode
{
    CTNodeData Data;
    struct ChildNode* NextSibling;
}ChildNode;

typedef struct CTNode
{
    CTNodeData Data;
    ChildNode* FirstChild;
}CTNode;

typedef struct ChildTree
{
    struct CTNode[MAX_NUM];
    int nodenum;
}ChildTree;