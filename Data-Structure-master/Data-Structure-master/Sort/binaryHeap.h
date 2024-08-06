/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/8/3
description:�����
********************************************/
#ifndef _BINARY_HEAP
#define _BINARY_HEAP

struct HeapStruct;
typedef HeapStruct * PriorityQueue;
typedef int ElementType;


PriorityQueue Initialize(int MaxElements);
void Destroy(PriorityQueue H);
void makeEmpty(PriorityQueue H);
void Insert(ElementType X, PriorityQueue H);
ElementType DeleteMin(PriorityQueue H);
ElementType FindMin(PriorityQueue H);
int isEmpty(PriorityQueue H);
int isFull(PriorityQueue H);
PriorityQueue BuildHeap(ElementType *x, int n);
void PercolateUp(PriorityQueue H, int hole);
void PercolateDown(PriorityQueue H, int hole);


/*��ӡ����ѣ����õݹ��ӡ�������������������*/
void printBHeap(PriorityQueue H, int depth, int Index);
#endif

struct HeapStruct
{
	int capacity;
	int size;
	ElementType * Elements;
};


