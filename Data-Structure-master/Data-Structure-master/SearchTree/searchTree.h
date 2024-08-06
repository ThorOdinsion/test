/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/7/20
description:���������
********************************************/


#ifndef _SEARCHTREE_H
#define _SEARCHTREE_H

struct TreeNode;
typedef struct TreeNode * Position;
typedef Position SearchTree;

typedef int ElementType;


SearchTree MakeEmpty(SearchTree T);
Position Find(ElementType X, SearchTree T);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
SearchTree Insert(ElementType X, SearchTree T);
SearchTree Delete(ElementType X, SearchTree T);
ElementType Retrieve(Position P);

/*������Ľṹ��������ڵ�ĸ߶�*/
void PrintTree(SearchTree T, int depth);
void PrintTree(SearchTree T);
void PrintDepth(ElementType A, int depth);

struct TreeNode
{
	ElementType Element;
	SearchTree lchild;
	SearchTree rchild;
};
#endif

