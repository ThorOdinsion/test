/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/7/20
description:���������
********************************************/
#include "searchTree.h"

#include <stdlib.h>
#include <malloc.h>
#include <iostream>
SearchTree MakeEmpty(SearchTree T)
{
	if(T != NULL)
	{
		MakeEmpty(T->lchild);
		MakeEmpty(T->rchild);
		free(T);
	}

	return NULL;
}

/*�ݹ����*/
Position Find(ElementType X, SearchTree T)
{
	if(T == NULL)
		return NULL;

	if(T->Element == X)
		return T;
	else if(X <T->Element)
		return Find(X, T->lchild);
	else
		return Find(X, T->rchild);
}

/*�ǵݹ������Сֵ*/
Position FindMin(SearchTree T)
{
	if(T!=NULL)
	{
		while(T->lchild !=NULL)
			T = T->lchild;

		return T;
	}
	return NULL;
}

/*�ǵݹ�������ֵ*/
Position FindMax(SearchTree T)
{
	if(T!= NULL)
	{
		while(T->rchild !=NULL)
			T= T->rchild;

		return T;
	}
	return NULL;
}

/*�ݹ����*/
SearchTree Insert(ElementType X, SearchTree T)
{
	if(T ==NULL)
	{
		T = (SearchTree)malloc(sizeof(TreeNode));
		T->Element = X;
		T->lchild = T->rchild = NULL;

	}
	else if(X< T->Element)
	{
		T->lchild = Insert(X, T->lchild);
	}
	else if(X>T->Element)
	{
		T->rchild = Insert(X, T->rchild);
	}
	return T;

}

/*�ݹ�ɾ��*/
SearchTree Delete(ElementType X, SearchTree T)
{
	Position tempCell;
	if(T ==NULL)
	{
		perror("Element not Found");
		return NULL;
	}
	if(X< T->Element)
		T->lchild = Delete(X, T->lchild);
	else if(X> T->Element)
		T->rchild = Delete(X, T->rchild);
	else
	{
		/*�ҵ������ڵ�������������ӵĻ������������������ֵ����õ㣬��ɾȥ�������ϵ����ֵ*/
		if(T->lchild && T->rchild)
		{
			tempCell = FindMin(T->rchild);
			T->Element = tempCell ->Element;
			T->rchild = Delete(T->Element, T->rchild);
		}
		else 
		{
			tempCell = T;
			if(T->lchild ==NULL)
				T = T->rchild;
			else
				T = T->lchild;
			free(tempCell);
		}
	}
	return T;

}
/*��ӡ�ڵ�ֵ�����������֮ǰ����4���ո�*/
void PrintDepth(ElementType A, int depth)
{
	while(depth !=0)
	{
		printf("	");
		depth --;
	}
	printf("%d\n", A);
}
/*��ӡ����depthΪ���ڵ�ĳ�ʼ�����*/
void PrintTree(SearchTree T, int depth)
{
	if(T == NULL)
	{
		perror("wrong tree");
		exit(1);
	}
	if(T->lchild != NULL)
		PrintTree(T->lchild, depth+1);

	PrintDepth(T->Element, depth);
	if(T->rchild !=NULL)
		PrintTree(T->rchild, depth+1);
}
/*��ӡ�����ȴ�Ӧ�������ٴ�ӡ������*/
void PrintTree(SearchTree T)
{
	if(T == NULL)
	{
		perror("wrong tree");
		exit(1);
	}
	if(T->lchild != NULL)
		PrintTree(T->lchild);

	printf("%d\n",T->Element);
	if(T->rchild !=NULL)
		PrintTree(T->rchild);
}