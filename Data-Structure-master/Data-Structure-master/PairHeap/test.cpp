/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/10/10
description:��Զ�
********************************************/

#include "PairingHeap.h"
#include <stdlib.h>
#include <iostream>

int main()
{
	int i;
	PairHeap One;
	One = NULL;

	Position Location;

	/*�������ݣ��Ȳ���10���ٷֱ�ż����������0-20*/
	insert(10, One, &Location);

	for(i = 0; i<10; i++)
	{
		One = insert(2*i, One, &Location);
	}

	for(i = 0; i<10; i++)
	{
		One = insert(2*i+1, One, &Location);
	}
	/*��ӡ������ÿһ����ȼ�һ��4���ո��ȴ�ӡ�������ٴ�ӡ������*/
	PrintTree(One,0);

	
	printf("\n\n\n\n");


	DecreaseKey(Location, 3,  One);
	PrintTree(One,0);
	printf("\n\n\n\n");

	/*ɾ��Ԫ��֮�����*/
	int Min;
	One = deleteMin(& Min, One);

	PrintTree(One,0);






	std::cout<<std::endl;
}