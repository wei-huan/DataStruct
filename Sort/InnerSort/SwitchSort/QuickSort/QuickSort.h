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
void Quick_Sort(SortDataPtrType UnSortData, int low, int high);
int Quick_Pass(SortDataPtrType UnSortData, int low, int high);