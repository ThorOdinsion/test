/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/9/30
description:��·�ؽ����⣬���������������ݽṹ
			��Ҫ֧�ֶ���ظ���key�����ڱ�ݣ�����
			����ֱ��ʹ��multiset�������б�д�ˡ�
********************************************/
#include "roadRebuild.h"

bool Turnpike(int X[], multiset<int> D, int N)
{
	X[1] = 0;
	auto it = D.end();
	X[N] = *(--it);
	--it;
	D.erase(X[N]);
	X[N-1] = *(it);
	D.erase(X[N-1]);

	if((it = D.find(X[N]- X[N-1])) != D.end())
	{
		D.erase(it);
		return Place(X, D, N, 2, N-2);
	}
	return 0;
}

bool Place(int X[], multiset<int> D, int N, int left, int right)
{
	bool found = false;

	if(D.empty())
		return true;

	auto it = D.end();
	--it;
	X[right] = *it;
	

	int i, j;
	/*�ж���ߵ㵽X[right]�ľ����Ƿ񶼴���*/
	for(i=1; i<left; i++)
	{
		if((it = D.find(X[right] - X[i])) != D.end())
			D.erase(it);
		else
		{
			for(int k = i-1;k>0; k--)
				D.insert(X[right] - X[i]);
			break;
		}
	}
	/*��ߵ㵽X[right]���붼�������ж��ұ�*/
	if(i == left)
	{
		for(i=right+1; i<=N; i++)
		{
			if((it = D.find(X[i] - X[right])) != D.end())
				D.erase(it);
			else
			{
				/*�ұ߲����ϣ����ð���ǰ�����ɾ���Ľڵ㲹���ٲ����ұߵ�*/
				for(int k = 1;k<left; k++)
					D.insert(X[right] - X[k]);

				for(int k = i-1;k>right; k--)
					D.insert(X[k] - X[right]);
				break;
			}
		}
		/*�������߶����ϣ�������һ���жϣ������Ͼͼ���ִ�г���*/
		if(i == N+1)
		{
			found = Place(X, D, N, left, right-1);

			/*��һ��ɹ���ֱ�ӷ��سɹ������������*/
			if(!found)
			{
				for(i=1; i<left; i++)
					D.insert(X[right] - X[i]);
				for(i=right+1; i<=N; i++)
					D.insert(X[i] - X[right]);
			}
			else
				return true;
		}
	}

	/*�����һ��û�з��أ�������뵽rightʧ�ܣ����ڲ��뵽���*/

	X[left] = X[N] - X[right];

	/*�ж���ߵ㵽X[left]�ľ����Ƿ񶼴���*/
	for(i=1; i<left; i++)
	{
		if((it = D.find(X[left] - X[i])) != D.end())
			D.erase(it);
		else
		{
			for(int k = i-1;k>= 0; k--)
				D.insert(X[left] - X[k]);
			break;
		}
	}
	/*��ߵ㵽X[right]���붼�������ж��ұ�*/
	if(i == left)
	{
		for(i=right+1; i<=N; i++)
		{
			if((it = D.find(X[i] - X[left])) != D.end())
				D.erase(it);
			else
			{
				/*�ұ߲����ϣ����ð���ǰ�����ɾ���Ľڵ㲹���ٲ����ұߵ�*/
				for(int k = 1;k<left; k++)
					D.insert(X[left] - X[k]);

				for(int k = i-1;k> right; k--)
					D.insert(X[k] - X[left]);
				break;
			}
		}
		/*�������߶����ϣ�������һ���жϣ������Ͼͼ���ִ�г���*/
		if(i == N+1)
		{
			found = Place(X, D, N, left+1, right);

			/*��һ��ɹ���ֱ�ӷ��سɹ������򷵻�ʧ��*/
			if(!found)
			{
				for(i=1; i<left; i++)
					D.insert(X[left] - X[i]);
				for(i=right+1; i<=N; i++)
					D.insert(X[i] - X[left]);
			}
			else
				return true;
		}
	}

	return false;

}