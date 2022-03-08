#include "HashMap.h"

int main() {
    HashMapType hm;
    RecordType r;
    RecordType r1;
    int idx = 0;
    r.key = "Hello";
    r.value = 13;
    HashInsert(&hm, r);
    r.key = "World";
    r.value = 57;
    HashInsert(&hm, r);
    idx = HashRecordGet(hm, "Hello", &r1);
    printf("r1: %d (%s, %d)\n", idx, r1.key, r1.value);
    idx = HashRecordGet(hm, "World", &r1);
    printf("r1: %d (%s, %d)\n", idx, r1.key, r1.value);
}
