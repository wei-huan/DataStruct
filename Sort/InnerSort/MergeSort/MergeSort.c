#include "MergeSort.h"

// 归并排序, 从小到大
void Merge_Sort(SortDataPtrType UnSortData, int start, int end, SortDataPtrType SortedData){
    int mid = (start + end) / 2;
    SortDataPtrType SortAidArray;

    if(start != end){
        SortAidArray = (SortDataPtrType)malloc(sizeof(SortDataType) * (end - start + 1 + 1)); // 长度加1
        // 先对子序列归并排序
        Merge_Sort(UnSortData, start, mid, SortAidArray);
        Merge_Sort(UnSortData, mid + 1, end, SortAidArray + (mid - start + 1));

        // 对排好的子序列合并
        Merge(SortAidArray, 1, mid - start + 1, end - start + 1, SortedData);
        
        free(SortAidArray);
    }
    else
        SortedData[1] = UnSortData[start];
}

// 合并 UnSortData 左右两边子项到 SortedData
void Merge(SortDataPtrType UnSortData, int start, int mid, int end, SortDataPtrType SortedData){
    int lft_idx = start, rght_idx = mid + 1, s_idx = 1;

    while(lft_idx <= mid || rght_idx <= end){
        if(lft_idx > mid )
            SortedData[s_idx++] = UnSortData[rght_idx++];
        else if(rght_idx > end)
            SortedData[s_idx++] = UnSortData[lft_idx++];
        else{
            if(UnSortData[lft_idx].key <= UnSortData[rght_idx].key)
                SortedData[s_idx++] = UnSortData[lft_idx++];
            else
                SortedData[s_idx++] = UnSortData[rght_idx++];
        }
    }
}
