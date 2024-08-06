/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/8/11
description:�������
********************************************/

#include "binomialQueue.h"
#include <stdlib.h>
#include <iostream>

int main()
{
	int i, j;
	BinQueue One;
	One = initialize();

	/*�������ݣ��Ȳ���10���ٷֱ�ż����������0-20*/
	insert(10, One);
	insert(0, One);
	insert(1, One);
	for(j = 0; j<10; j++)
	{
		insert(2*j, One);

	}

	for(j = 0; j<10; j++)
	{
		insert(2*j+1, One);

	}

	/*��ӡ������ÿһ����ȼ�һ��4���ո��ȴ�ӡ�������ٴ�ӡ�ֵ�*/
	for(i =0; i< MaxSize; i ++)
	{
		if(One ->theTrees[i])
		{
			PrintTree(One ->theTrees[i],0);
			printf("\n\n");
		}

	}



	printf("\n\n\n\n");

	/*ɾ��Ԫ��֮�����*/

	DeleteMin(One);
	DeleteMin(One);

	for(i =0; i< MaxSize; i ++)
	{
		if(One ->theTrees[i])
		{
			PrintTree(One ->theTrees[i],0);
			printf("\n\n");
		}

	}

	std::cout<<std::endl;
}