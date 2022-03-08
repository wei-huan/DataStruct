#include "HashMapType.h"

// 除留余数法
int Remainder_HashFunc(KeyType k, int div) {
    int sum = 0;
    while(*k) {
        sum += *k;
    }
    return sum % div;
}

// 平方取中法
int SquareMid_HashFunc(KeyType k) {

}

// 选择除留余数法， 再散列解决冲突
int HashSearch(HashMapType hm, KeyType k) {

}

int HashInsert(HashMapTypePtr hm, RecordType r) {
    int idx = HashSearch(*hm, r.key);
    if(idx != -1)
        (*hm)[idx] = r;
    return idx;
}

int HashDelete(HashMapTypePtr hm, KeyType k) {
    int idx = HashSearch(*hm, k);
    if(idx != -1){
        (*hm)[idx].key = 0;
        (*hm)[idx].value = 0;
    }
    return idx;
}

void HashRecordGet(HashMapType hm, KeyType k, RecordTypePtr r) {
    int idx = HashSearch(hm, k);
    if( idx != -1 ){
        *r =  hm[idx];
    } else {
        r = NULL;
    }
}

void HashValueGet(HashMapType hm, KeyType k, ValueTypePtr v) {
    int idx = HashSearch(hm, k);
    if( idx != -1 ){
        *v =  hm[idx].value;
    } else {
        v = NULL;
    }
}