/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/9/22
description:�������ľ���
********************************************/
#include "nearPoint.h"
#include <cstdio>
#include <cmath>


float ABS(float a)
{
	return a>0? a:-a;
}



void getNearDis(PointX X[], int N, PointX &a, PointX &b, float &d)
{
	MergeSort(X, N);

	PointY *Y = new PointY[N];

	for(int i=0; i<N; i++)
	{
		Y[i].xID = i;
		Y[i].x = X[i].x;
		Y[i].x = X[i].y;
	}

	MergeSort(Y, N);

	PointY *Z = new PointY[N];
	getClosest(X, Y, Z, 0, N-1, a, b, d);

	delete [] Y;
	delete [] Z;
}



void getClosest(PointX X[], PointY Y[], PointY Z[], int left, int right, PointX &a, PointX &b, float &d)
{
	/*ʣ��������*/
	if(right -left ==1)
	{
		d = getDis(X[left], X[right]);
		a = X[left];
		b = X[right];
		return;
	}
	/*ʣ��������*/
	if(right - left ==2)
	{
		float d1, d2, d3;
		d1 = getDis(X[left], X[right-1]);
		d2 = getDis(X[left], X[right]);
		d3 = getDis(X[left+1], X[right]);

        if(d1<=d2 && d1<=d3)   
        {   
            a=X[left];  
            b=X[right -1];  
            d=d1;  
            return;  
        }   
  
        if(d2<=d3)  
        {   
            a=X[left];  
            b=X[right];  
            d=d2;  
        }   
        else {   
            a=X[left+1];   
            b=X[right];   
            d=d3;   
        } 
			
		return;
	}

	int center = (left + right)/2;

	int k = left;
	int g= center +1;
	/*���Ѿ���Y����ĵ㣬�������ߣ��ֱ����������ߺ��ұ�*/
	for(int i = left; i <=right; i++)
	{
		if(Y[i].xID <= center) 
			Z[k++] = Y[i];
		else
			Z[g++] = Y[i];
	}

	PointX atmp, btmp;
	float dtmp;

	getClosest(X, Z, Y, left, center, a, b, d);
	getClosest(X, Z, Y, center+1, right, atmp, btmp, dtmp);

	if(dtmp< d)
	{
		a = atmp;
		b = btmp;
		d = dtmp;
	}

	Merge(Z, Y, left, center+1, right);

	int f = left;
	/*���������߾�����d�ڵĵ����Z�У�������Щ���ǰ���y�����С��������� */
	for(int i =left; i<=right; i++)
	{
		if(ABS(X[center].x - Y[i].x) <d)
			Z[f++] = Y[i];
	}

	/*�����ոռ���strip�еĵ㣬 ���y֮��ľ������d���Ϳ�ʼ����*/
	for(int i=left; i<f; i++)
		for(int j = i+1; j< f && (Y[j].y-Y[i].y) < d; j++)
		{
			dtmp =getDis(Y[i], Y[j]);
			if(dtmp <d)
			{
				d = dtmp;
				a = X[Y[i].xID];
				b = X[Y[j].xID];
			}
		}
}




