#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include "cyclequeueelement.h"
#define Maxsize 50

typedef struct Queue{
    datatype element[Maxsize];
    int front,rear;     
}Queue_Type;

bool init_queue(Queue_Type *Q);
bool enter_queue(Queue_Type *Q, datatype newnode);
bool exit_queue(Queue_Type *Q, datatype *exitnode);
bool is_empty(Queue_Type *Q);
bool is_full(Queue_Type *Q);
void destroy_queue(Queue_Type *Q);
void YangHuiTriangle(int line);
