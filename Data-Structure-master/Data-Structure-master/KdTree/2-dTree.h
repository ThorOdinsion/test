/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/10/10
description:2-d��
********************************************/
#ifndef _2DTREE_H
#define _2DTREE_H

#define Infinity 0x7fffffff

struct KdNode;
typedef struct KdNode* KdTree;
typedef struct KdNode* Position;
typedef int  ElementType[2];



struct KdNode
{
	ElementType Element;
	KdTree left;
	KdTree right;
	int Priority;
};

/*��ʼ��*/
KdTree initialize();


KdTree insert(ElementType item, KdTree T);
KdTree insert(ElementType item, KdTree T, int level);

/*��ӡ��Χ*/
void PrintRange(ElementType Low, ElementType High , KdTree T);
static void RecPrintRange(ElementType Low, ElementType High , KdTree T, int level);

/*��ӡ��*/
void PrintTree(KdTree T, int depth);
#endif