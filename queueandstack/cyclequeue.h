#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>



#define Maxsize 50

typedef int datatype;

typedef struct queue
{
    datatype element[Maxsize];
    int front,rear;     
}queuearray;

extern bool init_queue(queuearray *Q);
extern bool enter_queue(queuearray *Q, datatype newnode);
extern bool exit_queue(queuearray *Q, datatype *exitnode);
extern bool is_empty(queuearray *Q);
extern bool is_full(queuearray *Q);
extern void destroy_queue(queuearray *Q);
extern void YangHuiTriangle(int line);