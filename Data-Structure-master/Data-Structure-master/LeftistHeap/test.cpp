/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/8/4
description:��չ���Ĳ��Դ��룬������Ľṹ
********************************************/
#include "LeftistHeap.h"
#include <stdlib.h>
#include <iostream>

int main()
{
	int i;
	PriorityQueue One;
	One = NULL;

	/*�������ݣ��Ȳ���10���ٷֱ�ż����������0-20*/
	insert(10, One);

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

	PrintTree(One,0);
	printf("\n\n\n\n");

	/*ɾ��Ԫ��֮�����*/



	PrintTree(One,0);






	std::cout<<std::endl;
}