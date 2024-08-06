#include "sort.h"
#include "binaryHeap.h"
#include <stdlib.h>
#include <iostream>

/*��������*/
void InsertionSort(ElementType A[], int N)
{
	int i,j;
	ElementType temp;

	for(i=1; i<N; i++)
	{
		temp = A[i];

		for(j=i; j>0; j--)
		{
			if(temp <A[j-1])
				A[j] = A[j-1];
			else
				break;
		}
		A[j] = temp;
	}
}

/*ϣ������*/
void ShellSort(ElementType A[], int N)
{
	/*Sedgewick����*/
	int Sedgewick[5] = {109, 41, 19, 5, 1};
	
	int i, j;
	int Index, Increament;
	ElementType temp;

	for(Index=0; Index<5; Index++)
		if(Sedgewick[Index] < N)
			break;
	if(Index == 5)
		return;

	for(; Index<5; Index++)
	{
		Increament = Sedgewick[Index];
		for(i=Increament; i<N; i++)
		{
			temp = A[i];
			for(j = i; j>Increament-1; j--)
			{
				if(temp < A[j-Increament])
					A[j] = A[j-Increament];
				else
					break;
			}
			A[j] = temp;
		}
	}
}

/*������ֱ�ӵ�����֮ǰ��д�Ķ���Ѵ���*/
void HeapSort(ElementType A[], int N)
{
	int i;
	PriorityQueue H = BuildHeap(A, N);
	for(i=0; i<N; i++)
		A[i] = DeleteMin(H);

	Destroy(H);
}


/*�鲢����*/
void Merge(ElementType A[], ElementType TmpArray[], int Lpos, int Rpos, int RightEnd)
{
	int i, LeftEnd, Num, TmpPos;
	LeftEnd = Rpos -1;
	Num = RightEnd - Lpos +1;
	TmpPos = Lpos;

	while(Lpos <= LeftEnd && Rpos <= RightEnd)
	{
		if(A[Lpos] < A[Rpos])
			TmpArray[TmpPos++] = A[Lpos++];
		else
			TmpArray[TmpPos++] = A[Rpos++];
	}

	/*����ʣ�µ�����*/
	while(Lpos <= LeftEnd)
		TmpArray[TmpPos++] = A[Lpos++];

	while(Rpos <= RightEnd)
		TmpArray[TmpPos++] = A[Rpos++];

	/*������ԭ��������*/
	for(i =0; i<Num; i++, RightEnd--)
	{
		A[RightEnd] = TmpArray[RightEnd];
	}
}



void Msort(ElementType A[], ElementType TmpArray[], int Left, int Right)
{
	int Center;
	if(Left < Right)
	{
		Center = (Left+Right)/2;
		Msort(A, TmpArray, Left, Center);
		Msort(A, TmpArray, Center+1, Right);
		Merge(A, TmpArray, Left, Center+1, Right);
	}
}



void MergeSort(ElementType A[], int N)
{
	ElementType * TmpArray = (ElementType *)malloc(N*sizeof(ElementType));
	if(TmpArray == NULL)
	{
		fprintf(stderr, "not enough memory\n");
		exit(1);
	}

	Msort(A, TmpArray, 0, N-1);
	free(TmpArray);
}

/*��������*/

void Swap(ElementType *A, ElementType *B)
{
	ElementType temp;
	temp = *A;
	*A = *B;
	*B = temp;
}

ElementType Median3(ElementType A[], int Left, int Right)
{
	int Center = (Left + Right) / 2;

	/*�����ң���С��������*/
	if(A[Left] > A[Center])
		Swap(&A[Left], &A[Center]);
	if(A[Left] > A[Right])
		Swap(&A[Left], &A[Right]);
	if(A[Center] > A[Right])
		Swap(&A[Center], &A[Right]);

	Swap(&A[Center], &A[Right-1]);
	return A[Right-1];
}

#define Cutoff (3)

void Qsort(ElementType A[], int Left, int Right)
{
	int i,j;
	ElementType Pivot;
	
	Pivot = Median3(A, Left, Right);

	if(Left + Cutoff <Right)
	{
		i = Left;
		j = Right-1;
		while(1)
		{
			while(A[++i] < Pivot);
			while(A[--j] > Pivot);
			if(i < j)
				Swap(&A[i], &A[j]);
			else
				break;
		}
		/*����ŦԪ�Ż��м�,��ʱ��ŦԪ��ߵ����ݶ�����С
		�ұߵ����ݶ��������ٶ������������򼴿�*/
		Swap(&A[i], &A[Right-1]);

		Qsort(A, Left, i-1);
		Qsort(A, i+1, Right);
	}
	else
		/*����3�����ݾ�ֱ��ʹ�ò����������*/
		InsertionSort(A+Left, Right-Left+1);
}

void QuickSort(ElementType A[], int N)
{
	Qsort(A, 0, N-1);
}



/*����ѡ��,ѡ�����֮��Ҫ��ĵ�KС�����������±�Ϊk-1��*/
void QSelect(ElementType A[], int k, int Left, int Right)
{
	int i,j;
	ElementType Pivot;
	
	Pivot = Median3(A, Left, Right);

	if(Left + Cutoff <Right)
	{
		i = Left;
		j = Right-1;
		while(1)
		{
			while(A[++i] < Pivot);
			while(A[--j] > Pivot);
			if(i < j)
				Swap(&A[i], &A[j]);
			else
				break;
		}
		/*����ŦԪ�Ż��м�,��ʱ��ŦԪ��ߵ����ݶ�����С
		�ұߵ����ݶ��������ٶ������������򼴿�*/
		Swap(&A[i], &A[Right-1]);

		/*k=i+1��ʱ�򣬼���i=k-1��ʱ�򣬴�����ŦԪ���Ѿ���Ҫ��Ľ���ˣ�
		���ô���k-1�ϣ����ﲻʹ��k-1�����ж���Ϊ�˱���k=0�����*/
		if(k <=i)
			QSelect(A, k, Left, i-1);
		else if(k>i+1)
			QSelect(A, k, i+1, Right);
	}
	else/*����3�����ݾ�ֱ��ʹ�ò����������*/
		InsertionSort(A+Left, Right-Left+1);
}


void QuickSelect(ElementType A[], int k, int N)
{
	QSelect(A, k, 0, N-1);
}