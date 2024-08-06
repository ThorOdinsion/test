/***************************************
Author: YinWen
email: yinwenatbit@163.com
date: 2015/10/4
description:�Զ����µĺ����
			�Զ����²���
			�Զ�����ɾ��
********************************************/

#include "RedBlackTree.h"
#include <iostream>
#define Infinity 0x7FFFFFFF
#define NegInfinity 0x8FFFFFFF

Position NullNode = NULL;

static Position X, P, GP, GGP, BRO;

/*����ת*/
RedBlackTree rightSingleRotate(RedBlackTree T)
{
	RedBlackTree k1;

	k1 = T->left;
	T->left = k1->right;
	k1->right = T;
	return k1;
}
/*����ת*/
RedBlackTree leftSingleRotate(RedBlackTree k1)
{
	Position k2;

	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	return k2;
}


/*��ӡ�����*/
void DoPrint(RedBlackTree T, int depth)
{
	if(T != NullNode)
	{
		DoPrint(T->left, depth +1);
		for(int i =0; i<depth; i++)
			printf("    ");
		printf("%d,%s\n", T->Elememt, T->color == Red? "Red":"Black");

		DoPrint(T->right, depth+1);
	}
}


/*��ʼ������������NullNodeδ����ʼ����������ռ�*/
RedBlackTree Initialize()
{
	if(NullNode == NULL)
	{
		NullNode = (RedBlackTree)malloc(sizeof(struct RedBlackNode));
		if(NullNode == NULL)
			exit(1);
		NullNode->color = Black;
		NullNode->left = NullNode->right= NullNode;
		NullNode->Elememt = Infinity;
	}

	RedBlackTree T;
	T = (RedBlackTree)malloc(sizeof(struct RedBlackNode));
	if(T == NULL)
		exit(1);

	T->Elememt = NegInfinity;
	T->left = T->right = NullNode;
	T->color = Black;
	
	return T;
}

/*��Ҫ������ת��ʱ�������ת����ת֮ǰӦ�Ƚ����ж�*/
static Position Rotate(ElementType item, RedBlackTree Parent)
{
	if(item < Parent->Elememt)
		return Parent->left = item<Parent->left->Elememt? 
			rightSingleRotate(Parent->left):
			leftSingleRotate(Parent->left);
	else
		return Parent->right = item <Parent->right->Elememt?
			rightSingleRotate(Parent->right):
			leftSingleRotate(Parent->right);
}

/*�������Ӷ��Ǻ�ɫ�ڵ�ʱ���������׺ͺ��ӽڵ����ɫ���б�Ҫ��ʱ�������ת*/
static void HandleReorient(ElementType item, RedBlackTree T)
{
	X->color = Red;
	X->left->color = Black;
	X->right->color = Black;

	if(P->color == Red)
	{
		GP->color = Red;
		if((item< P->Elememt) != (item < GP->Elememt))
			//P = Rotate(item, GP);
			Rotate(item, GP);

		X = Rotate(item, GGP);
		X->color =Black;

	}
	T->right->color = Black;
}

/*����ڵ㣬����ڵ��Ѿ����ڣ���ʲôҲ����*/
RedBlackTree insert(ElementType item, RedBlackTree T)
{
	X = P =GP = T;
	NullNode->Elememt = item;
	while(X->Elememt != item)
	{
		GGP = GP; GP = P; P =X;
		if(item<X->Elememt)
			X = X->left;
		else
			X = X->right;
		if(X->left->color == Red && X->right->color == Red)
			HandleReorient(item, T);
	}
	if(X != NullNode)
		return NullNode;

	X = (RedBlackTree)malloc(sizeof(struct RedBlackNode));
	X->Elememt = item;
	X->left = X->right = NullNode;
	
	if(item<P->Elememt)
		P->left = X;
	else
		P->right = X;

	HandleReorient(item, T);
	return T;
}



/*������*/
void destroyTree(RedBlackTree T)
{
	if(T != NullNode)
	{
		destroyTree(T->left);
		destroyTree(T->right);
		free(T);
	}
}


RedBlackTree find(ElementType item, RedBlackTree T)
{
	RedBlackTree Parent;
	while(T != NullNode && T->Elememt != item)
	{
		Parent = T;
		if(item <T->Elememt)
			T =T->left;
		else
			T =T->right;
	}
	if(T == NullNode)
		return Parent;
	else
		return T;
}

ElementType findItem(ElementType item);
void solveStep2A23();
void solve2B();
void normalDown(ElementType item);

/*ɾ���ڵ�*/
RedBlackTree Delete(ElementType item, RedBlackTree T)
{
	T->color =Red;
	X= T->right; 
	BRO = T->left;
	GP = GGP = P = T;

	while(X != NullNode)
	{
		/*Setp2���ֳַ�2A����2B*/
		/*Step 2A*/
		if(X->left->color == Black && X->right->color == Black)
		{
			if(BRO->left->color == Black && BRO->right->color == Black)
			{
				/*step 2A1*/
				P->color =Black;
				X->color = Red;
				if(BRO != NullNode)
					BRO->color = Red;
			}
			else 
				/*step 2A23*/
				solveStep2A23(); 
			
			/*���XȾɫΪ��ɫ�����׽ڵ��Ϊ��ɫ*/
			if(X->Elememt == item)
				/*���ǰ���������������ɾ��,��X�Ƿ�ΪNullNode����*/
				item = findItem(item);
			else	
				/*û���ҵ��ڵ�ʱǰ����Ȼ�����step2*/
				normalDown(item);

		}
		/*step 2B*/
		else
		{	
			if(X->Elememt != item)
				/*step 2B,�����½�*/
				normalDown(item);
			
			else
				item = findItem(item);
			
			/*����Ѿ������ɾ������X�����NullNode*/
			if(X == NullNode)
				break;

			/*û�����ɾ�������ʱ�Ѿ�������½�*/
			if(X->color == Black)
				/*�ֵܽڵ��Ȼ�Ǻ�ɫ��������ת����ת֮��X��ɺ�ɫ��BRO��ɺ�ɫ��P��ɺ�ɫ��
				�ص�Step2���ٶ�X���б任�ɺ�ɫ����ɺ�ɫ֮���ٽ����ж�X�Ƿ���Ҫ�ҵĽڵ�*/
				solve2B();
			else if(X->Elememt != item)
				/*��ɫ�����½���X��BRO�������Ǻ�ɫ*/
				normalDown(item);
			else
				item = findItem(item);
		}
	}

	/*Step4�� 3�Ѿ�������������*/
	T->color = Black;
	T->right ->color = Black;

	return T;
}


RedBlackTree DeleteNode(RedBlackTree target, RedBlackTree T)
{
	RedBlackTree origin = T;
	RedBlackTree Parent 
		;
	while(T != target)
	{
		Parent = T;
		if(target->Elememt < T->Elememt)
			T= T->left;
		else
			T = T->right;
	}

	if(T == origin)
	{
		RedBlackTree temp;
		if(T->right != NullNode)	
			temp =T->right;
		else
			temp = T->left;

		free(T);	
		return temp;
	}

	if(Parent->right == T)
	{
		if(T->right != NullNode)
			Parent->right = T->right;
		else
			Parent->right = T->left;
	}
	else
	{
		if(T->right != NullNode)
			Parent->left = T->right;
		else
			Parent->left = T->left;
	}
	free(T);
	return origin;

}

ElementType findItem(ElementType item)
{
	ElementType temp;
	RedBlackTree ToDelete;
	/*�����ҪѰ�ҵĵ㣬���ж��Ƿ���Ҷ�ӽڵ㣬������ͨ���滻�ڵ�ɾ��*/
	if(X->left == NullNode && X->right == NullNode)
	{
		if(P->right == X)
			P->right = NullNode;
		else
			P->left = NullNode;

		free(X);
		X = NullNode;
		temp = item;
	}
	else
	{
		/*����Ҷ�ӽڵ�*/
		if(X->right != NullNode)
		{
			/*���ұ�Ѱ��һ����С�Ľڵ����X��λ����*/
			ToDelete = find(item, X->right);
			X->Elememt = ToDelete->Elememt;
			temp = ToDelete->Elememt;
			if(ToDelete ->color == Red)
			{
				/*����ҵĽڵ��Ǻ�ɫ������ֱ��ɾȥ�ýڵ�*/
				X->right = DeleteNode(ToDelete, X->right);
				X = NullNode;
			}
			else
			{
				/*A2�У�����ǰ��,��ʱ�µ�X��һ���Ǻ�ɫ���ֵ�BROҲһ���Ǻ�ɫ����ʱ�ͻص���step2
				  B2�У���ǰ��,��ʱ�µ�X�������Ǻ�ɫҲ�����Ǻ�ɫ������Ǻ�ɫ�Ļ���һ������ToDelete�ڵ㣬��Ϊ�������Ѿ��ų�����*/
				GP = P; P= X; BRO = P->left;	
				X = X->right;
			}
		}
		else
		{
			/*�����Ѱ��һ�����Ľڵ����X��λ����*/
			ToDelete = find(item, X->left);
			X->Elememt = ToDelete->Elememt;
			temp = ToDelete->Elememt;
			if(ToDelete ->color == Red)
			{
				/*����ҵĽڵ��Ǻ�ɫ������ֱ��ɾȥ�ýڵ�*/
				X->left = DeleteNode(ToDelete, X->left);
				X = NullNode;
			}
			else
			{
				/*����ǰ��,��ʱ�µ�X��һ���Ǻ�ɫ���ֵ�BROҲһ���Ǻ�ɫ����ʱ�ͻص���step2
				B2�У���ǰ��,��ʱ�µ�X�������Ǻ�ɫҲ�����Ǻ�ɫ������Ǻ�ɫ�Ļ���һ������ToDelete�ڵ㣬��Ϊ�������Ѿ��ų�����*/
				GP = P; P= X; BRO = P->right;
				X = X->left;
			}
						
		}

	}

	return temp;
}


void solveStep2A23()
{
	/*�ֵ����ұ�*/
	if(P->left == X)
	{
					
		if(BRO->left->color == Red)
		{
			/*step 2A2*/
			P->color = Black;
			X->color = Red;
			P->right =  rightSingleRotate(BRO);
			if(GP->left == P)
				GP->left = leftSingleRotate(P);
			else
				GP->right = leftSingleRotate(P);
		}
		else
		{
			/*step 2A3*/
			X->color = Red;
			P->color = Black;
			BRO->color = Red;
			BRO->right->color = Black;

			if(GP->right == P)
				GP->right = leftSingleRotate(P);
			else
				GP->left = leftSingleRotate(P);
		}
	}
	/*�ֵ������*/
	else
	{
		if(BRO->right->color == Red)
		{
			/*step 2A2*/
			X->color = Red;
			P->color = Black;
			P->left = leftSingleRotate(BRO);
			if(GP->left == P)
				GP->left = rightSingleRotate(P);
			else
				GP->right = rightSingleRotate(P);
		}
		else
		{
			/*step 2A3*/
			X->color = Red;
			P->color = Black;
			BRO->color = Red;
			BRO->left->color = Black;

			if(GP->right == P)
				GP->right = rightSingleRotate(P);
			else
				GP->left = rightSingleRotate(P);
		}
	}

}

void solve2B()
{
	BRO->color = Black;
	P->color = Red;
	if(P->left == X)
	{
		if(GP->left == P)
			GP->left = leftSingleRotate(P);
		else
			GP->right = leftSingleRotate(P);
		BRO = P->right;
	}
	else
	{
		if(GP->left == P)
			GP->left = rightSingleRotate(P);
		else
			GP->right = rightSingleRotate(P);

		BRO = P->left;
	}

	
}


void normalDown(ElementType item)
{
	if(item<X->Elememt)
	{
		GP = P; P= X; BRO = P->right;
		X= X->left;
	}
	else
	{
		GP = P; P= X; BRO = P->left;
		X = X->right;
	}
}







///*��ΪX������һ����ɫ�ڵ㣬���Բ�����Ҷ�ӽڵ㣬һ���к��ӣ����Ҵ�ʱX�Ǻ�ɫ�Ľڵ�*/
//				if(X->right != NullNode)
//				{
//					/*���ұ�Ѱ��һ����С�Ľڵ����X��λ����*/
//					ToDelete = find(item, X->right);
//					X->Elememt = ToDelete->Elememt;
//					if(ToDelete ->color == Red)
//					{
//						/*����ҵĽڵ��Ǻ�ɫ������ֱ��ɾȥ�ýڵ�*/
//						X->right = DeleteNode(ToDelete, X->right);
//						break;
//					}
//					else
//					{
//						/*����ǰ��,��ʱ�µ�X�������Ǻ�ɫҲ�����Ǻ�ɫ������Ǻ�ɫ�Ļ���
//						һ������ToDelete�ڵ㣬��Ϊ�������Ѿ��ų�����*/
//						X = X->right;
//						/*Ҫɾ���ĵ�ֵ�仯���µ�*/
//						item = ToDelete->Elememt;
//					}
//					
//				}
//				else
//				{
//					/*�����Ѱ��һ�����Ľڵ����X��λ����*/
//					ToDelete = find(item, X->left);
//					X->Elememt = ToDelete->Elememt;
//					if(ToDelete ->color == Red)
//					{
//						/*����ҵĽڵ��Ǻ�ɫ������ֱ��ɾȥ�ýڵ�*/
//						X->left = DeleteNode(ToDelete, X->left);
//						break;
//					}
//					else
//					{
//						/*����ǰ��,��ʱ�µ�X�������Ǻ�ɫҲ�����Ǻ�ɫ������Ǻ�ɫ�Ļ���
//						һ������ToDelete�ڵ㣬��Ϊ�������Ѿ��ų�����*/
//						X = X->left;
//						item = ToDelete->Elememt;
//					}
//				}


///*X�Ǻ�ɫ�����ж��Ƿ���ҪѰ�ҵĵ�,�����½�������Step2�� ��Ϊ��ʱP��ɺ�ɫ��X��T����ɺ�ɫ*/
//				if(X->Elememt == item)
//				{
//					/*�����ҪѰ�ҵĵ㣬���ж��Ƿ���Ҷ�ӽڵ㣬������ͨ���滻�ڵ�ɾ��*/
//					if(X->left == NullNode && X->right == NullNode)
//					{
//						if(P->right == X)
//							P->right = NullNode;
//						else
//							P->left = NullNode;
//
//						free(X);
//					}
//					else
//					{
//						/*����Ҷ�ӽڵ�*/
//						if(X->right != NullNode)
//						{
//							/*���ұ�Ѱ��һ����С�Ľڵ����X��λ����*/
//							ToDelete = find(item, X->right);
//							X->Elememt = ToDelete->Elememt;
//							if(ToDelete ->color == Red)
//							{
//								/*����ҵĽڵ��Ǻ�ɫ������ֱ��ɾȥ�ýڵ�*/
//								X->right = DeleteNode(ToDelete, X->right);
//								break;
//							}
//							else
//							{
//								/*����ǰ��,��ʱ�µ�X��һ���Ǻ�ɫ���ֵ�BROҲһ���Ǻ�ɫ����ʱ�ͻص���step2*/
//								X = X->right;
//								/*Ҫɾ���ĵ�ֵ�仯���µ�*/
//								item = ToDelete->Elememt;
//							}
//						}
//						else
//						{
//							/*�����Ѱ��һ�����Ľڵ����X��λ����*/
//							ToDelete = find(item, X->left);
//							X->Elememt = ToDelete->Elememt;
//							if(ToDelete ->color == Red)
//							{
//								/*����ҵĽڵ��Ǻ�ɫ������ֱ��ɾȥ�ýڵ�*/
//								X->left = DeleteNode(ToDelete, X->left);
//								break;
//							}
//							else
//							{
//								/*����ǰ��,��ʱ�µ�X��һ���Ǻ�ɫ���ֵ�BROҲһ���Ǻ�ɫ����ʱ�ͻص���step2*/
//								X = X->left;
//								item = ToDelete->Elememt;
//							}
//						
//						}