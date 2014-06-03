#ifndef  __BP_TREE_H__
#define __BP_TREE_H__

#include <vector>
#include <algorithm>

struct Value
{
	int     len;   
	void* value;
};

struct Record
{
	int       key;
	Value* value;
};

struct Node
{
	Node*    parent;
	int          count;
	bool       is_leaf;

	std::vector<Node*>   children_node;  //���ӽڵ�
	std::vector<Record*> node_record;    //���ڵ������  value����Ϊ��
};

struct Meta
{
	int  degree; 
	int  height;
	int  inner_node_num;
	int  leaf_node_num;

	int key_size;
	int value_size;

	Node*  root;  //root�ڵ�
};



class BP_Tree
{
public:
	BP_Tree();
	~BP_Tree();

	int  init_meta();
	int  insert(int key, Value* value);

private:
	Node* create_node(Node* parent, bool is_leaf);
	Node* search_node(int key);
	Node* search_leaf(Node* parent, int key);

	Meta*  m_meta;

private:

	int insert_to_leaf_no_split(Node* leaf, int key, Value* value);
	int insert_to_index(Node* node, int key);
	int insert_to_index_no_split(Node* index, int key);
	int reset_index_children_parent(Node* node);
};



#endif