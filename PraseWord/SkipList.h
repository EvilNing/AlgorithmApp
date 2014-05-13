//SkipList��ʵ�� �ο�������ַ
//http://www.cnblogs.com/xuqiang/archive/2011/05/22/2053516.html
#ifndef  __SKIP_LIST_H__
#define __SKIP_LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int kMaxLevel=8;


template<class V>
struct ListNode
{
	int   key;
	V   value;
	ListNode** next;         //һ��һά����
};

template<class V>
class EqualChanger
{
public:
	bool operator()(V& dest,V& src)
	{
		dest=src;
		return true;
	}
};

template<class T>
class SkipListIterator
{
public:
	SkipListIterator(T* value=NULL){ m_value=value; };

	T& operator*() const{return *m_value;};
	T*  operator->() const{return m_value;};

	SkipListIterator& operator++()
	{  //ǰ��
		m_value=m_value->next[0];
		return *this;
	}
	//SkipListIterator& operator++(int)
	//{  //����
	//	T* tmp=m_value;
	//	m_value=m_value->next[0];
	//	return *this;
	//}

	bool operator==(SkipListIterator& other){return m_value->key==other->key; }
	bool operator!=(SkipListIterator& other){ return m_value->key!=other->key;}

protected:
	T* m_value;
};


template<class V, class Changer>
class SkipList
{
public:
	explicit SkipList(Changer changer);
	~SkipList(void);

	bool  add_node(int key, V value);
	bool  search_node(int key, V* value);
	bool  delete_node(int key);
	
	typedef SkipListIterator<ListNode<V>>  iterator;
	iterator  begin(){ return m_begin; };
	iterator  end(){ return m_end; };

private:
	ListNode<V>*  create_node(int key, V value, int level);
	void          create_list();
	int            rand_level();

	ListNode<V>*      m_header;
	ListNode<V>*      m_nil;
	
	iterator m_begin;
	iterator m_end;

	Changer               m_changer_func;
	unsigned int  m_level;
};

template<class V, class Changer>
SkipList<V,Changer>::SkipList(Changer changer):m_changer_func(changer)
{
	srand(time(0));
	m_level=0;
	create_list();
	m_begin= m_nil;
	m_end=m_nil;
}

template<class V,class Changer>
SkipList<V,Changer>::~SkipList(void)
{

}

template<class V,class Changer>
void SkipList<V,Changer>::create_list()
{
	m_nil=new ListNode<V>;
	m_nil->key=0x7fffffff; //int ���ֵ
	m_nil->value=0;
	m_nil->next=0;

	m_header=create_node(0,0, kMaxLevel);
	for ( int i=0; i<kMaxLevel; i++ )
	{
		m_header->next[i]=m_nil;
	}
}

template<class V,class Changer>
bool  SkipList<V,Changer>::add_node(int key, V data)
{
	//��ȡ����λ������update
	ListNode<V>*  update[kMaxLevel];

	ListNode<V>*  p=m_header;
	ListNode<V>*  q;

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
		m_changer_func(q->value, data);
		//q->value=data;
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
	ListNode<V>* node=create_node(key,data,cur_level);
	for ( ; cur_level>=0 ; --cur_level )
	{
		p=update[cur_level];
		node->next[cur_level]=p->next[cur_level];
		p->next[cur_level]=node;
	}
	m_begin=m_header->next[0];
	return true;
}

template<class V,class Changer>
bool SkipList<V,Changer>::search_node(int key, V* value)
{
	ListNode<V>* q;
	ListNode<V>* p=m_header;
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

template<class V,class Changer>
bool  SkipList<V,Changer>::delete_node(int key)
{
	ListNode<V>* aim;  // Ҫɾ����Ŀ��node
	ListNode<V>* p=m_header;
	ListNode<V>* update[kMaxLevel];
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
		m_begin=m_header->next[0];
		return true;
	}
	else
	{
		return false;
	}
}

template<class V,class Changer>
ListNode<V>*  SkipList<V,Changer>::create_node(int key, V data, int level)
{
	ListNode<V>* node=new ListNode<V>();
	node->key=key;
	m_changer_func(node->value, data);
	node->next=new ListNode<V>*[level];
	return node;
}

template<class V,class Changer>
int  SkipList<V,Changer>::rand_level()
{
	int level=0;
	while( (rand()%2) )level++;
	level=level>(kMaxLevel-1)?(kMaxLevel-1):level;
	return level;
}


#endif // !__SKIP_LIST_H__
