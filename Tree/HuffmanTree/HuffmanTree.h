#ifndef Huffman_Tree
#define Huffman_Tree

#include "HuffmanTreeNode.h"
#include "HuffmanCode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>

//说明:HT是HuffmanTree的简称
#define INFINITY    32678

typedef void CALLBACK(HTNode);

extern int Creat_HT(HuffmanTree HT,const int* HuffmanWeight, const int WeightNum);
extern void Traverse_HT(const HuffmanTree HT,const int NodeNum,CALLBACK visitnode);
extern void Creat_HuffmanCode(const HuffmanTree HT,HuffmanCodeTable HCTable, const int CodeNum);
extern void Traverse_HCTable(const HuffmanTree HT,const HuffmanCodeTable HCTable,const int CodeNum);

#endif