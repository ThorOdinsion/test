/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/9/30
description:��·�ؽ����⣬���������������ݽṹ
			��Ҫ֧�ֶ���ظ���key�����ڱ�ݣ�����
			����ֱ��ʹ��multiset�������б�д�ˡ�
********************************************/


#include <set>

using namespace std;


bool Turnpike(int X[], multiset<int> D, int N);

bool Place(int X[], multiset<int> D, int N, int left, int right);