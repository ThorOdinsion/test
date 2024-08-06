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
#include "queue.h"

/*��ʼ��ͼ*/
Graph intializeGraph(int VertexNum)
{
	return initializeTable(VertexNum*4);
}

/*���붥�㣬ֱ�ӵ��ù�ϣ��Ĳ����ֵ*/
void insertVertex(VertexType vertex, Graph G)
{
	insertKey(vertex, G);
	G->vertex++;
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

	
	/*�����µı�*/
	Edge newEdge = (Edge)malloc(sizeof(EdgeNode));
	newEdge->vertexIndex = P2;
	newEdge->weight = weight;
	newEdge->next = G->TheCells[P1].next;
	G->TheCells[P1].next = newEdge;
	/*������һ*/
	G->edge++;
}

/*Ѱ�Ҷ�������*/
Position findVertex(VertexType vertex, Graph G)
{
	return FindKey(vertex, G);
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

/*Ѱ��ĩβ����ΪP�ı��Ƿ����*/
bool findEdge(VertexNode * V, Index P)
{
	if(V->next == NULL)
		return false;

	Edge edge = V->next;
	while(edge != NULL)
	{
		if(edge->vertexIndex == P)
			return true;

		edge = edge->next;
	}

	return false;
	
}

/*����ÿ������������*/
void countIn(int num, Indegree D,  Graph G)
{
	int total = G->vertex;
	Index P = D[num].vertexIndex;

	for(int i=0; i<total; i++)
	{
		Index temp = D[i].vertexIndex;
		if(temp != P)
		{
			/*����ö�����һ��ָ�����󶥵�ıߣ�����ȼ�һ*/
			if(findEdge(&G->TheCells[temp], P))
				D[num].indegreenum++;
		}
	}
}

/*��ȡ�����*/
Indegree getIndegree(Graph G)
{
	int num = G->vertex;
	Indegree indegree;
	int count=0;

	indegree = (Indegree)calloc(num, sizeof(IndegreeNode));
	for(int i=0; i<G->TableSize; i++)
		if(G->TheCells[i].Info == Legitimate)
			indegree[count++].vertexIndex = i;

	for(int i=0; i<num; i++)
		countIn(i, indegree, G);

	return indegree;
}

/*����ָ���������е���ȣ����ظö���ʣ�µ����ֵ*/
int decreaseDegree(Index P, Indegree D, int total)
{
	for(int i=0; i<total; i++)
		if(D[i].vertexIndex == P)
			return --D[i].indegreenum;
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
		if(D[i].indegreenum == 0)
			enqueue(D[i].vertexIndex, Q);
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
			 if(decreaseDegree(edge->vertexIndex, D, num) == 0)
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
void PrintIndegree(Indegree D, Graph G, int total)
{
	Index P;
	for(int i=0; i<total; i++)
	{
		P = D[i].vertexIndex;
		printf("%s indegree:  ", G->TheCells[P].vertexName);
		printf("%d\n",D[i].indegreenum);
	}
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

void PrintTopSort(int * TopNum, Graph G)
{
	int num = G->vertex;
	Index P;

	printf("TopSort :\n");
	for(int i=0; i<num; i++)
	{
		P = TopNum[i];
		printf("%s  ",G->TheCells[P].vertexName);	
	}
	printf("\n");
}