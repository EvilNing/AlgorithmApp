#include <stdlib.h>
#include <stdio.h>

#include "bp_tree.h"


void  test()
{
	std::vector<int>  aa;

	if(aa.begin()==aa.end());
		printf("====");

	//for ( int i=0; i<10; i++ )
	//{
	//	std::vector<int>::iterator iter=std::upper_bound(aa.begin(), aa.end(), i);
	//	aa.insert(iter, i);
	//}

	//std::vector<int>::iterator iter=std::upper_bound(aa.begin(), aa.end(), 10);
//	aa.insert(iter, 10);

	return ;
}



int main()
{
	test();
	BP_Tree* tree=new BP_Tree;
	tree->init_meta();

	for ( int i=0 ;i<30; ++i )
	{
		tree->insert(i,NULL);

		tree->print_tree();
		printf("=========================\n");
	}
	tree->print_tree();

	printf("\n\n||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| \n\n");


	for ( int i=30; i >=0 ; i-- )
	{
		tree->remove(i);
		tree->print_tree();	
	}

	return 0;
}
