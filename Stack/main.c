#include "stack.h"

int main()
{
    Stack S;
    BiNode retnode;
    int i='A';

    InitStack(&S);
    
    while(i<='A'+100)
    {
        BiNode node;

        node.Data=i;
        node.LeftChild=NULL;
        node.RightChild=NULL;

        Push(&S,node);
        i++;
    }

    retnode=Pop(&S);

    printf("出栈数据为%c\n",retnode.Data);
    printf("栈顶指向%d\n",Get_Stack_Top(&S));

    return 0;
}