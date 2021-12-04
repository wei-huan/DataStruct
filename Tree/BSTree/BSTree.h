#ifndef BINARY_SORT_TREE
#define BINARY_SORT_TREE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include "BSTreeNode.h"

typedef void CALLBACK(datatype);
typedef bool PREDICATE(BSTree);
typedef bool PREDICATE_VALUE(BSTree,datatype);

void Destroy_BST(BSTree root);
void Clear_BST(BSTree root);
BSTree Creat_BST();
bool is_BST_Empty(BSTree root);
bool is_Node_Leaf(BSTree root,const datatype data);
bool Add_Node_LChild(BSTree root,const datatype data,const datatype add_data);
bool Add_Node_RChild(BSTree root,const datatype data,const datatype add_data);
bool Del_Node(BSTree root,const datatype data);
bool Del_Node_LChild(BSTree root,const datatype data);
bool Del_Node_RChild(BSTree root,const datatype data);
void DLR_Traverse_BST(BSTree root,CALLBACK visit);
void DLR_Traverse_BST_IF(BSTree root,CALLBACK visit,PREDICATE judge);
void DLR_Traverse_BST_Stack(BSTree root,CALLBACK visit);
void LDR_Traverse_BST(BSTree root,CALLBACK visit);
void LDR_Traverse_BST_IF(BSTree root,CALLBACK visit,PREDICATE judge);
void LDR_Traverse_BST_Stack(BSTree root,CALLBACK visit);
void LRD_Traverse_BST(BSTree root,CALLBACK visit);
void LRD_Traverse_BST_IF(BSTree root,CALLBACK visit,PREDICATE judge);
void LRD_Traverse_BST_Stack(BSTree root,CALLBACK visit);
bool IF_LEAF(BSTree root);
bool IF_DATA(BSTree root,const datatype data);
bool Get_Node(BSTree root,const datatype data,BSTree *getnode);
bool Get_Node_Parent(BSTree root,const datatype data,BSTree *getnode);
bool Get_Node_LChild(BSTree root,const datatype data,BSTree *getnode);
bool Get_Node_RChild(BSTree root,const datatype data,BSTree *getnode);
int Get_Height(BSTree root);
void Count_Node(BSTree root,int* count);

#endif /*BINARY_SORT_TREE*/
