#ifndef BinaryTree
#define BinaryTree

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include "/home/weihuan/C/Datastruct/Stack/Stack.h"

typedef void CALLBACK(datatype);
typedef bool PREDICATE(BiTree);
typedef bool PREDICATE_VALUE(BiTree,datatype);

extern void Init_BT(BiTree *root);
extern void Destroy_BT(BiTree root);
extern void Clear_BT(BiTree root);
extern bool is_Complt_BT_Data(const datatype *data,int *length);
extern bool Arrange_Complt_BT(BiTree *root,const datatype *data,const int length,int *i);
extern bool Creat_Complt_BT(BiTree root,const datatype *data);
extern bool Creat_Common_BT(BiTree root,const datatype *data,int *i);
extern bool is_BT_Empty(BiTree root);
extern bool is_Node_Leaf(BiTree root,const datatype data);
extern bool Add_Node_LChild(BiTree root,const datatype data,const datatype add_data);
extern bool Add_Node_RChild(BiTree root,const datatype data,const datatype add_data);
extern bool Del_Node(BiTree root,const datatype data);
extern bool Del_Node_LChild(BiTree root,const datatype data);
extern bool Del_Node_RChild(BiTree root,const datatype data);
extern void DLR_Traverse_BT(BiTree root,CALLBACK visit);
extern void DLR_Traverse_BT_IF(BiTree root,CALLBACK visit,PREDICATE judge);
extern void DLR_Traverse_BT_Stack(BiTree root,CALLBACK visit);
extern void LDR_Traverse_BT(BiTree root,CALLBACK visit);
extern void LDR_Traverse_BT_IF(BiTree root,CALLBACK visit,PREDICATE judge);
extern void LDR_Traverse_BT_Stack(BiTree root,CALLBACK visit);
extern void LRD_Traverse_BT(BiTree root,CALLBACK visit);
extern void LRD_Traverse_BT_IF(BiTree root,CALLBACK visit,PREDICATE judge);
extern void LRD_Traverse_BT_Stack(BiTree root,CALLBACK visit);
extern bool IF_LEAF(BiTree root);
extern bool IF_DATA(BiTree root,const datatype data);
extern bool Get_Node(BiTree root,const datatype data,BiTree *getnode);
extern bool Get_Node_Parent(BiTree root,const datatype data,BiTree *getnode);
extern bool Get_Node_LChild(BiTree root,const datatype data,BiTree *getnode);
extern bool Get_Node_RChild(BiTree root,const datatype data,BiTree *getnode);
extern int Get_Height(BiTree root);
extern void Count_Node(BiTree root,int* count);
extern void Get_BT_from_Traverse(BiTree root);
#endif