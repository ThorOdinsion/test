/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/7/26
description:SplayTree UpDown�Զ����£����������׽ڵ�
			���Դ���
********************************************/
#include "SplayTree.h"
#include <stdlib.h>
#include <iostream>

int main()
{
	int i;
	SplayTree One;
	One = NULL;

	/*�������ݣ��Ȳ���10���ٷֱ�ż����������0-20*/
	One = insert(10, One);

	for(i = 0; i<10; i++)
	{
		One = insert(2*i, One);
	}

	for(i = 0; i<10; i++)
	{
		One = insert(2*i+1, One);
	}
	/*��ӡ������ÿһ����ȼ�һ��4���ո��ȴ�ӡ�������ٴ�ӡ������*/
	PrintTree(One,0);
	printf("\n\n\n\n");

	/*Ѱ��5֮�����*/
	One = Find(5,One);
	PrintTree(One,0);
	printf("\n\n\n\n");

	/*ɾ��Ԫ��֮�����*/
	One = Delete(11, One);
	One = Delete(3, One);
	One = Delete(21, One);
	printf("\n\n\n\n");
	printf("\n\n\n\n");

	One = Delete(3, One);
	One = Delete(8, One);
	One = Delete(16, One);
	PrintTree(One,0);
	
	std::cout<<std::endl;
}