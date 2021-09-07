#include "SimpleSelectSort.h"

// 简单选择排序, 从小到大
void Simple_Select_Sort(SortDataPtrType UnSortData, int length){
    int min_index;

    for(int di = 1; di <= length - 1; di++){
        min_index = di;

        for(int mi = di + 1; mi <= length; mi++)
            if(UnSortData[mi].key < UnSortData[min_index].key)
                min_index = mi;

        if(min_index != di){
            UnSortData[0] = UnSortData[di];
            UnSortData[di] = UnSortData[min_index];
            UnSortData[min_index] = UnSortData[0];
        }
    }
}
