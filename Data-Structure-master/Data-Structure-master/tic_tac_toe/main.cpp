/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/10/1
description:�����壬ʹ��alpha-beta֦��
			���Դ���
********************************************/

#include "tic_tac_toe.h"



using namespace std;



int main()
{
	char game =' ';
	while(game != 'n' && game != 'N')
	{
		cout<<"you wanna play a game? y/n: ";
		cin >>game;
		if(game == 'y' || game == 'Y')
		{
			srand(time(NULL));
			char first;
			cout<<"you wanna play first?  y/n: ";
			cin >>first;

			if(first == 'y' || first == 'Y')
				manFirst();	
			else
				comFirst();
		}
	}
}






