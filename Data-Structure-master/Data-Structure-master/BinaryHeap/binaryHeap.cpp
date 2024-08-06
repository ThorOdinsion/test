/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/8/3
description:�����
********************************************/
#include"binaryHeap.h"
#include <stdlib.h>
#include <iostream>


PriorityQueue Initialize(int MaxElements)
{
	PriorityQueue H;
	if(MaxElements < 10)
	{
		fprintf(stderr,"too small elements\n");
		return NULL;
	}
	H = (PriorityQueue)malloc(sizeof(HeapStruct));
	if(H ==NULL)
	{
		fprintf(stderr,"out of space\n");
		return NULL;
	}
	H->capacity = MaxElements;
	H->size = 0;
	H->Elements = (ElementType *)malloc((MaxElements +1) *sizeof(ElementType));
	if(H ->Elements ==NULL)
	{
		fprintf(stderr,"out of space\n");
		return NULL;
	}
	H->Elements[0] = 0x80000000;
	return H;
}

void Destory(PriorityQueue H)
{
	free(H->Elements);
	free(H);
}

void makeEmpty(PriorityQueue H)
{
	H->size =0;
}

void Insert(ElementType X, PriorityQueue H)
{
	if(isFull(H))
		return;

	int i;
	i= ++ H->size ;
	while(H->Elements[i/2] > X)
	{
		H->Elements[i] = H->Elements[i/2];
		i = i/2;
	}
	H->Elements[i] = X;

}

ElementType DeleteMin(PriorityQueue H)
{
	if(isEmpty(H))
	{
		fprintf(stderr,"Queue is empty\n");
		return H->Elements[0];
	}

	ElementType min = H->Elements[1];
	ElementType last = H->Elements[H->size--];
	if(H->size == 0)
	{
		return min;
	}
	int i, child;
	for(i=1;;i = child)
	{
		/*���ϵĴ���û�м�鵱size=1����0������������ȼ��size�Ƿ�Ϊ1*/
		if(2*i > H->size)
			break;

		child = 2*i;
		/*�ҵ����Һ�������С��һ�������ֻ�����ӣ��Ͳ���Ƚϵڶ���ѡ��*/
		if( child !=H->size && H->Elements[child]>H->Elements[child+1] )
			child++;

		/*���һ��Ԫ�غͽ�С�ĺ��ӱȽϣ�С�ķ��ڿ�Ѩ��*/
		if(last < H->Elements[child])
			break;

		H->Elements[i] = H->Elements[child];
	}
	H->Elements[i] = last;
	return min;

}

ElementType FindMin(PriorityQueue H)
{
	if(isEmpty(H))
	{
		fprintf(stderr,"Queue is empty\n");
		return H->Elements[0];
	}
	return H->Elements[1];
}

int isEmpty(PriorityQueue H)
{
	return H->size ==0;
}

int isFull(PriorityQueue H)
{
	return H->size == H->capacity;
}

void printDapth(ElementType X, int depth)
{
	while(depth >0)
	{
		printf("    ");
		depth--;
	}
	printf("%d\n", X);
}

void printBHeap(PriorityQueue H, int depth, int Index)
{
	if(Index <= H->size)
	{
		printBHeap(H, depth +1, 2*Index);
		printDapth(H->Elements[Index], depth);
		printBHeap(H, depth +1, 2*Index+1);
	}
}