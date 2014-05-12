#include "SkipList.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int kMaxLevel=8;

SkipList::SkipList(void)
{
	srand(time(0));
	m_level=0;
	create_list();
}


SkipList::~SkipList(void)
{

}

void SkipList::create_list()
{
	m_nil=new ListNode;
	m_nil->key=0x7fffffff; //int ���ֵ
	m_nil->value=0;
	m_nil->next=0;
	
	m_header=create_node(0,0, kMaxLevel);
	for ( int i=0; i<kMaxLevel; i++ )
	{
		m_header->next[i]=m_nil;
	}
}

bool  SkipList::add_node(int key, void* data)
{
	//��ȡ����λ������update
	ListNode*  update[kMaxLevel];

	ListNode*  p=m_header;
	ListNode*  q;

	int cur_level=m_level;	
	for ( ;cur_level>=0; --cur_level )
	{
		while ( q=p->next[cur_level], q->key<key )
		{
			p=q;
		}
		update[cur_level]=p;
	}
	
	//�Ѿ�����
	if ( q->key==key )
	{
		q->value=data;
		return false;
	}

	//�������һ����
	cur_level=rand_level();
	if ( cur_level>m_level )
	{
		cur_level=++m_level;
		update[cur_level]=m_header; //��header�ĺ����������
	}

	//���ɽڵ�
	ListNode* node=create_node(key,data,cur_level);
	for ( ; cur_level>=0 ; --cur_level )
	{
		p=update[cur_level];
		node->next[cur_level]=p->next[cur_level];
		p->next[cur_level]=node;
	}

	return true;
}

bool SkipList::search_node(int key, void** value)
{
	ListNode* q;
	ListNode* p=m_header;
	int  cur_level=m_level;

	for ( ; cur_level>=0 ; --cur_level  )
	{
		while ( q=p->next[cur_level], q->key<key )
		{
			p=q;
		}
	}
	if ( q->key==key )
	{
		*value=q->value;
		return true;
	}
	else
	{
		value=NULL;
		return false;
	}
}

bool  SkipList::delete_node(int key)
{
	ListNode* aim;  // Ҫɾ����Ŀ��node
	ListNode* p=m_header;
	ListNode* update[kMaxLevel];
	int cur_level=m_level;

	// ��ȡupdate����
	for ( ; cur_level>=0 ; --cur_level )
	{
		while ( aim=p->next[cur_level] ,aim->key < key )
		{
			p=aim;
		}
		update[cur_level]=p;
	}

	if ( aim->key==key )
	{   //�ҵ���ɾ��
		for (cur_level=0; cur_level<m_level&&((p=update[cur_level])->next[cur_level]==aim); ++cur_level )
		{
			p->next[cur_level]=aim->next[cur_level];
		}
		delete p->value;
		delete p;

		//ά������߶�
		cur_level=m_level;
		while ( m_header->next[cur_level]==m_nil&&cur_level>0 )
		{
			cur_level--;
		}
		m_level=cur_level;
		return true;
	}
	else
	{
		return false;
	}
}

ListNode*  SkipList::create_node(int key, void* data, int level)
{
	ListNode* node=new ListNode;
	node->key=key;
	node->value=data;
	node->next=new ListNode*[level];
	return node;
}

int  SkipList::rand_level()
{
	int level=1;
	while( (rand()%2) )level++;
	level=level>kMaxLevel?kMaxLevel:level;
	return level;
}

