#include "QuickSort.h"

// 快速排序, 从小到大
void Quick_Sort(SortDataPtrType UnSortData, int low, int high){
    int mid;

    if(low < high){
        mid = Quick_Pass(UnSortData, low, high);
        Quick_Sort(UnSortData, mid + 1, high);
        Quick_Sort(UnSortData, low, mid - 1);
    }
}

// 
int Quick_Pass(SortDataPtrType UnSortData, int low, int high){
    int mid = low;
    SortDataType Mid = UnSortData[low]; // 取基准数据

    while(low < high){
        // 从右到左找比Mid.key小的数据, 如果找到则将其填入UnSortData[low], 此时low下标的单元是不需要保留的
        while(low < high && UnSortData[high].key >= Mid.key)
            high--;

        if(low < high){
            UnSortData[low] = UnSortData[high];
            low++;
        }

        // 从左到右找比Mid.key大的数据, 如果找到则将其填入UnSortData[high], 此时high下标的单元是不需要保留的
        while(low < high && UnSortData[low].key < Mid.key)
            low++;

        if(low < high){
            UnSortData[high] = UnSortData[low];
            high--;
        }
    }

    // 将基准数据保存在mid位置
    mid = low;
    UnSortData[mid] = Mid;
    return mid;
}
