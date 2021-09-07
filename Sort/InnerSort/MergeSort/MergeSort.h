#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_DATA_NUM    20
#define EOL putchar('\n')

typedef int KeyType;
typedef int InformType;
typedef struct {
    KeyType key;
    InformType inform;
}RecordType;

typedef RecordType SortDataType;
typedef RecordType* SortDataPtrType;
void Merge_Sort(SortDataPtrType UnSortData, int start, int end, SortDataPtrType SortedData);
void Merge(SortDataPtrType UnSortData, int start, int mid, int end, SortDataPtrType SortedData);

