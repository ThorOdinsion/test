/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/9/30
description:��·�ؽ����⣬���������������ݽṹ
			��Ҫ֧�ֶ���ظ���key�����ڱ�ݣ�����
			����ֱ��ʹ��multiset�������б�д�ˡ�
********************************************/
#include "roadRebuild.h"
#include <iostream>

int main()
{
	multiset<int> D;
	D.insert(1);
	D.insert(2);
	D.insert(2);
	D.insert(2);
	D.insert(3);
	D.insert(3);
	D.insert(3);
	D.insert(4);
	D.insert(5);
	D.insert(5);
	D.insert(5);
	D.insert(6);
	D.insert(7);
	D.insert(8);
	D.insert(10);

	cout<<"the ansewer is: "<<endl;

	int X[7];
	if(Turnpike(X, D, 6))
		for(int i=1; i<7; i++)
			cout<<X[i]<<endl;

	else
		cout<<"cannot find a result"<<endl;

	
}
