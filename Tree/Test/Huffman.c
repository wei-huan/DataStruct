#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Huffman.h"

static void Select(HuffmanTree ht, int n, int *s1, int *s2)
{
    int i, min;

    min = -1;
    for (i = 1; i <= n; ++i)
        if (ht[i].parent == 0 && (min == -1 || ht[i].weight < ht[min].weight))
            min = i;
    *s1 = min;

    min = -1;
    for (i = 1; i <= n; ++i)
        if (ht[i].parent == 0 && (min == -1 || ht[i].weight < ht[min].weight) && i != *s1)
            min = i;
    *s2 = min;
}

void CreateHuffmanTree(HuffmanTree ht, int *w, int n)
{
    int i, s1, s2;
    int m = 2 * n - 1;

    for (i = 1; i <= m; ++i)
    {
        ht[i].weight = i <= n ? w[i] : 0;
        ht[i].parent = ht[i].LChild = ht[i].RChild = 0;
    }

    for (i = n + 1; i <= m; ++i)
    {
        Select(ht, i - 1, &s1, &s2);
        ht[s1].parent = ht[s2].parent = i;
        ht[i].LChild = s1;
        ht[i].RChild = s2;
        ht[i].weight = ht[s1].weight + ht[s2].weight;
    }
}

void PrintHuffmanTree(HuffmanTree HT, int m)
{
    for (int i = 1; i <= m; ++i)
        printf("%2d:(%4d, %4d, %4d, %4d)\n", i, HT[i].weight, HT[i].parent, HT[i].LChild, HT[i].RChild);
}

void CreateHuffmanCodeTable(HuffmanTree ht, HuffmanCodeTable hc, int n)
{
    HuffmanCode cd;
    int i, start, c;
    int p;

    cd[n] = '\0'; /*从右向左逐位存放编码，首先存放编码结束符*/
    for (i = 1; i <= n; ++i)   /*求n个叶子结点对应的哈夫曼编码*/
    {
        start = n;   /*初始化编码起始指针*/
        for (c = i, p = ht[i].parent; p != 0; c = p, p = ht[p].parent) /*从叶子到根结点求编码*/
            cd[--start] = ht[p].LChild == c ? '0' : '1';
        strcpy(hc[i], &cd[start]);
    }
}

void PrintHuffmanCodeTable(HuffmanTree ht, HuffmanCode *hc, int n)
{
    for (int i = 1; i <= n; ++i)
        printf("The node weighs %d was encoded as %s\n", ht[i].weight, hc[i]);
    printf("\n");
}
