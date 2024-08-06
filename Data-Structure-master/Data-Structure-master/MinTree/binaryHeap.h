/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/8/27
description:Ϊ��dijkstra�㷨�޸ĵĶ����
********************************************/
#include "AdjacencyList.h"




#ifndef _BINARY_HEAP
#define _BINARY_HEAP


#define NotAVertex -1

struct AdjvexPath;
struct HeapStruct;
typedef HeapStruct * PriorityQueue;
typedef struct AdjvexPath Adjvex;


PriorityQueue Initialize(int MaxElements);
void Destory(PriorityQueue H);
void makeEmpty(PriorityQueue H);
void Insert(Adjvex X, PriorityQueue H);
Adjvex DeleteMin(PriorityQueue H);
Adjvex FindMin(PriorityQueue H);
int isEmpty(PriorityQueue H);
int isFull(PriorityQueue H);
PriorityQueue BuildHeap(Adjvex *x, int n);
void PercolateUp(PriorityQueue H, int hole);
void PercolateDown(PriorityQueue H, int hole);

/*Ϊ��ʹ��Kruskal�㷨�����һ�����㣬����ʵ�����Ǳ�ʾһ����
������֮ǰ��д��Dijkstra�㷨���ּ���,�����һ��Ԫ��ʵ����ֻ

��Ҫ���һ����ʼ����䣨�����������û�£����������ֽṹ���Զ���ֵ*/
struct AdjvexPath
{
	Index vertex;
	Index adjvex;
	WeightType cost;
};

/*��ӡ����ѣ����õݹ��ӡ�������������������*/
void printBHeap(PriorityQueue H, int depth, int Index);
#endif

struct HeapStruct
{
	int capacity;
	int size;
	Adjvex * Elements;
};


