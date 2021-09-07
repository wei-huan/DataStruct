#include "HeapSort.h"

// 堆排序, 从小到大
void Heap_Sort(SortDataPtrType UnSortData, int length){
    Crt_Heap(UnSortData, length);

    for(int di = length; di >= 2; di--){
        UnSortData[0] = UnSortData[1];
        UnSortData[1] = UnSortData[di];
        UnSortData[di] = UnSortData[0];

        Adjst_Heap(UnSortData, 1, di - 1);
    }
}

// 建立大根堆
void Crt_Heap(SortDataPtrType UnSortData, int length){
    for(int ni = length / 2; ni >= 1; ni--)
        Adjst_Heap(UnSortData, ni, length);
}

// 将堆调整为大根堆
void Adjst_Heap(SortDataPtrType UnSortData, int start, int end){
    bool swap_fin_flag = false;
    int swp_idx = start, sub_swp_idx;

    while(swp_idx <= end && swap_fin_flag == false){
        sub_swp_idx = swp_idx * 2;

        if(sub_swp_idx <= end){
            if(sub_swp_idx + 1 <= end && UnSortData[sub_swp_idx + 1].key > UnSortData[sub_swp_idx].key)
                sub_swp_idx = sub_swp_idx + 1;

            if(UnSortData[swp_idx].key < UnSortData[sub_swp_idx].key){
                UnSortData[0] = UnSortData[swp_idx];
                UnSortData[swp_idx] = UnSortData[sub_swp_idx];
                UnSortData[sub_swp_idx] = UnSortData[0];

                swp_idx = sub_swp_idx;
            }
            else
                swap_fin_flag = true;
            
        }
        else
            swap_fin_flag = true;
    }
}
