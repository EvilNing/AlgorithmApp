#include <stdlib.h>
#include <stdio.h>

#include "bp_tree.h"
#include "search_db.h"


int main()
{
	BP_Tree* tree=new BP_Tree;

	for ( int i=0 ;i<10000000; ++i )
	{
		tree->insert(i,NULL);

	}

	printf("\n\n||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| \n\n");


	for ( int i=30; i >=0 ; i-- )
	{
		tree->remove(i);
		tree->print();	
		printf("=========================\n");
	}

	printf("\n\n||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| \n\n");

	for ( int i=0 ;i<30; ++i )
	{
		tree->insert(i,NULL);

		tree->print();
		printf("=========================\n");
	}

	return 0;
}
