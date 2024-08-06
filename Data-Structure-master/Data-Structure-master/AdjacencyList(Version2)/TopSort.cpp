/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/8/23
description:�����������ȡ�������
			��ӡ����������ӡ��������
********************************************/

#include "AdjacencyList.h"
#include "queue.h"
#include <iostream>
#include <cstdlib>


/*��ȡ�����*/
Indegree getIndegree(Graph G)
{
	int num = G->vertex;
	Indegree indegree;
	int count=0;

	indegree = (Indegree)calloc(num, sizeof(int));
	for(int i=0; i<G->TableSize; i++)
	{
		if(G->TheCells[i].Info == Legitimate)
		{
			Edge edge = G->TheCells[i].next;
			while(edge != NULL)
			{
				indegree[edge->vertexIndex]++;
				edge = edge->next;
			}
		}
	}
	return indegree;
}


/*��������*/
int* TopSort(Graph G, Indegree D)
{
	Queue Q;
	Q = createQueue();
	int num = G->vertex;
	int * TopNum = (int *)calloc(G->vertex, sizeof(int));


	if(TopNum == NULL)
	{
		fprintf(stderr, "not enough memory\n");
		exit(1);
	}

	for(int i=0; i<num; i++)
	{
		if(D[i] == 0)
			enqueue(i, Q);
	}



	int count =0;
	Index V;

	while(!isEmpty(Q))
	{
		 V = dequeue(Q);
		 TopNum[count++] = V;

		 Edge edge = G->TheCells[V].next;
		 while(edge != NULL)
		 {
			 if( --D[edge->vertexIndex] == 0)
				 enqueue(edge->vertexIndex, Q);
			 edge = edge->next;
		 }
	}

	/*ɾ������*/
	disposeQueue(Q);

	if(count != num)
	{
		fprintf(stderr,"Graph has a cycle\n");
		free(TopNum);
		return NULL;
	}
	return TopNum;
}

/*��ӡ�����*/
void PrintIndegree(Indegree D, Graph G)
{
	int total = G->vertex;

	Index P;
	for(int i=0; i<total; i++)
	{
		printf("%s indegree:  ", G->TheCells[i].vertexName);
		printf("%d\n",D[i]);
	}
}



/*��ӡ��������˳��*/
void PrintTopSort(int * TopNum, Graph G)
{
	int num = G->vertex;
	Index P;
	if(TopNum == NULL)
	{
		fprintf(stderr,"empty array\n");
		return;
	}

	printf("TopSort :\n");
	for(int i=0; i<num; i++)
	{
		P = TopNum[i];
		printf("%s  ",G->TheCells[P].vertexName);	
	}
	printf("\n");
}