#include <stdio.h>

#include "Huffman.h"

#define N	5
#define M	(2*N-1)

int main()
{ 
	HuffmanTree HT; 
	HuffmanCodeTable HC; 
	int w[N+1] = {-1, 5, 7, 3, 2, 8}; //{-1, 40, 30, 15, 5, 4, 3, 3}; 
	
	CreateHuffmanTree(HT, w, N); 
	CreateHuffmanCodeTable(HT, HC, N);

	PrintHuffmanTree(HT, M); 
	printf("\n");
    PrintHuffmanCodeTable(HT, HC, N);
	
    return 0;
} 