typedef char VertexData_Type;
typedef int ArcWeight_Type;

typedef struct ArcNode{
    int ANIdx;
    VertexData_Type AVD;
    ArcWeight_Type AW;
    struct ArcNode *NextAdj;
}ArcNode_Type, *ArcNodePtr_Type; 

typedef ArcNode_Type datatype;
