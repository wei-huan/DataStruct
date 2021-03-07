//哈夫曼代码的个数等于哈夫曼树叶节点个数
#define MAX_CODE_NUM    20
//哈夫曼代码的最大位数等于哈夫曼树叶节点个数减1
#define MAX_CODE_BIT    (MAX_CODE_NUM-1)
//哈夫曼代码最大字符串位数等于哈夫曼代码加1为\0
#define MAX_CODE_CHAR   (MAX_CODE_BIT+1)

typedef char HuffmanCode[7];
typedef HuffmanCode HuffmanCodeTable[MAX_CODE_NUM+1];