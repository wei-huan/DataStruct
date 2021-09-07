#include "cyclequeue.h"

#define EOL putchar('\n')

bool init_queue(Queue_Type *Q){
    Q->front=Q->rear=0;
    return true;
}

bool enter_queue(Queue_Type *Q, datatype newnode){
    if (!is_full(Q))
    {
        Q->element[(Q->rear)%(Maxsize)]=newnode;
        Q->rear++;
        return true;
    }
    else
        return false;
}

bool exit_queue(Queue_Type *Q, datatype *exitnode){
    if (!is_empty(Q)){
        *exitnode = Q->element[(Q->front++)%(Maxsize)];
        return true;
    }
    else
        return false;
}

bool is_empty(Queue_Type *Q){
    if (Q->rear==Q->front)
        return true;
    else
        return false;
}

bool is_full(Queue_Type *Q){
    if (Q->rear == Q->front + Maxsize - 1)
        return true;
    else
        return false;
}


// //利用队列打印杨辉三角
// void YangHuiTriangle(int line){
//     Queue_Type Q;
    
//     datatype exit;
    
//     int count1=0,count2=0;
    
//     init_queue(&Q);
    
//     //第一行进队
//     enter_queue(&Q,1);

//     while (count1<line-1)//从第二行开始{
//         //最左边元素进队
//         enter_queue(&Q,1);

//         //n行中间n-2个元素
//         while (count2<count1&&line-2>0&&count1>0)//第3行开始{
//             enter_queue(&Q,Q.element[(Q.front)%(Maxsize)]+Q.element[(Q.front+1)%(Maxsize)]);
            
//             exit_queue(&Q,&exit);
//             printf("%d\t",exit);

//             count2++;
//         }
        
//         count2=0;
//         //最右边元素进队
//         enter_queue(&Q,1);

//         //打印前一行最后一个元素
//         exit_queue(&Q,&exit);
//         printf("%d\t",exit);
//         EOL;

//         count1++;
//     }

//     //打印最后一行
//     while (!is_empty(&Q)){
//         exit_queue(&Q,&exit);
//         printf("%d\t",exit);
//     }
//     EOL;
// }

