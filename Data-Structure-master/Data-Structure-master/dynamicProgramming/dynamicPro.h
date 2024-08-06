/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/9/27
description:��̬�滮���⣬
			쳲��������м���
			C(N)=(2/N)((C(0)+0) + (C(1)+1) + ... +(C(N-1)+N-1))�������
			����˷�˳����
********************************************/
#include <string>

typedef int TwoDimArray[8][8];
typedef double doubleArray[8][8];

/*쳲��������м���*/
int Fibonacci(int N);

/*C(N)=(2/N)((C(0)+0) + (C(1)+1) + ... +(C(N-1)+N-1))�������*/
double Eval(int N);

/*����˷�˳����*/
void OptMatrix(const long C[], int N, TwoDimArray M, TwoDimArray LastChange);




struct Vocab
{
	std::string name;
	double value;
};

typedef struct Vocab Vob;



/*���Ų��Ҷ�����*/
void OptSearchTree(const Vob C[], int N, doubleArray &M, TwoDimArray &LastChange);