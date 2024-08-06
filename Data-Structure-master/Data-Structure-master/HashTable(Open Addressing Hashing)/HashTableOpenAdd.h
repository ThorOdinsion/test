/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/7/30
description:��ϣ��(���Ŷ�ַ��)
********************************************/

#ifndef _HASH_TABLE
#define _HASH_TABLE

struct HashTbl;
typedef HashTbl * HashTable;
typedef int ElementType;
typedef unsigned int Index;
typedef Index Position;


HashTable initializeTable(int TableSize);
void DestroyTable(HashTable H);
Position FindKey(ElementType Key, HashTable H);
void insertKey(ElementType Key, HashTable H);
void deleteKey(ElementType Key, HashTable H);

void PrintHashTable(HashTable H);

/*ƽ��ȡ�з�*/
int Hash(ElementType Key, int TableSize);

/*��EmptyĬ��Ϊ0����ʹ��calloc�����Զ���ʼ��ΪEmpty*/
enum KindOfEntry
{
	Empty =0,
	Legitimate,
	Deleted
};

struct HashEntry
{
	ElementType Element;
	enum KindOfEntry Info;
};

typedef struct HashEntry Cell;

struct HashTbl
{
	int TableSize;
	Cell * TheCells;
};


#endif