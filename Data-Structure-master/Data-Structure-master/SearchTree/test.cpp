/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/7/20
description:������������Դ���
********************************************/
#include "searchTree.h"
#include <stdlib.h>
#include <malloc.h>
#include <iostream>

int main()
{

#pragma region searchtree
	int i;
	SearchTree One;
	One = NULL;
	/*�������ݣ��Ȳ���10���ٲ���ż��������*/
	One = Insert(10, One);
	for(i = 0; i<10; i++)
	{
		One = Insert(2*i, One);
	}
	for(i = 0; i<10; i++)
	{
		One = Insert(2*i+1, One);
	}
	
	PrintTree(One,0);
	/*ɾ���ڵ�*/
	Delete(20, One);

	Delete(11, One);

	Delete(3, One);

	PrintTree(One,0);



	std::cout<<std::endl;

#pragma endregion  

}