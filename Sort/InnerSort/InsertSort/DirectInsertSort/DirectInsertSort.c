#include "DirectInsertSort.h"

// 直插排序, 从小到大
void Direct_Insert_Sort(SortDataPtrType UnSortData, int length){
    int compare_Idx = 1;

    // 从第二个元素开始比较
    for(int di = 2; di <= length; di++){
        UnSortData[0] = UnSortData[di];
        compare_Idx = 1;

        while(UnSortData[compare_Idx].key <= UnSortData[0].key && compare_Idx < di)
            compare_Idx++;

        // compare_Idx不是最后一个, 所以compare_Idx开始的元素要往后挪
        if(compare_Idx < di){

            for(int mi = di - 1; mi >= compare_Idx; mi--)
                UnSortData[mi + 1] = UnSortData[mi];
            
            UnSortData[compare_Idx] = UnSortData[0];
        }
    }
}
