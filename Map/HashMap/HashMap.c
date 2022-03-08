#include "HashMap.h"

// 除留余数法
int Remainder_HashFunc(KeyType k, int div) {
    int sum = 0, idx = 0;
    while (k[idx]) {
        sum += *k;
        idx++;
    }
    return sum % div;
}

// 平方取中法
int SquareMid_HashFunc(KeyType k) {}

void HashInit(HashMapTypePtr hm) {}

// 选择除留余数法， 再散列解决冲突
// 找键对应的数组下标
int HashSearch(HashMapType hm, KeyType k) {
    int idx = Remainder_HashFunc(k, PRIMENUM1);
    // 有空位 或 当前数据已经占了
    if (hm[idx].key == 0 || hm[idx].key == k) {
        return idx;
    }
    // 其他数据已经占了
    else {
        idx = Remainder_HashFunc(k, PRIMENUM2);
        if (hm[idx].key == 0 || hm[idx].key == k)
            return idx;
        else
            return -1;
    }
}

// 插入记录，如果有记录则更新值
int HashInsert(HashMapTypePtr hm, RecordType r) {
    int idx = HashSearch(*hm, r.key);
    if (idx != -1)
        (*hm)[idx] = r;
    return idx;
}

// 删除记录，如果没有就啥都不做
int HashDelete(HashMapTypePtr hm, KeyType k) {
    int idx = HashSearch(*hm, k);
    if (idx != -1) {
        (*hm)[idx].key = 0;
        (*hm)[idx].value = 0;
    }
    return idx;
}

int HashRecordGet(HashMapType hm, KeyType k, RecordTypePtr r) {
    int idx = HashSearch(hm, k);
    if (idx != -1) {
        *r = hm[idx];
    } else {
        r = NULL;
    }
    return idx;
}

int HashValueGet(HashMapType hm, KeyType k, ValueTypePtr v) {
    int idx = HashSearch(hm, k);
    if (idx != -1) {
        *v = hm[idx].value;
    } else {
        v = NULL;
    }
    return idx;
}