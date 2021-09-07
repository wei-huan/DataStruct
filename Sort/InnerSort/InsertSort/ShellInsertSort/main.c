#include"ShellInsertSort.h"

int main(){
    SortDataType SortDataArray[45 + 1];
    
    // 随机生成10个0-99的数
    srand((unsigned)time(NULL));
    for(int di = 1; di < 46; di++){
        SortDataArray[di].key = rand() % 100;
        printf("%2d ", SortDataArray[di].key);
    }
    EOL;

    Shell_Insert_Sort(SortDataArray, 45);
    
    for(int di = 1; di < 46; di++)
        printf("%2d ", SortDataArray[di].key);
    EOL;
    
    return 0;
}