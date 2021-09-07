#include "TreeSelectSort.h"

// 树形选择排序, 从小到大
void Tree_Select_Sort(SortDataPtrType UnSortData, int length){
    // 构造一个满二叉树, 不够的数据用无穷填补, 0号数据做监视哨
    int log2_length, fullbitree_length, leave_base_idx, empty_node_idx, tree_layer, lst_layer_base_idx;

    log2_length = (int)(log(length)/log(2)) + 1;
    tree_layer = log2_length + 1;
    fullbitree_length = 2 * (int)pow(2, log2_length) - 1;
    leave_base_idx = (fullbitree_length + 1)/2;
    empty_node_idx = leave_base_idx + length;
    SortDataType SortTree[fullbitree_length + 1];

    // 叶子节点填入要排序的数据, 空位填无穷
    for(int ni = 1; ni <= length; ni++)
        // UnSortData[1] 才是起始数据, leave_base_idx是SortTree要复制的起始下标, 所以加了ni后要减1
        SortTree[leave_base_idx + ni - 1] = UnSortData[ni];

    while(empty_node_idx != fullbitree_length + 1)
        SortTree[empty_node_idx++].key = INFINITY;

    // 2进1构建树
    // 大循环, 循环次数为树的树的层数 - 1
    for(int li = tree_layer - 1; li >= 1; li--){
        lst_layer_base_idx = (int)pow(2, li - 1);
        
        // 小循环, 两两比较循环次数为2 ^ (tree_layer - 1)
        for(int ci = 0; ci < (int)pow(2, li - 1); ci++)
            if(SortTree[2 * (lst_layer_base_idx + ci)].key <= SortTree[2 * (lst_layer_base_idx + ci) + 1].key)
                SortTree[lst_layer_base_idx + ci].key = SortTree[2 * (lst_layer_base_idx + ci)].key;
            else
                SortTree[lst_layer_base_idx + ci].key = SortTree[2 * (lst_layer_base_idx + ci) + 1].key;
    }

    //排序, 循环次数为数据长度 - 1
    int round = 1, min_idx;

    while(round <= length){
        // 将本轮最小的数写到要到排列的数组的对应位置
        min_idx = 1;
        UnSortData[round] = SortTree[min_idx];

        // 找到最小数在原来的位置, 并置无穷
        for(int li = 1; li <= tree_layer - 1; li++)
            if(SortTree[min_idx].key == SortTree[2 * min_idx].key)
                min_idx = 2 * min_idx;
            else
                min_idx = 2 * min_idx + 1;
        
        SortTree[min_idx].key = INFINITY;

        // 重新设定相关分支, 选出最小值
        for(int li = tree_layer - 1; li >= 1; li--){
            if(SortTree[(min_idx / 2) * 2].key <= SortTree[(min_idx / 2) * 2 + 1].key)
                SortTree[min_idx / 2] = SortTree[(min_idx / 2) * 2];
            else
                SortTree[min_idx / 2] = SortTree[(min_idx / 2) * 2 + 1];

            min_idx = min_idx / 2;
        }
        round++;
    }
}
