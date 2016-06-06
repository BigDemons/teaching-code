#define _CRT_SECURE_NO_WARNINGS 1

#pragma once

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef int DataType;
typedef struct LinkNode
{
	DataType data;
	struct LinkNode *next;
}LinkNode,*pLinkNode,*pList;

void InitList(pList* pplist);
void DestroyList(pList *pplist);
void PrintList(pList head);
int GetListLength(pList head);

void PushBack(pList *pplist, DataType x);
void PopBack(pList *pplist);

void PushFront(pList *pplist, DataType x);
void PopFront(pList *pplist);

pLinkNode Find(pList head, DataType x);
void Insert(pList *pplist, pLinkNode pos, DataType x);
void Remove(pList *pplist, DataType x);
void RemoveAll(pList *pplist, DataType x);
void Erase(pLinkNode *pplist, pLinkNode pos);

// �������������

//ɾ����β�ڵ�-----1
void EraseNotTail(pLinkNode pos);

//��ת����������--2
void ReverseList(pList* pplist);

//��������ð�ݣ�--3
void BubbleSort(pList * pplist);

// ɾ����β���----4
void DelNonTailNode(pLinkNode pos);

// �ڵ�ǰ�ڵ�ǰ����һ������x-----5
void InsertFrontNode(pLinkNode pos, DataType x);

//�ϲ����������б�-----6
pLinkNode Merge(pList l1, pList l2);

//����������м�ڵ�---7
pLinkNode FindMidNode(pList head);

// ɾ��������ĵ�����k���ڵ�(k > 1 && k < ������ܳ���)----8
// ʱ�临�Ӷ�O(N)
void DelKNode(pList *pplist, int k);

// ������������⡿-----9
// �ж������Ƿ����, ������������󻷵ĳ��Ⱥ������ڵ㣬����������-1
pLinkNode CheckCycle(pList pList);
int GetCircleLength(pLinkNode meet);
//FindEntryNode()
// ��ȡ����ڵ�
pLinkNode GetCycleEntryNode(pList list, pLinkNode meetNode);

// �������ཻ���⡿
//
// �ж����������Ƿ��ཻ����������������������
// �󻷵Ľ��㣬����������n����nΪ������ĳ��Ȳ��Ȼ����һ���ߣ���һ����������Ϊ���㡣
//
int CheckCross(pList list1, pList list2);


/*����ʵ����ع���*/

void InitList(pList* pplist)
{
	assert(pplist);
	*pplist = NULL;
}

void DestroyList(pList *pplist)
{
	pLinkNode cur = *pplist;
	assert(pplist);

	while (cur)
	{
		pLinkNode del = cur;//�ȱ��潫Ҫ����Ҫɾ���Ľڵ�
		cur = cur->next;
		free(del);
		del = NULL;
	}
	*pplist = NULL;
}

void PrintList(pList head)
{
	pLinkNode cur = head;
	printf("list :");

	while (cur)
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("over\n");
}

int GetListLength(pList head)
{
	pLinkNode cur = head;
	int count = 0;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	return count;
}

pLinkNode BuyNode(DataType x)
{
	pLinkNode newNode = (pLinkNode)malloc(sizeof(LinkNode));
	if (newNode == NULL)
	{
		printf("out of memory\n");
		exit(EXIT_FAILURE);
	}
	newNode->data = x;
	newNode->next = NULL;
	return newNode;
}

void PushBack(pList *pplist, DataType x)
{
	pLinkNode newNode = NULL;
	assert(pplist);
	newNode = BuyNode(x);
	//û�нڵ�
	if (*pplist == NULL)
	{
		*pplist = newNode;
	}
	else//��һ�������Ͻڵ�
	{
		pLinkNode cur = *pplist;
		while (cur->next)
		{
			cur = cur->next;
		}
		cur->next = newNode;
	}
}

void PopBack(pList *pplist)
{
	assert(pplist);
	//û�нڵ�
	if (*pplist == NULL)
	{
		return;
	}
	else if ((*pplist)->next == NULL)//��һ���ڵ�
	{
		free(*pplist);
		*pplist = NULL;
		return;
	}
	else//�������Ͻڵ�
	{
		pLinkNode cur = *pplist;
		while (cur->next->next != NULL)
		{
			cur = cur->next;
		}
		free(cur->next);
		cur->next = NULL;
	}
}

void PushFront(pList *pplist, DataType x)
{
	pLinkNode newNode = BuyNode(x);
	assert(pplist);
	if (*pplist == NULL)
	{
		*pplist = newNode;
	}
	else
	{
		newNode->next = *pplist;
		*pplist = newNode;
	}
}

void PopFront(pList *pplist)
{
	assert(pplist);
	if (*pplist == NULL)
	{
		return;
	}
	else
	{
		pLinkNode del = *pplist;
		*pplist = (*pplist)->next;
		free(del);
	}
}

pLinkNode Find(pList plist,DataType x)
{
	pLinkNode begin = plist;

	while (begin)
	{
		if (begin->data == x)
		{
			return begin;
		}
		begin = begin->next;
	}
	return NULL;
}
//ָ��λ��֮�����һ������
void Insert(pList *pplist, pLinkNode pos, DataType x)
{
	pLinkNode newNode = BuyNode(x);
	assert(pplist);
	assert(pos);
	//û�нڵ� 
	if (*pplist == NULL)
	{
		*pplist = newNode;
	}
	else//һ���ڵ�����
	{
		newNode->next = pos->next;
		pos->next = newNode;
	}
}

void Remove(pList *pplist, DataType x)
{
	pLinkNode begin = *pplist;
	pLinkNode prev = NULL;
	assert(pplist);
	while (begin)
	{
		if (begin->data == x)//����ҵ���
		{
			pLinkNode del = begin;

			if ((*pplist) == begin)//�ǵ�һ���ڵ�
			{
				*pplist = (*pplist)->next;
			}
			else//�ǵ�һ���ڵ�
			{
				prev->next = begin->next;
			}
			free(del);
			return;
		}
		prev = begin;
		begin = begin->next;
	}
}

void RemoveAll(pList *pplist, DataType x)
{
	pLinkNode begin = *pplist;
	pLinkNode prev = NULL;
	assert(pplist);
	while (begin)
	{
		if (begin->data == x)//�ҵ���
		{
			pLinkNode del = begin;

			if ((*pplist) == begin)//�ǵ�һ���ڵ�
			{
				*pplist = (*pplist)->next;
				begin = *pplist;
			}
			else//�ǵ�һ���ڵ�
			{
				prev->next = begin->next;
				begin = prev->next;//����begin
			}
			free(del);
		}
		else//�Ҳ�����������
		{
			prev = begin;
			begin = begin->next;
		}
	}
}

void Erase(pLinkNode *pplist, pLinkNode pos)
{
	pLinkNode prev = *pplist;
	assert(pplist);

	while (prev && prev->next != pos)
	{
		prev = prev->next;
	}

	if (prev != NULL)
	{
		pLinkNode del = pos;
		prev->next = pos->next;
		free(del);
	}
}

//ɾ����ͷ������ķ�β���--
void EraseNotTail(pLinkNode pos)
{
	assert(pos->next);//���Ϊβ�ڵ�Ͷ���ʧ�ܣ�����
	pLinkNode del = pos->next;
	pos->data = pos->next->data;
	pos->next = pos->next->next;
	free(del);
	del = NULL;
}

// �������������

//��ת����������
void ReverseList(pList* pplist)
{
	assert(pplist);
	if ((*pplist == NULL) || ((*pplist)->next == NULL))//û�нڵ��ֻ��һ���ڵ�
	{
		return;
	}
	pLinkNode cur = *pplist;
	pLinkNode tmp = NULL;
	pLinkNode newHead = NULL;
	while (cur != NULL)//ͷժ��ͷ��
	{
		tmp = cur;
		cur = cur->next;
		tmp->next = newHead;
		newHead = tmp;	
	}
	*pplist = newHead;
}

//��������ð�ݣ�
void BubbleSort(pList * pplist)
{
	pLinkNode start = *pplist;
	pLinkNode tail = NULL;
	while (*pplist != tail)
	{
		while (start->next != tail)
		{
			if (start->data > start->next->data)
			{
				DataType tmp = start->data;
				start->data = start->next->data;
				start->next->data = tmp;
			}
			start = start->next;
		}
		tail = start;
		start = *pplist;
	}
}

// ����ͷ�������һ���ڵ�ǰ����һ������x
void InsertFrontNode(pLinkNode n, DataType x)
{
	assert(n);
	pLinkNode newNode = BuyNode(x);
	DataType tmp;

	//����ǰλ�õĺ��
	newNode->next = n->next;
	n->next = newNode;

	//��������
	tmp = n->data;
	n->data = newNode->data;
	newNode->data = tmp;
}

//�ϲ����������б�(�ǵݹ�ʵ��)
pLinkNode Merge(pList list1, pList list2)
{
	pList newList = NULL;
	pList begin1 = list1;
	pList begin2 = list2;
	pLinkNode tail = NULL;
	// �������������ͬ������ϲ���ֱ�ӷ���
	if (list1 == list2)
	{
		return list1;
	}
	// ������һ������Ϊ�գ��򷵻���һ������
	if (list1 == NULL)
	{
		return list2;
	}
	if (list2 == NULL)
	{
		return list1;
	}

	if (begin1->data > begin2->data)
	{
		newList = begin2;
		begin2 = begin2->next;
	}
	else
	{
		newList = begin1;
		begin1 = begin1->next;
	}

	//�ҽ�С������β��
	tail = newList;

	while (begin1 && begin2)
	{
		if (begin1->data > begin2->data)
		{
			tail->next = begin2;
			begin2 = begin2->next;
			tail = tail->next;
		}
		else
		{
			tail->next = begin1;
			begin1 = begin1->next;
			tail = tail->next;
		}
	}
	//ʣ�������׷��
	if (begin1)
	{
		tail->next = begin1;
	}
	else
	{
		tail->next = begin2;
	}

	return newList;
}


pLinkNode _Merge(pList list1, pList list2)
{
	pList newList = NULL;
	pList begin1 = list1;
	pList begin2 = list2;
	pLinkNode tail = NULL;
	// �������������ͬ������ϲ���ֱ�ӷ���
	if (list1 == list2)
	{
		return list1;
	}
	// ������һ������Ϊ�գ��򷵻���һ������
	if (list1 == NULL)
	{
		return list2;
	}
	if (list2 == NULL)
	{
		return list1;
	}

	if (begin1->data > begin2->data)
	{
		newList = begin2;
		//newList->next = _Merge(begin2->next, begin1);
		newList->next = _Merge(begin1, begin2->next);
	}
	else
	{
		newList = begin1;
		newList->next = _Merge(begin2, begin1->next);
	}

	return newList;
}

//
// Լɪ�򻷣�Լɪ�����⣩��һ����ѧ��Ӧ�����⣺
// ��֪n���ˣ��Ա��1��2��3...n�ֱ��ʾ��Χ����һ��//Բ����Χ��
// �ӱ��Ϊk���˿�ʼ����������m���Ǹ��˳��У�������һ�����ִ�1��ʼ����������m���Ǹ���
// �ֳ��У����˹����ظ���ȥ��ֱ��Բ����Χ����ȫ�����С�
//
pLinkNode JosephCycle(pList * pplist, int num)
{
	assert(pplist);
	
	pLinkNode cur = *pplist;
	while (1)
	{
		int count = num;
		if (cur->next == cur)//ʣһ���˵�ʱ��ͣ����
		{
			break;
		}
		pLinkNode del = NULL;
		while (--count)//����
		{
			cur = cur->next;
		}
		printf("del:%d\n", cur->data);
		del = cur->next;//������ɾ����ǰ�ڵ�
		cur->data = cur->next->data;
		cur->next = cur->next->next;
		free(del);
		del = NULL;
	}
	return cur;
}

pLinkNode FindMidNode(pList head)
{
	if (head == NULL)
	{
		return NULL;
	}
	pLinkNode fast = head;
	pLinkNode slow = head;
	//��fastΪNULL,������ڵ���Ϊż����
	//��fast->nextΪNULL,������Ľڵ���Ϊ������
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}


//ɾ���ڵ���K���ڵ�
void DelKNode(pList *pplist, int k)
{
	pLinkNode slow = *pplist;
	pLinkNode fast = *pplist;
	assert(k > 1);
	
	if (*pplist == NULL)
	{
		return;
	}
	while (fast)
	{
		if (--k < 0)
		{
			slow = slow->next;
		}
		fast = fast->next;
	}

	if (k < 0)
	{
		pLinkNode del = slow->next;
		slow->data = slow->next->data;
		slow->next = slow->next->next;
		free(del);
	}
}


// ������������⡿-----10
// �ж������Ƿ����, ������������󻷵ĳ��Ⱥ������ڵ㣬����������NULL
pLinkNode CheckCycle(pList pList)
{
	int ret = 0;
	int len = 0;
	pLinkNode fast = pList;
	pLinkNode slow = pList;
	pLinkNode last = NULL;
	while (fast && fast->next)
	{
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow)
		{
			return slow;
		}
	}
	return NULL;
}

int GetCircleLength(pLinkNode meet)
{
	pLinkNode cur = meet;
	meet = meet->next;
	int count = 1;
	while (meet != cur)
	{
		meet = meet->next;
		count++;
	}
	return count;
}

// ��ȡ����ڵ�
pLinkNode GetCycleEntryNode(pList list, pLinkNode meetNode)
{
	assert(meetNode);

	pLinkNode start = list;
	pLinkNode entry = meetNode;
	while (entry != start)
	{
		entry = entry->next;
		start = start->next;
	}
	return entry;
}


// ��ȡ����ڵ�(ת��Ϊ�����ཻ����)
pLinkNode GetCycleEntryNode2(pList list, pLinkNode meetNode)
{
	assert(meetNode);

	pLinkNode start1 = list;
	pLinkNode start2 = meetNode;
	pLinkNode entry = meetNode;
	pLinkNode end = meetNode;
	int len1 = 1;
	int len2 = 1;
	while (start1->next != end)
	{
		len1++;
		start1 = start1->next;
	}
	while (start2->next != end)
	{
		len2++;
		start2 = start2->next;
	}
	int count = (len1 > len2 ? len1 - len2 : len2 - len1);
	start1 = list;
	start2 = meetNode;

	if (len1 > len2)
	{
		while (--count)
		{
			start1 = start1->next;
		}
	}
	else
	{
		while (--count)
		{
			start2 = start2->next;
		}
	}
	while (start1 != start2)
	{
		start1 = start1->next;
		start2 = start2->next;
	}
	entry = start1;
	return entry;
}

//
// �������ཻ���⡿
//
// �ж����������Ƿ��ཻ����������������������
//
int CheckCross(pList list1, pList list2)
{
	assert(list1);
	assert(list2);

	pLinkNode end1= 0;
	pLinkNode end2 = 0;

	while (list1)
	{
		end1 = list1;
		list1 = list1->next;
	}
	while (list2)
	{
		end2 = list2;
		list2 = list2->next;
	}
	if (end1 == end2)
	{
		return 1;
	}
	return 0;
}


