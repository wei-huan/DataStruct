#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include "AVLTreeNode.h"

typedef void CALLBACK(AVLNode);
typedef bool PREDICATE(AVLTree);
typedef bool PREDICATE_VALUE(AVLTree, datatype);

void Creat_AVLT(AVLTree* root);
void Rotate_Left(AVLTree* root, AVLNode* node_f, AVLNode* node_s);
void Rotate_Right(AVLTree* root, AVLNode* node_s, AVLNode* node_f);
void Add_Node(AVLTree* root, const datatype data);
void Destroy_AVLT(AVLTree root);
bool is_AVLT_Empty(AVLTree root);
bool is_Node_Leaf(AVLTree root, const datatype data);
bool Del_Node(AVLTree* root, const datatype data);
void DLR_Traverse_AVLT(AVLTree root, CALLBACK visit);
void DLR_Traverse_AVLT_IF(AVLTree root, CALLBACK visit, PREDICATE judge);
void LDR_Traverse_AVLT(AVLTree root, CALLBACK visit);
void LDR_Traverse_AVLT_IF(AVLTree root, CALLBACK visit, PREDICATE judge);
void LRD_Traverse_AVLT(AVLTree root, CALLBACK visit);
void LRD_Traverse_AVLT_IF(AVLTree root, CALLBACK visit, PREDICATE judge);
bool IF_LEAF(AVLTree root);
bool IF_DATA(AVLTree root, const datatype data);
bool Get_Node(AVLTree root, const datatype data,AVLNode** getnode);
bool Get_Node_Parent(AVLTree root, const datatype data, AVLTree *getnode);
bool Get_Node_LChild(AVLTree root, const datatype data, AVLTree *getnode);
bool Get_Node_RChild(AVLTree root, const datatype data, AVLTree *getnode);
int Get_Height(AVLTree root);
void Count_Node(AVLTree root, int* count);

#endif /*AVL_TREE*/
