/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/9/28
description:����
********************************************/


#define MAX_LEVEL 10 //������ 
//�ڵ�  
typedef  struct nodeStructure  
{  
    int key;  
    int value;  
    struct nodeStructure *forward[1];  
}nodeStructure;  
    
//����  
typedef  struct skiplist  
{  
    int level;  
    nodeStructure *header;  
}skiplist;  

//�����ڵ�  
nodeStructure* createNode(int level,int key,int value);

//��ʼ������  
skiplist* createSkiplist();

//�����������  
int randomLevel();
	
//����ڵ�  
bool insert(skiplist *sl,int key,int value);

//����ָ��key��value  
void search(skiplist *sl,int key, nodeStructure **&update); 

//ɾ��ָ����key  
bool deleteSL(skiplist *sl,int key);

void printSL(skiplist *sl);