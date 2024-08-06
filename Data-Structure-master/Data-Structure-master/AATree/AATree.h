/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/10/9
description:AA��
********************************************/
#ifndef _AATREE_H
#define _AATREE_H

struct AANode;
typedef struct AANode* AATree;
typedef struct AANode* Position;
typedef int ElementType;

struct AANode
{
	ElementType Element;
	AATree left;
	AATree right;
	int level;
};

/*��ʼ��*/
AATree initialize();

/*ȥ����������ڵ�ͬ�߶�*/
AATree skew(AATree T);

/*ȥ�������������Һ캢��*/
AATree split(AATree T);

/*����ת*/
AATree insert(ElementType item, AATree T);

/*����ת*/
AATree remove(ElementType item, AATree T);

/*����ת*/
AATree rightSingleRotate(AATree T);

/*����ת*/
AATree leftSingleRotate(AATree k1);

/*��ӡ��*/
void PrintTree(AATree T, int K);
#endif