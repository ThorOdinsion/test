/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/7/25
description:���и���ָ��ʵ�ֵ���չ�����Ե�����ʵ����չ
********************************************/
#include "SplayTree.h"
#include <stdlib.h>
#include <iostream>


SplayTree FindMax(SplayTree T);
SplayTree searchValue(ElementType X, SplayTree T);

/*���빦��ʵ�ֵķ�ʽ���ȷǵݹ�Ĳ��룬�ٽ���Splay��������ʵ���ڸ��ӣ������Ż���
�Ƚ���Splay������Ȼ���ٰ���ֵ��Ϊ���ڵ�ͷ��ص����ϲ��Ϳ���*/
SplayTree insert(ElementType X, SplayTree T)
{
	/*����ʱֱ�Ӵ����µ���*/
	if(T == NULL)
	{
		T = (SplayTree)malloc(sizeof(struct SplayNode));
		if(T == NULL)
		{
			fprintf(stderr, "not enough memory");
			exit(1);
		}
		T->Element = X;
		T->Left = T->Right =T->Parent = NULL;
		return T;
	}
	/*XΪ���ڵ�ʱֱ�ӷ���*/
	if(X == T->Element)
		return T;
	/*X��Ϊ���ڵ㣬Ѱ�ҵ�X֮�����Splay����*/
	else
	{
		Position tempP = T;
		Position temp = T;
		while(temp != NULL)
		{
			if(X < temp->Element)
			{
				tempP =temp;
				temp = temp->Left;
			}
			else if(X >temp->Element)
			{
				tempP= temp;
				temp = temp->Right;
			}
			//��ʱX����temp�ĳ�Աֵ
			else
				break;
		}
		/*�ڵ��в�����X*/
		if(temp == NULL)
		{
			Position np= (SplayTree)malloc(sizeof(struct SplayNode));
			if(np == NULL)
			{
				fprintf(stderr, "not enough memory");
				exit(1);
			}
			np->Element = X;
			np->Left = np->Right = NULL;
			np->Parent =tempP;
			if(X<tempP->Element)
				tempP->Left = np;
			else
				tempP->Right = np;

			/*׼���������ڵ�*/
			temp = np;
		}
		T = Splay(temp, T);
	}
	return T;
}

SplayTree Delete(ElementType X, SplayTree T)
{
	if(T == NULL)
	{
		fprintf(stderr, "%d don't exist", X);
	}
	T =Find(X, T);
	/*ҪѰ�ҵ�ֵ�Ѿ���ɸ��ڵ㣬���������ҵ���������򲻴���*/
	if(X == T->Element)
	{
		/*ɾ������ʣ����������L������������R������������ʹ��FindMax����L�����ڵ㣬��ʱ��L�ĸ�û����������ʹR��ΪL�ĸ���������*/
		if(T->Left && T->Right)
		{
			Position Ltemp, Rtemp;
			Ltemp = T->Left;
			Rtemp = T->Right;
			/*���ҽڵ�ĸ��׽ڵ�����ΪNULL*/
			Ltemp->Parent = Rtemp->Parent =NULL;

			free(T);
			Ltemp = FindMax(Ltemp);
			Ltemp->Right = Rtemp;
			Rtemp->Parent = Ltemp;
			return Ltemp;
		}
		else if(T->Left)
		{
			Position Ltemp = T->Left;
			Ltemp ->Parent =NULL;
			free(T);
			return Ltemp;
		}
		else
		{
			Position Rtemp = T->Right;
			Rtemp ->Parent =NULL;
			free(T);
			return Rtemp;
		}
		
	}
	else
	{
		fprintf(stderr, "%d do not exist", X);
		return T;
	}
}

SplayTree Find(ElementType X, SplayTree T)
{
	/*����ֱ�ӷ���*/
	if(T==NULL)
	{
		fprintf(stderr, "empty tree");
		return T;
	}
	Position np = searchValue(X, T);
	/*����֤��󷵻ص�Ԫ�ص���X����Ҫ�����߼�飬��Ϊ���ڵ������splay����*/
	if(np != T)
		 return Splay(np, T);
	/*��Ϊ���ڵ㣬ֱ�ӷ���*/
	else
		return T;

}
SplayTree searchValue(ElementType X, SplayTree T)
{

	/*XС�ڵ�ǰԪ����������ʱ*/
	if(X<T->Element && T->Left)
		return searchValue(X, T->Left);
	/*X���ڵ�ǰԪ�������Һ���ʱ*/
	else if(X >T->Element && T->Right)
		return searchValue(X, T->Right);
	/*X���ڵ�ǰԪ�أ�����û�ҵ���Ԫ�أ���û�����Һ���ʱ*/
	else
		return T;
}

/*�ҵ���Сֵ֮�󽫸�ֵ��Ϊ���ڵ�*/
SplayTree FindMin(SplayTree T)
{
	Position np = T;
	if(T!=NULL)
	{
		while(np->Left !=NULL)
			np = np->Left;

		return Splay(np, T);
	}
	return NULL;
}

/*�ҵ����ֵ֮�󽫸�ֵ��Ϊ���ڵ�*/
SplayTree FindMax(SplayTree T)
{
	Position np = T;
	if(T!=NULL)
	{
		while(np->Right !=NULL)
			np = np->Right;

		return Splay(np, T);
	}
	return NULL;
}

SplayTree makeEmpty(SplayTree T)
{
	if(T != NULL)
	{
		makeEmpty(T->Left);
		makeEmpty(T->Right);
		free(T);
	}

	return NULL;
}


SplayTree RightSingleRotate(SplayTree T)
{
	SplayTree k1, parent;

	parent = T ->Parent;
	k1 = T->Left;

	k1->Parent = parent;

	/*����k1��������*/
	if(k1->Right)
		k1->Right->Parent = T;
	T->Left = k1->Right;

	/*����k1��T��λ��*/
	T->Parent = k1;
	k1->Right = T;

	/*������һ���ڵ�*/
	if(parent)
	{
		if(parent->Left ==T)
			parent->Left = k1;
		else
			parent->Right = k1;
	}

	return k1;
}

SplayTree LeftSingleRotate(SplayTree k1)
{
	SplayTree k2, parent;

	parent = k1 ->Parent;
	k2 = k1->Right;

	k2->Parent = parent;

	/*����k2��������*/
	if(k2->Left)
		k2->Left->Parent = k1;
	k1->Right = k2->Left;

	/*����k1��T��λ��*/
	k1->Parent = k2;
	k2->Left = k1;

	/*������һ���ڵ�*/
	if(parent)
	{
		if(parent->Left ==k1)
			parent->Left = k2;
		else
			parent->Right = k2;
	}

	return k2;
}

SplayTree RightDoubleRotate(SplayTree k3)
{
	LeftSingleRotate(k3->Left);
	return RightSingleRotate(k3);
}

SplayTree LeftDoubleRotate(SplayTree k1)
{
	RightSingleRotate(k1->Right);
	return LeftSingleRotate(k1);
}

SplayTree Splay(Position np, SplayTree T)
{
	Position P,G;
	P = np->Parent;
	
	while(P != NULL)
	{
		G = P->Parent;
		/*X�Ǹ��׵���ڵ�*/
		if(np == P->Left)
		{
			/*X�ĸ��׽ڵ�Ϊ���ڵ�*/
			if(G == NULL)
				RightSingleRotate(P);
			/*zigzig��״*/
			else if(G->Left == P)
			{
				RightSingleRotate(G);
				/*��һ����ת���֮��P�����G�ĸ��ڵ�*/
				RightSingleRotate(P);
			}
			/*zagzig��״*/
			else
				LeftDoubleRotate(G);
		}
		/*/*X�Ǹ��׵��ҽڵ�*/
		else
		{
			/*X�ĸ��׽ڵ�Ϊ���ڵ�*/
			if(G == NULL)
				LeftSingleRotate(P);
			/*zagzag��״*/
			else if(G->Right == P)
			{
				LeftSingleRotate(G);
				/*��һ����ת���֮��P�����G�ĸ��ڵ�*/
				LeftSingleRotate(P);
			}
			/*zagzig��״*/
			else
				RightDoubleRotate(G);
		}
		
		P= np->Parent;
	}/*while*/

	/*��ʱnp�Ѿ���ɸ��ڵ�*/
	return np;
}


void PrintDepth(ElementType A, int depth)
{
	while(depth !=0)
	{
		printf("	");
		depth --;
	}
	printf("%d\n", A);
}

void PrintTree(SplayTree T, int depth)
{
	if(T == NULL)
	{
		perror("wrong tree");
		exit(1);
	}
	if(T->Left != NULL)
		PrintTree(T->Left, depth+1);

	PrintDepth(T->Element, depth);
	if(T->Right !=NULL)
		PrintTree(T->Right, depth+1);
}

void PrintTree(SplayTree T)
{
	if(T == NULL)
	{
		perror("wrong tree");
		exit(1);
	}
	if(T->Left != NULL)
		PrintTree(T->Left);

	printf("%d\n",T->Element);
	if(T->Right !=NULL)
		PrintTree(T->Right);
}