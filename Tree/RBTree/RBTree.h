#ifndef RB_TREE_H
#define RB_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include "RBTreeNode.h"

typedef void CALLBACK(RBNode);
typedef bool PREDICATE(RBTree);
typedef bool PREDICATE_VALUE(RBTree, datatype);

extern const char red[4];
extern const char black[6];

void Creat_RBT(RBTree* root);
void Rotate_Left(RBTree* root, RBNode* node_f, RBNode* node_s);
void Rotate_Right(RBTree* root, RBNode* node_s, RBNode* node_f);
void Swap(RBNode* node1, RBNode* node2);
void Add_Node(RBTree* root, const datatype data);
void Destroy_RBT(RBTree root);
bool is_RBT_Empty(RBTree root);
bool is_Node_Leaf(RBTree root, const datatype data);
bool Del_Node(RBTree* root, const datatype data);
void DLR_Traverse_RBT(RBTree root, CALLBACK visit);
void DLR_Traverse_RBT_IF(RBTree root, CALLBACK visit, PREDICATE judge);
void LDR_Traverse_RBT(RBTree root, CALLBACK visit);
void LDR_Traverse_RBT_IF(RBTree root, CALLBACK visit, PREDICATE judge);
void LRD_Traverse_RBT(RBTree root, CALLBACK visit);
void LRD_Traverse_RBT_IF(RBTree root, CALLBACK visit, PREDICATE judge);
bool IF_LEAF(RBTree root);
bool IF_DATA(RBTree root, const datatype data);
bool Get_Node(RBTree root, const datatype data,RBTree *getnode);
bool Get_Node_Parent(RBTree root, const datatype data, RBTree *getnode);
bool Get_Node_LChild(RBTree root, const datatype data, RBTree *getnode);
bool Get_Node_RChild(RBTree root, const datatype data, RBTree *getnode);
int Get_Height(RBTree root);
void Count_Node(RBTree root, int* count);

#endif /*RB_TREE_H*/
