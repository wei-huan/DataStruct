#include <stdio.h>
#include "HashMapType.h"

#define MAX_LEN 100
#define PRIMENUM1 101
#define PRIMENUM2 107

typedef void* ArgType;
typedef int SEARCHCALLBACK(KeyType k, ArgType arg0, ArgType arg1);
typedef RecordType HashMapType[MAX_LEN];
typedef HashMapType* HashMapTypePtr;

void HashInit(HashMapTypePtr hm);
int Remainder_HashFunc(KeyType k, int div);
int SquareMid_HashFunc(KeyType k);
int HashSearch(HashMapType hm, KeyType k);
int HashInsert(HashMapTypePtr hm, RecordType r);
int HashDelete(HashMapTypePtr hm, KeyType k);
int HashRecordGet(HashMapType hm, KeyType k, RecordTypePtr r);
int HashValueGet(HashMapType hm, KeyType k, ValueTypePtr v);
