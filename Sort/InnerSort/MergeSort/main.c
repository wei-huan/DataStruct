#include "MergeSort.h"

int main(){
    SortDataType SortDataArray[10 + 1];
    
    // 随机生成10个0-99的数
    srand((unsigned)time(NULL));
    for(int di = 1; di < 11; di++){
        SortDataArray[di].key = rand() % 100;
        // 延迟函数, 防止设值快于随机数生成
        printf("%2d ", SortDataArray[di].key);
    }
    EOL;

    Merge_Sort(SortDataArray, 1, 10, SortDataArray);
    
    for(int di = 1; di < 11; di++)
        printf("%2d ", SortDataArray[di].key);
    EOL;

    return 0;
}
