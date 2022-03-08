#include <stdio.h>
#include "HashMapType.h"

#define MAX_LEN 100

typedef void* ArgType;
typedef int SEARCHCALLBACK(KeyType k, ArgType arg0, ArgType arg1);
typedef RecordType HashMapType[MAX_LEN];
typedef HashMapType* HashMapTypePtr;

int Remainder_HashFunc(KeyType k, int div);
int SquareMid_HashFunc(KeyType k);
int HashSearch(HashMapType hm, KeyType k);
int HashInsert(HashMapTypePtr hm, RecordType r);
int HashDelete(HashMapTypePtr hm, KeyType k);
void HashRecordGet(HashMapType hm, KeyType k, RecordTypePtr r);
void HashValueGet(HashMapType hm, KeyType k, ValueTypePtr v);
