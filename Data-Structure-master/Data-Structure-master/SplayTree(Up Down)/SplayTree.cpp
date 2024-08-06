/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/7/26
description:SplayTree UpDown�Զ����£����������׽ڵ�
********************************************/
#include "SplayTree.h"
#include <stdlib.h>
#include <iostream>


/*�Ƚ���Splay�������ж��µĸ��ڵ��Ƿ����Ҫ�����ֵ��
���Ҫ�����ֵ�����ڣ�����ֵ��Ϊ���ڵ�ͷ��ص����ϲ��Ϳ���*/
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
		T->Left = T->Right = NULL;
		return T;
	}
	T = Splay(X, T);
	/*Ԫ�ز�����*/
	if(X != T->Element)
	{
		SplayTree newone;
		newone = (SplayTree)malloc(sizeof(struct SplayNode));
		newone->Element = X;
		/*С��T�ĸ��ڵ㣬����ڵ㼰����������Ϊ�½ڵ������������֮��Ȼ*/
		if(X < T->Element)
		{
			newone ->Right = T;
			newone ->Left = T->Left;
			T->Left = NULL;
		}
		else
		{
			newone ->Left = T;
			newone ->Right = T->Right;
			T->Right = NULL;
		}
		T = newone;
	}

	/*Ԫ�ش���ʱֱ�ӷ���T,�벻����ʱ����ֵ��ͬ*/
	return T;

}

SplayTree Delete(ElementType X, SplayTree T)
{
	if(T == NULL)
	{
		fprintf(stderr, "empty Tree");
		return T;
	}
	
	T = Splay(X, T);
	if(X == T->Element)
	{
		/*����������Ϊ�գ���ôѰ�������������ֵ��Ϊ�µĸ��ڵ�*/
		if(T->Left && T->Right)
		{
			SplayTree ltemp,rtemp;
			ltemp = T->Left;
			rtemp = T->Right;
			free(T);
			ltemp = Splay(X, ltemp);
			ltemp->Right =rtemp;
			T = ltemp;
		}
		/*������Ϊ��*/
		else if(T->Left)
		{
			SplayTree temp;
			temp = T;
			T = T->Left;
			free(temp);
		}
		/*������Ϊ��*/
		else
		{
			SplayTree temp;
			temp = T;
			T = T->Right;
			free(temp);
		}
		/*����������Ϊ��Ҳû��ϵ�����ص���NULL*/
	}
	else
		printf("%d don't exist", X);

	return T;
}

SplayTree Find(ElementType X, SplayTree T)
{
	/*����ֱ�ӷ���*/
	if(T==NULL)
	{
		fprintf(stderr, "empty tree");
		return T;
	}
	
	/*����֤��󷵻ص�Ԫ�ص���X����Ҫ�����߼��*/
	T = Splay(X, T);
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

		ElementType X = np->Element;
		return Splay(X, T);
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

		ElementType X = np->Element;
		return Splay(X, T);
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


/*����ת*/
SplayTree RightSingleRotate(SplayTree T)
{
	SplayTree k1;

	k1 = T->Left;
	T->Left = k1->Right;
	k1->Right = T;
	return k1;
}
/*����ת*/
SplayTree LeftSingleRotate(SplayTree k1)
{
	Position k2;

	k2 = k1->Right;
	k1->Right = k2->Left;
	k2->Left = k1;
	return k2;
}


SplayTree Splay(ElementType X, SplayTree T)
{
	SplayNode pseudo;
	SplayTree ltree, rtree;
	ltree = rtree = &pseudo;
	pseudo.Left = pseudo.Right = NULL;

	if(T == NULL || X == T->Element)
		return T;

	for(;;)
	{
		/*С�������ڵ�ʱ*/
		if(X < T->Element)
		{
			/*û����������֤��û���ҵ���ֱ���˳�*/
			if(T->Left == NULL)
				break;
			/*zigzig��״*/
			if(X < T->Left->Element)
			{
				T = RightSingleRotate(T);
				/*��ת��֮�����û����ڵ㣬һ����û�ҵ�*/
				if(T->Left == NULL)
					break;
			}
			/*�����ӣ��������ڵ㼰���������ӵ�������*/
			rtree->Left = T;
			rtree = T;
			T = T->Left;
		}
		else if(X > T->Element)
		{
			/*û����������֤��û���ҵ���ֱ���˳�*/
			if(T->Right == NULL)
				break;
			/*zagzag��״*/
			if(X > T->Right->Element)
			{
				T = LeftSingleRotate(T);
				/*��ת��֮�����û���ҽڵ㣬һ����û�ҵ�*/
				if(T->Right == NULL)
					break;
			}
			/*�����ӣ��������ڵ㼰���������ӵ�������*/
			ltree->Right = T;
			ltree = T;
			T = T->Right;
		}
		/*�ҵ��ýڵ㣬�˳�*/
		else
			break;
	}

	/*���¹����������ڸ��ڵ�����Һ��ӷֱ�ӵ��������ҽڵ����������ڵ�*/
	ltree->Right = T->Left;
	rtree->Left = T->Right;
	T->Left = pseudo.Right;
	T->Right = pseudo.Left;

	return T;
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