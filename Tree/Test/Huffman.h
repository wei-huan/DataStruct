#pragma once

#define MAXN	20
#define MAXM	(2*MAXN)

typedef char HuffmanCode[MAXN+1];
typedef HuffmanCode HuffmanCodeTable[MAXN+1];

typedef struct 
{
	int weight;
	int parent, LChild, RChild;
} HTNode, HuffmanTree[MAXM];

extern void CreateHuffmanTree(HuffmanTree ht, int *w, int n);
extern void CreateHuffmanCodeTable(HuffmanTree ht, HuffmanCodeTable hc, int n);
extern void PrintHuffmanTree(HuffmanTree HT, int m);
extern void PrintHuffmanCodeTable(HuffmanTree ht, HuffmanCodeTable hc, int n);