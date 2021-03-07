#ifndef parenttree
#define Parenttree

#include "ParentTreeNode.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

typedef struct ParentTree
{
    PTNode PT[MAX];
    int nodenum;
}ParentTree;

#endif