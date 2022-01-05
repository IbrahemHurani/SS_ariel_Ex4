#include"graph.h"
#include<stdio.h>
int main()
{
	pnode head = NULL;
	char select;
	while (scanf("%c", &select) !=EOF) {
	    if(select=='A'){
			build_graph_cmd(&head);
		}
		if(select=='B'){
			insert_node_cmd(&head);
		  }
		if(select=='D'){
			delete_node_cmd(&head);
	
		}
		if(select=='S'){
			shortsPath_cmd(head);
		}
	
		if(select=='T'){
			TSP_cmd(head);
		}
		else{
			break;
		}
		
	}
	//printGraph_cmd(head);
	deleteGraph_cmd(&head);
	return 0;
}
