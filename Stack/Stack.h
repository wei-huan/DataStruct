#ifndef stack
#define stack

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <malloc.h>
#include "/home/weihuan/C/Datastruct/Tree/BiTree/BiTreeNode.h"

#define StackSize 100

typedef BiNode* elemtype;
typedef struct Stack
{
    elemtype elem[StackSize];
    int top;
}Stack,*StackPtr;

extern void InitStack(Stack *S);
extern void ClearStack(Stack *S);
extern bool Push(Stack *S,const elemtype pushdata);
extern elemtype Pop(Stack *S);
extern bool is_Stack_Empty(Stack *S);
extern bool is_Stack_Full(Stack *S);
extern int Get_Stack_Top(Stack *S);

#endif