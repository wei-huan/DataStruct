#include "ShellInsertSort.h"

void Shell_Insert_Sort(SortDataPtrType UnSortData, int length){
    int step = length / 3 + 1;

    while(1){
        printf("step: %d\n", step);

        for(int idx = 1; idx <= step; idx++)
            Shell_SubSort(UnSortData, length, step, idx);
        
        for(int di = 1; di <= length; di++)
            printf("%2d ", UnSortData[di].key);
        EOL;

        if(step == step / 3 + 1)
            break;
        else
            step = step / 3 + 1;
    }
}

void Shell_SubSort(SortDataPtrType UnSortData, int length, int step, int start_idx){
    int compare_idx = start_idx;

    // 从第二个元素开始比较
    for(int di = start_idx + step; di <= length; di = di + step){
        UnSortData[0] = UnSortData[di];

        compare_idx = start_idx;

        while(UnSortData[compare_idx].key <= UnSortData[0].key && compare_idx < di)
            compare_idx = compare_idx + step;

        // compare_Idx不是最后一个, 所以compare_Idx开始的元素要往后挪
        if(compare_idx < di){

            for(int mi = di - step; mi >= compare_idx; mi = mi - step)
                UnSortData[mi + step] = UnSortData[mi];
            
            UnSortData[compare_idx] = UnSortData[0];
        }
    }
}
