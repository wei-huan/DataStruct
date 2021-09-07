#include"BinaryInsertSort.h"

void Binary_Insert_Sort(SortDataPtrType UnSortData, int length){
    int binary_index = 1, up_index, down_index;

    // 从第二个元素开始比较
    for(int di = 2; di <= length; di++){
        UnSortData[0] = UnSortData[di];
        down_index = 1;
        up_index = di;
        binary_index  = di / 2;

        // 要插入之前的元素是顺序的, 所以可以折半查找
        while(!(UnSortData[0].key < UnSortData[binary_index].key && UnSortData[0].key >= UnSortData[binary_index - 1].key)){
            // 如果是边缘的两个数要单独考虑
            if(binary_index == di - 1 && UnSortData[binary_index].key <= UnSortData[di].key){
                    binary_index = di;
                    break;
            }

            if(binary_index == 1 && UnSortData[binary_index].key >= UnSortData[di].key)
                break;
            
            if(UnSortData[binary_index].key <= UnSortData[0].key){
                down_index = binary_index;
                binary_index = (down_index + up_index) / 2;
            }
            else if(UnSortData[binary_index - 1].key >= UnSortData[0].key){
                up_index = binary_index;
                binary_index = (down_index + up_index) / 2;
            }
        }

        // binary_index不是最后一个, 所以binary_index开始的元素要往后挪
        if(binary_index < di){
            for(int mi = di - 1; mi >= binary_index; mi--)
                UnSortData[mi + 1] = UnSortData[mi];
            
            UnSortData[binary_index] = UnSortData[0];
        }

        for(int di = 1; di < 11; di++)
            printf("%2d ", UnSortData[di].key);
        EOL;
    }
}
