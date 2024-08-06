/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/8/27
description:���·���㷨��
			��Ȩ���·��
			Dijstra�㷨
			��ӡ��Ȩ·��
********************************************/
#include "AdjacencyList.h"
#include "queue.h"
#include <cstdlib>
#include <iostream>
#include "binaryHeap.h"


/*�����Ȩ·��,��ʼ��·����*/
void initTable(Index V, int num, Table T)
{
	for(int i=0; i<num; i++)
	{
		T[i].known = false;
		T[i].dist = Infinity;
		T[i].path = -1;
	}
	T[V].dist = 0;
}

/*�����Ȩ·��,����·��*/
void unweighted(Index S, Table T, Graph G)
{
	Queue Q = createQueue();
	enqueue(S, Q);
	Index V,W;


	while(!isEmpty(Q))
	{
		V = dequeue(Q);
		T[V].known = true;

		Edge edge = G->TheCells[V].next;
		while(edge !=NULL)
		{
			W = edge->vertexIndex;
			if(T[W].dist == Infinity)
			{
				T[W].dist = T[V].dist+1;
				T[W].path = V;
				enqueue(W,Q);
			}
			edge = edge->next;
		}
	}
	disposeQueue(Q);
}

/*�����Ȩ·��*/
Table UnweightedShortestPath(VertexType vertex, Graph G)
{
	Index S = findVertex(vertex, G);
	if(G->TheCells[S].Info != Legitimate)
	{
		fprintf(stderr, "vertex %s does not exist", vertex);
		return NULL;
	}

	/*�����б�*/
	Table T = (Table)calloc(G->vertex, sizeof(TableNode));
	if(T == NULL)
	{
		fprintf(stderr, "not enough memory");
		return NULL;
	}

	initTable(S, G->vertex, T);
	
	unweighted(S, T, G);
	return T;
}



/*��ӡ���·��,�Ӻ���*/
void PrintEveryPath(Index S, Index D, Table T, Graph G)
{
	if(D != S)
	{
		Index pre = T[D].path;
		PrintEveryPath(S, T[D].path, T, G);
		printf(" --%d--> %s",T[D].dist - T[pre].dist, G->TheCells[D].vertexName);
	}
	else
		printf("%s",G->TheCells[S].vertexName);
}

/*��ӡ���·��,�Ӻ���*/
void PrintPath(Index S, Index D, Table T, Graph G)
{
	if(T[D].dist != Infinity)
	{
		if(D != S)
		{
			printf("%s --%d--> %s:\n", G->TheCells[S].vertexName, T[D].dist, G->TheCells[D].vertexName);
			PrintEveryPath(S, D, T, G);
		}
		else
			printf("%s --%d--> %s", G->TheCells[S].vertexName, T[D].dist, G->TheCells[D].vertexName);

		printf("\n\n");
	}
	else
		printf("%s --Infinity--> %s:\n", G->TheCells[S].vertexName, G->TheCells[D].vertexName);
}

/*��ӡ���·��*/
void PrintWeighted(Table T, Graph G)
{
	int num = G->vertex;
	Index S, W;
	for(int i=0; i<num; i++)
		if(T[i].dist == 0)
		{
			S = i;
			break;
		}

	for(int i=0; i<num; i++)
		PrintPath(S, i, T, G);

}


void Dijkstra(Index S, Table T, Graph G)
{
	Index V,W;
	PriorityQueue H = Initialize(G->edge);

	struct AdjvexPath temp;
	temp.cost =0;
	temp.vertex = S;
	Insert(temp, H);

	while(!isEmpty(H))
	{		
		while(1)
		{
			temp = DeleteMin(H);
			V = temp.vertex;
			if(!T[V].known)
				break;

			if(isEmpty(H))
				break;
		}
		if(V == NotAVertex)
			break;

		T[V].known = true;

		Edge edge = G->TheCells[V].next;

		while(edge !=NULL)
		{
			W = edge->vertexIndex;
			if(!T[W].known)
			{
				if(T[W].dist > T[V].dist +edge->weight)
				{
					T[W].dist = T[V].dist +edge->weight;
					T[W].path = V;
					temp.cost = T[W].dist;
					temp.vertex = W;
					Insert(temp, H);
				}
			}

			edge = edge->next;
		}/*while*/
	}

}


/*�����Ȩ·��,Dijkstra�㷨*/
Table Dijkstra(VertexType vertex, Graph G)
{
	Index S = findVertex(vertex, G);
	if(G->TheCells[S].Info != Legitimate)
	{
		fprintf(stderr, "vertex %s does not exist", vertex);
		return NULL;
	}

	/*�����б�*/
	Table T = (Table)calloc(G->vertex, sizeof(TableNode));
	if(T == NULL)
	{
		fprintf(stderr, "not enough memory");
		return NULL;
	}

	initTable(S, G->vertex, T);
	Dijkstra(S, T, G);
	return T;
}