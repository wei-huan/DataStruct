#pragma once
#include <stdio.h>
#include <stdlib.h>
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
void Shell_Insert_Sort(SortDataPtrType UnSortData, int length);
void Shell_SubSort(SortDataPtrType UnSortData, int length, int step, int start_idx);