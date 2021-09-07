#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_DATA_NUM    20
#define EOL putchar('\n')
#define KEY_SIZE 2

typedef int KeyType;
typedef int InformType;
typedef struct {
    KeyType keys[KEY_SIZE];
    InformType inform;
}RecordType;

typedef RecordType SortDataType;
typedef RecordType* SortDataPtrType;


void Radix_Sort(SortDataPtrType UnSortData, int length);
void Distribute();
void Collect();
