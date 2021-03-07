#include "Stack.h"

void InitStack(Stack *S)
{
    S->top=-1;
}

void ClearStack(Stack *S)
{
    S->top=-1;
}

bool Push(Stack *S,const elemtype pushdata)
{
    if(is_Stack_Full(S)==true)
    {
        printf("栈满,无法入栈\n");
        return false;
    }

    S->top++;
    S->elem[S->top]=pushdata;
    
    return true;
}

elemtype Pop(Stack *S)
{
    if(is_Stack_Empty(S)==true)
    {
        printf("栈空,无法出栈\n");
        exit(0);
    }

    S->top--;
    return S->elem[S->top+1];
}

bool is_Stack_Empty(Stack *S)
{
    if(S->top<0)
        return true;
    else
        return false;
}

bool is_Stack_Full(Stack *S)
{
    if(S->top>=StackSize-1)
        return true;
    else
        return false;
}

int Get_Stack_Top(Stack *S)
{
    return S->top;
}