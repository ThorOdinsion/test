/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/10/4
description:�Զ����µĺ����
			�Զ����²���
			�Զ�����ɾ��
********************************************/
#include <cstdlib>

typedef int ElementType;
struct RedBlackNode;
typedef struct RedBlackNode * RedBlackTree;
typedef RedBlackTree Position;

typedef enum ColorType
{
	Red, Black
}ColorType;

struct RedBlackNode
{
	ElementType Elememt;
	RedBlackTree left;
	RedBlackTree right;
	ColorType color;

};

/*��ӡ�����*/
void DoPrint(RedBlackTree T, int depth);

/*��ӡ�����������Һ���Ϊ�����ĺ����*/
inline void PrintTree(RedBlackTree T)
{DoPrint(T->right, 0);}

/*��ʼ������������NullNodeδ����ʼ����������ռ�*/
RedBlackTree Initialize();

/*��Ҫ������ת��ʱ�������ת����ת֮ǰӦ�Ƚ����ж�*/
static Position Rotate(ElementType item, RedBlackTree Parent);

/*�������Ӷ��Ǻ�ɫ�ڵ�ʱ���������׺ͺ��ӽڵ����ɫ���б�Ҫ��ʱ�������ת*/
static void HandleReorient(ElementType item, RedBlackTree T);

/*����ڵ㣬����ڵ��Ѿ����ڣ���ʲôҲ����*/
RedBlackTree insert(ElementType item, RedBlackTree T);

/*ɾ���ڵ�*/
RedBlackTree Delete(ElementType item, RedBlackTree T);

/*������*/
void destroyTree(RedBlackTree T);

/*Ѱ�����ڵ㣬�����Ԫ�ز����ڣ��򷵻�����󵽴�Ľڵ�*/
RedBlackTree find(ElementType item, RedBlackTree T);


/*ɾ��ֻ��һ�����ӣ�����û�к��ӵĽڵ�*/
RedBlackTree DeleteNode(RedBlackTree target, RedBlackTree T);

/*����ת*/
RedBlackTree rightSingleRotate(RedBlackTree T);

/*����ת*/
RedBlackTree leftSingleRotate(RedBlackTree k1);