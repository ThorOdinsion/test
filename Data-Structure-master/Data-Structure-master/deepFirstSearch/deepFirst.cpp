/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/9/15
description:�����������
			˫��ͨ�ԣ�����
			ŷ����·
********************************************/
#include "AdjacencyList.h"
#include <stdlib.h>
#include <iostream>;
#include "list.h"


#define Min(x,y) ((x)<(y)?(x):(y))

void Dfs(Index S, Table T, Graph G);

Table deepFirstSearch(Graph G, VertexType start)
{
	Index P1;
	P1 = FindKey(start, G);
	if(G->TheCells[P1].Info != Legitimate)
		return NULL;

	Table T = (Table)malloc(G->vertex * sizeof(struct TableNode));
	initTable(P1, G->vertex, T);

	Dfs(P1, T, G);
	return T;
}

void Dfs(Index S, Table T, Graph G)
{
	Index adj;
	Edge edge = G->TheCells[S].next;
	T[S].known = true;
	while(edge != NULL)
	{
		adj = edge->vertexIndex;
		if(!T[adj].known)
		{
			T[adj].path = S;
			T[adj].dist = edge->weight;
			Dfs(adj, T, G);
		}
		edge = edge->next;
	}
}


struct ArtNode
{
	bool known;
	int parent;
	int Low;
	int Num;
};

void FindArt(Index S, Graph G, struct ArtNode * Art, int * countPos);

void FindArticulation(VertexType S, Graph G)
{
	Index P1;
	P1 = FindKey(S, G);
	if(G->TheCells[P1].Info != Legitimate)
		return;

	int count =1;
	struct ArtNode * Art= (struct ArtNode *)calloc(G->vertex, sizeof(struct ArtNode));
	FindArt(P1, G, Art, &count);

	free(Art);
}

void FindArt(Index S, Graph G, struct ArtNode * Art, int * countPos)
{
	Index W;
	int rootchild =0;

	Art[S].known = true;
	Art[S].Low = Art[S].Num = (*countPos)++;

	Edge edge = G->TheCells[S].next;
	while(edge != NULL)
	{
		W = edge->vertexIndex;
		/*�����*/
		if(!Art[W].known)
		{
			if(Art[S].Num ==1)
			{
				rootchild++;
				if(rootchild >1)
					printf("%s is a articulation point\n", G->TheCells[S].vertexName);
			}

			Art[W].parent = S;
			FindArt(W, G, Art, countPos);
			/*�����*/

			/*�����������������������Ҫ�ų�*/
			if(Art[W].Low >= Art[S].Num && Art[S].Num !=1)
				printf("%s is a articulation point\n", G->TheCells[S].vertexName);

			Art[S].Low = Min(Art[W].Low, Art[S].Low);
		}
		else if(Art[S].parent != W)
			Art[S].Low = Min(Art[W].Num, Art[S].Low);
		edge = edge->next;
	}

}

void eulerDfs(Index S, List L, Graph G, List inserPos);





List eulerCircuit(VertexType start, Graph G)
{

	Index P1;
	P1 = FindKey(start, G);
	if(G->TheCells[P1].Info != Legitimate)
		return NULL;
		
	List inserPos = (List)malloc(sizeof(struct ListNode));
	inserPos->Next = NULL;
	inserPos->Element =-1;

	List Head = (List)malloc(sizeof(struct ListNode));

	Head->Next = NULL;

	insert(P1, Head);
	eulerDfs(P1, Head->Next, G, inserPos);

	while(inserPos->Element != -1)
	{
		eulerDfs(inserPos->Element, inserPos->Next, G, inserPos);	
	}
	free(inserPos);
	return Head;
}

void eulerDfs(Index S, List L, Graph G, List inserPos)
{
	Index adj;
	Edge edge = G->TheCells[S].next;

	if(edge != NULL)
	{
		adj = edge->vertexIndex;
		insert(adj, L);

		removeEdgeWithIndexNoDirect(S, adj, G);

		if(G->TheCells[S].next != NULL)
		{
			inserPos->Element = S;
			inserPos->Next = L;
		}
		else if(S == inserPos->Element)
			inserPos->Element =-1;

		/*����ֻ����һ������ʱ�򣬷��ʽ����ڳ�ʼ���㣬����������¼*/
		if(G->TheCells[adj].next == NULL && adj == inserPos->Element)
			inserPos->Element =-1;

		eulerDfs(adj, L->Next, G, inserPos);
	}
}

