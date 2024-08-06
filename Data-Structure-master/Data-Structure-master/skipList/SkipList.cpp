/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/9/28
description:����
********************************************/
#include "SkipList.h"
#include<stdio.h>  
#include<stdlib.h>  
    

 
    

    
//�����ڵ�  
nodeStructure* createNode(int level,int key,int value)  
{  
    nodeStructure *ns=(nodeStructure *)malloc(sizeof(nodeStructure)+level*sizeof(nodeStructure*));    
    ns->key=key;    
    ns->value=value;    
    return ns;    
}  
    
//��ʼ������  
skiplist* createSkiplist()  
{  
    skiplist *sl=(skiplist *)malloc(sizeof(skiplist));    
    sl->level=0;    
    sl->header=createNode(MAX_LEVEL-1,0,0);    
    for(int i=0;i<MAX_LEVEL;i++)    
    {    
        sl->header->forward[i]=NULL;    
    }  
    return sl;  
}  
    
//�����������  
int randomLevel()    
{  
    int k=1;  
    while (rand()%2)    
        k++;    
    k=(k<MAX_LEVEL)?k:MAX_LEVEL;  
    return k;    
}  
    
//����ڵ�  
bool insert(skiplist *sl,int key,int value)  
{  
    nodeStructure **update = (nodeStructure **)calloc(MAX_LEVEL,sizeof(nodeStructure*));  
    
	search(sl, key, update);
    //���ܲ�����ͬ��key  
	if(update[0] && update[0]->forward[0] &&update[0]->forward[0]->key == key)  
    {  
		free(update);
        return false;  
    }  
    
    //����һ���������K  
    //�½�һ��������ڵ�q  
    //һ��һ�����  
    int k=randomLevel();  
    //���������level  
    if(k>(sl->level))  
    {  
        for(int i=sl->level; i < k; i++){  
            update[i] = sl->header;  
        }  
        sl->level=k;  
    }  
    
	nodeStructure * q=createNode(k,key,value);  
    //�����½ڵ��ָ�룬����ͨ�б����һ��  
    for(int i=0;i<k;i++)  
    {  
        q->forward[i]=update[i]->forward[i];  
        update[i]->forward[i]=q;  
    }  
	free(update);
    return true;  
}  
    
//����ָ��key��value  
void search(skiplist *sl,int key, nodeStructure **&update)
{  
    nodeStructure *p,*q=NULL;  
    p=sl->header;  
    //����߲㿪ʼ��  
    int k=sl->level;  
    //����߲����²�����Ҫ�����λ��  
    //���update  
    for(int i=k-1; i >= 0; i--){  
        while((q=p->forward[i])&&(q->key<key))  
        {  
            p=q;  
        }  
        update[i]=p;  
    }     
}  
    
//ɾ��ָ����key  
bool deleteSL(skiplist *sl,int key)  
{  
    nodeStructure **update = (nodeStructure **)calloc(MAX_LEVEL,sizeof(nodeStructure*));  
	//Ѱ�ҽڵ�
	search(sl, key, update);

	nodeStructure *target;
    if(update[0])
		target = update[0]->forward[0];
	else
	{
		free(update);
		return false;
	}

	if(target && target->key == key)  
    {  
        //���ɾ��������ͨ�б�ɾ��һ��  
        for(int i=0; i<sl->level; i++){    
            if(update[i]->forward[i]==target){    
                update[i]->forward[i]=target->forward[i];    
            }  
        }   
        free(target);  
        //���ɾ����������Ľڵ㣬��ô��Ҫ����ά�������  
        for(int i=sl->level - 1; i >= 0; i--){    
            if(sl->header->forward[i]==NULL){    
                sl->level--;    
            }    
        }   
		free(update);
        return true;  
    }  
    else  
	{
		free(update);
        return false;
	}
}  
    
void printSL(skiplist *sl)  
{  
    //����߲㿪ʼ��ӡ  
    nodeStructure *p,*q=NULL;  
    
    //����߲㿪ʼ��  
    int k=sl->level;  
    for(int i=k-1; i >= 0; i--)  
    {  
        p=sl->header;  
        while(q=p->forward[i])  
        {  
            printf("%d -> ",p->value);  
            p=q;  
        }  
        printf("\n");  
    }  
    printf("\n");  
}  


////�����ڵ�  
//nodeStructure* createNode(int level,int key,int value)  
//{  
//    nodeStructure *ns=(nodeStructure *)malloc(sizeof(nodeStructure)+level*sizeof(nodeStructure*));    
//    ns->key=key;    
//    ns->value=value;    
//    return ns;    
//}  
//    
////��ʼ������  
//skiplist* createSkiplist()  
//{  
//    skiplist *sl=(skiplist *)malloc(sizeof(skiplist));    
//    sl->level=0;    
//    sl->header=createNode(MAX_LEVEL-1,0,0);    
//    for(int i=0;i<MAX_LEVEL;i++)    
//    {    
//        sl->header->forward[i]=NULL;    
//    }  
//    return sl;  
//}  
//    
////�����������  
//int randomLevel()    
//{  
//    int k=1;  
//    while (rand()%2)    
//        k++;    
//    k=(k<MAX_LEVEL)?k:MAX_LEVEL;  
//    return k;    
//}  
//    
////����ڵ�  
//bool insert(skiplist *sl,int key,int value)  
//{  
//    nodeStructure *update[MAX_LEVEL];  
//    nodeStructure *p, *q = NULL;  
//    p=sl->header;  
//    int k=sl->level;  
//    //����߲����²�����Ҫ�����λ��  
//    //���update  
//    for(int i=k-1; i >= 0; i--){  
//        while((q=p->forward[i])&&(q->key<key))  
//        {  
//            p=q;  
//        }  
//        update[i]=p;  
//    }  
//    //���ܲ�����ͬ��key  
//    if(q&&q->key==key)  
//    {  
//        return false;  
//    }  
//    
//    //����һ���������K  
//    //�½�һ��������ڵ�q  
//    //һ��һ�����  
//    k=randomLevel();  
//    //���������level  
//    if(k>(sl->level))  
//    {  
//        for(int i=sl->level; i < k; i++){  
//            update[i] = sl->header;  
//        }  
//        sl->level=k;  
//    }  
//    
//    q=createNode(k,key,value);  
//    //�����½ڵ��ָ�룬����ͨ�б����һ��  
//    for(int i=0;i<k;i++)  
//    {  
//        q->forward[i]=update[i]->forward[i];  
//        update[i]->forward[i]=q;  
//    }  
//    return true;  
//}  
//    
////����ָ��key��value  
//int search(skiplist *sl,int key)  
//{  
//    nodeStructure *p,*q=NULL;  
//    p=sl->header;  
//    //����߲㿪ʼ��  
//    int k=sl->level;  
//    for(int i=k-1; i >= 0; i--){  
//        while((q=p->forward[i])&&(q->key<=key))  
//        {  
//            if(q->key == key)  
//            {  
//                return q->value;  
//            }  
//            p=q;  
//        }  
//    }  
//    return NULL;  
//}  
//    
////ɾ��ָ����key  
//bool deleteSL(skiplist *sl,int key)  
//{  
//    nodeStructure *update[MAX_LEVEL];  
//    nodeStructure *p,*q=NULL;  
//    p=sl->header;  
//    //����߲㿪ʼ��  
//    int k=sl->level;  
//    for(int i=k-1; i >= 0; i--){  
//        while((q=p->forward[i])&&(q->key<key))  
//        {  
//            p=q;  
//        }  
//        update[i]=p;  
//    }  
//    if(q&&q->key==key)  
//    {  
//        //���ɾ��������ͨ�б�ɾ��һ��  
//        for(int i=0; i<sl->level; i++){    
//            if(update[i]->forward[i]==q){    
//                update[i]->forward[i]=q->forward[i];    
//            }  
//        }   
//        free(q);  
//        //���ɾ����������Ľڵ㣬��ô��Ҫ����ά�������  
//        for(int i=sl->level - 1; i >= 0; i--){    
//            if(sl->header->forward[i]==NULL){    
//                sl->level--;    
//            }    
//        }    
//        return true;  
//    }  
//    else  
//        return false;  
//}  
//    
//void printSL(skiplist *sl)  
//{  
//    //����߲㿪ʼ��ӡ  
//    nodeStructure *p,*q=NULL;  
//    
//    //����߲㿪ʼ��  
//    int k=sl->level;  
//    for(int i=k-1; i >= 0; i--)  
//    {  
//        p=sl->header;  
//        while(q=p->forward[i])  
//        {  
//            printf("%d -> ",p->value);  
//            p=q;  
//        }  
//        printf("\n");  
//    }  
//    printf("\n");  
//}  