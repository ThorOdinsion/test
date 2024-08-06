/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/8/23
description:ʹ���ڽӱ�ʵ��ͼ�����ݽṹ
			ʹ���˿��Ŷ�ַ�Ĺ�ϣ��
********************************************/

#include "AdjacencyList.h"
#include <cstdlib>
#include <iostream>


/*��ʼ��ͼ*/
Graph intializeGraph(int VertexNum)
{
	return initializeTable(VertexNum);
}

/*���붥�㣬ֱ�ӵ��ù�ϣ��Ĳ����ֵ*/
void insertVertex(VertexType vertex, Graph G)
{
	insertKey(vertex, G);
	G->vertex++;
}

void insertEdgeWithIndex(Index P1, Index P2, WeightType weight, Graph G)
{
	/*�����µı�*/
	Edge newEdge = (Edge)malloc(sizeof(EdgeNode));
	newEdge->vertexIndex = P2;
	newEdge->weight = weight;
	newEdge->next = G->TheCells[P1].next;
	G->TheCells[P1].next = newEdge;
	/*������һ*/
	G->edge++;
}

/*����ͼ����ߣ����ò��������*/
void insertEdgeNoDirect(VertexType vertex1, VertexType vertex2, WeightType weight, Graph G)
{
	insertEdge(vertex1, vertex2, weight, G);
	insertEdge(vertex2, vertex1, weight, G);
}

/*����ߣ���Ҫ�Ƚ����жϱߵ����������Ƿ���ڣ����������Ȳ��붥��*/
void insertEdge(VertexType vertex1, VertexType vertex2, WeightType weight, Graph G)
{
	Position P1, P2;
	P1 = FindKey(vertex1, G);

	/*��Ҫ�Ȳ��붥��1�������ж϶���2����ţ�
	ԭ�д�����ͬʱѰַ�����Ѱַ����ͬһ��λ�á�
	�����Ķ��㶥�����Ȳ���Ķ���*/

	if(G->TheCells[P1].Info != Legitimate)
		insertVertex(vertex1, G);

	P2 = FindKey(vertex2, G);
	if(G->TheCells[P2].Info != Legitimate)
		insertVertex(vertex2, G);
	
	insertEdgeWithIndex(P1, P2, weight, G);
}

/*Ѱ�Ҷ�������*/
Position findVertex(VertexType vertex, Graph G)
{
	return FindKey(vertex, G);
}

void removeEdgeWithIndexNoDirect(Index P1, Index P2, Graph G)
{
	removeEdgeWithIndex(P1, P2, G);
	removeEdgeWithIndex(P2, P1, G);
}

void removeEdgeWithIndex(Index P1, Index P2, Graph G)
{
	VertexNode * V = &G->TheCells[P1];

	Edge parent = V->next;

	/*�жϸñ��Ƿ��ǵ�һ����*/
	if(parent->vertexIndex == P2)
	{
		V->next = parent->next;
		free(parent);
	}
	else
	{
		Edge temp;

		while(parent->next->vertexIndex != P2)
			parent = parent->next;

		temp = parent->next;
		parent->next = temp->next;
		free(temp);
	}
}

/*����ͼ�Ƴ��ߣ������Ƴ�������*/
void removeEdgeNoDirect(VertexType vertex1, VertexType vertex2, Graph G)
{
	removeEdge(vertex1, vertex2, G);
	removeEdge(vertex2, vertex1, G);
}

/*�Ƴ��ߣ���ȷ�϶������*/
void removeEdge(VertexType vertex1, VertexType vertex2, Graph G)
{
	Position P1, P2;
	P1 = FindKey(vertex1, G);
	P2 = FindKey(vertex2, G);
	
	if(G->TheCells[P2].Info != Legitimate && G->TheCells[P1].Info == Legitimate)
	{
		fprintf(stderr, "Edge not exist\n");
		return;
	}

	removeEdgeWithIndex(P1, P2, G);

}

/*ɾ����*/
void DestroyEdge(Edge E)
{
	Edge temp;	
	while(E != NULL)
	{
		temp = E->next;
		free(E);
		E = temp;
	}
}

/*ɾ��ͼ����Ҫ��ɾ���ߣ��ٵ���ɾ����ϣ��*/
void  DestroyGraph(Graph G)
{
	for(int i =0; i<G->TableSize; i++)
		if(G->TheCells[i].Info == Legitimate &&G->TheCells[i].next != NULL)
			DestroyEdge(G->TheCells[i].next);

	DestroyTable(G);
}




/*��ӡ��*/
void PrintEdge(VertexNode * V, Graph G)
{
	Edge edgeNext;
	edgeNext = V->next;
	while(edgeNext != NULL)
	{
		printf("Edge: %s -->  ", V->vertexName);
		Index P2 = edgeNext->vertexIndex;
		printf("%s  ",G->TheCells[P2].vertexName);
		printf("weight: %d\n",edgeNext->weight);
		edgeNext = edgeNext->next;
	}
}

/*��ӡͼ*/
void PrintGraph(Graph G)
{
	for(int i =0; i<G->TableSize; i++)
		if(G->TheCells[i].Info == Legitimate)
			PrintEdge(&G->TheCells[i], G);
}

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

/*��ӡ���·��,�Ӻ���*/
void PrintEveryPath(Index S, Index D, Table T, Graph G)
{
	if(D != S)
	{
		Index pre = T[D].path;
		PrintEveryPath(S, T[D].path, T, G);
		printf(" -- %d --> %s",T[D].dist - T[pre].dist, G->TheCells[D].vertexName);
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
			printf("%s -- %d --> %s:\n", G->TheCells[S].vertexName, T[D].dist, G->TheCells[D].vertexName);
			PrintEveryPath(S, D, T, G);
		}
		else
			printf("%s -- %d --> %s", G->TheCells[S].vertexName, T[D].dist, G->TheCells[D].vertexName);

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

void PrintTable(Table T, Graph G)
{
	printf("vertex  dv   pv\n");
	for(int i=0; i<G->vertex; i++)
	{
		printf("%s   %d   %s",G->TheCells[i].vertexName, T[i].dist, G->TheCells[T[i].path].vertexName);
		printf("\n");
	}
}



