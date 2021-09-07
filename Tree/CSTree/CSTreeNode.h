typedef char CSData;

typedef struct CSNode
{
    CSData Data;
    struct CSNode *FirstChild;
    struct CSNode *NextSibling;
}CSNode,*CSTree;