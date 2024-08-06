/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/10/10
description:Treap��
********************************************/
#ifndef _TREAP_H
#define _TREAP_H

#define Infinity 0x7fffffff

struct TreapNode;
typedef struct TreapNode* TreapTree;
typedef struct TreapNode* Position;
typedef int ElementType;

struct TreapNode
{
	ElementType Element;
	TreapTree left;
	TreapTree right;
	int Priority;
};

/*��ʼ��*/
TreapTree initialize();

/*����*/
TreapTree insert(ElementType item, TreapTree T);

/*ɾ��*/
TreapTree remove(ElementType item, TreapTree T);

/*����ת*/
TreapTree rightSingleRotate(TreapTree T);

/*����ת*/
TreapTree leftSingleRotate(TreapTree k1);

/*��ӡ��*/
void PrintTree(TreapTree T, int depth);
#endif