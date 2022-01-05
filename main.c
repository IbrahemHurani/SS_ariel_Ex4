#include"graph.h"
#include<stdio.h>
int main()
{   
	pnode head =NULL ;
	char select;
		while(scanf("%c", &select)!=EOF){
		switch (select)
		{
		case 'A': {
			build_graph_cmd(&head);
			break;
		}
		case'B': {
			insert_node_cmd(&head);
			break;
		}
		case 'D': {
			delete_node_cmd(&head);
			break;
		}
		case'S':
		{ 
			shortsPath_cmd(head);
			break;
		}
		case 'T':{
			 TSP_cmd(head);
			break;
		}

		}

	}
	//printGraph_cmd(head);
	deleteGraph_cmd(&head);
	return 0;
}
