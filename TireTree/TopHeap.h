#ifndef   __TOP_HEAP_H__
#define  __TOP_HEAP_H__

#include <vector>


//���
template<class T, class Comparator>
class TopHeap
{
public:
	explicit TopHeap(Comparator comp);
	~TopHeap(void);

	int    GetTop(int count, T* data);
	void  Add(T data);
	void  PrintHeap();

private:

	void  SiftupNode(int index);
	void  SiftdownNode(int index);

	int   left_child(int index);
	int   right_child(int index);
	int   node_parent(int index);
	int   node_value(int index);
	void swap_node(int index1, int index2);

	int               m_node_count;
	std::vector<T> m_array;
	Comparator  m_compare;
};

template<class T, class Comparator>
TopHeap<T,Comparator>::TopHeap(Comparator comp):m_compare(comp)
{

}

template<class T, class Comparator>
TopHeap<T,Comparator>::~TopHeap(void)
{

}

template<class T, class Comparator>
int  TopHeap<T,Comparator>::GetTop(int count, T* data)
{
	count=count>m_array.size()?m_array.size():count;
	for ( int i=0 ;i <count; i++ )
	{
		data[i]=m_array[0]; //���ֵ
		m_array[0]=m_array[m_array.size()-1];
		m_array.pop_back();
		SiftdownNode(0);
	}

	return 0;
}

template<class T, class Comparator>
void  TopHeap<T,Comparator>::Add(T data)
{
	m_array.push_back(data);
	SiftupNode(m_array.size()-1);
}

template<class T, class Comparator>
void TopHeap<T,Comparator>::PrintHeap()
{
	int  count=0;
	int  layer=0;
	for ( int i=0; i<m_array.size(); i++ )
	{ 
		count++;
		printf("%d ", m_array[i]);

		if ( count==pow(2,layer) )
		{
			count=0;
			layer++;
			printf("\n");
		}
	}
}


template<class T, class Comparator>
void TopHeap<T,Comparator>::SiftupNode(int index)
{
	int i=index;
	while ( i>0 )
	{
		if ( m_compare(m_array[i], m_array[node_parent(i)]) )
		{
			swap_node(i, node_parent(i) );
		}
		else
		{
			break;
		}
		i=node_parent(i);
	}

}

template<class T, class Comparator>
void TopHeap<T,Comparator>::SiftdownNode(int index)
{
	int i=index;
	int array_count=m_array.size();

	while (i<m_array.size())
	{
		if ( left_child(i)==0 ) //���Ӵ���
		{
			break;
		}

		if ( right_child(i)!=0 ) //�Һ��Ӵ���
		{
			int node=m_compare(m_array[left_child(i)],m_array[right_child(i)] )?left_child(i) : right_child(i);
			if ( m_compare(m_array[node] , m_array[i]) )
			{
				swap_node(i, node);
				i=node;
			}
			else
			{
				break;
			}
		}
		else
		{
			if ( m_compare(m_array[i] , m_array[left_child(i)]) )
			{
				break;
			}
			else
			{
				swap_node( i, left_child(i) );
				i=left_child(i);
			}
		}

	}
}

template<class T, class Comparator>
int TopHeap<T,Comparator>::left_child(int index)
{
	if ( index*2+1>m_array.size()-1 )
	{
		return 0;
	}
	return index*2+1;
}

template<class T, class Comparator>
int TopHeap<T,Comparator>::right_child(int index)
{
	if ( (index+1)*2>m_array.size()-1 )
	{
		return 0;
	}
	return (index+1)*2;
}

template<class T, class Comparator>
int TopHeap<T,Comparator>::node_parent(int index)
{
	return (index-1)/2;
}

template<class T, class Comparator>
int  TopHeap<T,Comparator>::node_value(int index)
{
	return m_array[index];
}

template<class T, class Comparator>
void TopHeap<T,Comparator>::swap_node(int index1, int index2)
{
	int temp=m_array[index1];
	m_array[index1]=m_array[index2];
	m_array[index2]=temp;
}




#endif  

