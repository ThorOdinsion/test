/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/8/30
description:������ͼ��ȡ��С������
********************************************/

#include "AdjacencyList.h"
#include <cstdlib>
#include "binaryHeap.h"
#include <iostream>
#include "DisjSet.h"




/*��С��������Prim�㷨,Ҫ������ͼ����ͨ��*/
void minTreePrim(Table T, Graph G)
{
	Index S = 0;
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
				if(T[W].dist > edge->weight)
				{
					T[W].dist = edge->weight;
					T[W].path = V;
					temp.cost = T[W].dist;
					temp.vertex = W;
					Insert(temp, H);
				}
			}

			edge = edge->next;
		}/*while*/
	}

	Destory(H);

}


/*��С��������Prim�㷨,Ҫ������ͼ����ͨ��*/
Table minTreePrim(Graph G)
{
	Index S = 0;

	/*�����б�*/
	Table T = (Table)calloc(G->vertex, sizeof(TableNode));
	if(T == NULL)
	{
		fprintf(stderr, "not enough memory");
		return NULL;
	}

	initTable(S, G->vertex, T);
	minTreePrim(T, G);
	return T;
}



Adjvex * setEdgeArray(Graph G)
{
	Adjvex * arr = (Adjvex *)malloc(G->edge * sizeof(Adjvex));
	for(int i=0, j=0; i< G->vertex; i++)
	{
		Edge edge = G->TheCells[i].next;
		while(edge != NULL)
		{
			arr[j].adjvex = edge->vertexIndex;
			arr[j].vertex = i;
			arr[j].cost = edge->weight;
			edge = edge->next;
			j++;
		}
	}
	return arr;
}

/*��С��������Kruskal�㷨,Ҫ������ͼ����ͨ��*/
void minTreeKruskal(DisjSet S, PriorityQueue H, Table T, int num)
{
	int count=0;
	Adjvex temp;
	while(count < num -1)
	{
		 temp = DeleteMin(H);
		 /*����һ��������*/
		 if(Find(temp.adjvex, S) != Find(temp.vertex, S))
		 {
			 SetUnion(S, Find(temp.adjvex, S), Find(temp.vertex, S));
			 ++count; 

			 if(T[temp.vertex].known == false)
			 {
				 T[temp.vertex].known == true;
				 T[temp.vertex].path = temp.adjvex;
				 T[temp.vertex].dist = temp.cost;
			 }
			 else
			 {
				 T[temp.adjvex].known == true;
				 T[temp.adjvex].path = temp.vertex;
				 T[temp.adjvex].dist = temp.cost;
			 }
		 }

	}
}

/*��С��������Kruskal�㷨,Ҫ������ͼ����ͨ��*/
Table minTreeKruskal(Graph G)
{
	DisjSet S;
	initialize(S);
	
	Adjvex * edges = setEdgeArray(G);
	PriorityQueue H = BuildHeap(edges, G->edge);

	/*�����б�*/
	Table T = (Table)calloc(G->vertex, sizeof(TableNode));
	if(T == NULL)
	{
		fprintf(stderr, "not enough memory");
		return NULL;
	}

	initTable(0, G->vertex, T);

	minTreeKruskal(S, H, T, G->vertex);

	return T;
}