typedef char* KeyType;
typedef KeyType* KeyTypePtr;
typedef int ValueType;
typedef ValueType* ValueTypePtr;

typedef struct Record {
    KeyType key;
    ValueType value;
} RecordType;

typedef RecordType* RecordTypePtr;
