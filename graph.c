#include "graph.h"
#include<stdio.h>
#include<stdlib.h>
#define infinity 1000000
void deleteGraph_cmd(pnode* head) {
	pnode current = *head;
	while (current != NULL) {
		pedge signaledge = current->edges;
		while (signaledge!= NULL) {
			pedge Redge = signaledge->next;
			free(signaledge);
			signaledge = Redge;
			
		}
		 pnode Rnode = current;
		 current = current->next;
		 free(Rnode);

	}
	 head = NULL;
}
pnode searchNode(pnode *head,int key) {
	pnode search = *head;
	while (search != NULL) {
	
		if (search->node_num == key) {
			return search;
		}
		search = search->next;
	}
	return NULL;
}


void insert_node_cmd(pnode *head) {
	int idSrc, idDest, weight;
	scanf("%d",&idSrc);
	pnode NodeSrc= searchNode(head, idSrc);
	if (NodeSrc== NULL) {
		NodeSrc = (pnode)malloc(sizeof(node));
		if (NodeSrc == NULL) {
			printf("memory for NodeSrc is Error");
			return;
		}
		else {
			NodeSrc->node_num = idSrc;
			NodeSrc->edges = NULL;
			NodeSrc->next = *head;
			*head = NodeSrc;
		}
	}
	else {
		pedge Edge = NodeSrc->edges;
		while (Edge != NULL) {
			pedge temp = Edge->next;
			free(Edge);
			Edge = temp;
		}
		NodeSrc->edges = NULL;

	}
	scanf("%d", &idDest);
	while (idDest !=0&&idDest!=EOF) {
		pnode NodeDest = searchNode(head, idDest);
		if (NodeDest == NULL) {
			NodeDest = (pnode)malloc(sizeof(node));
			if (NodeDest == NULL) {
				printf("memory for NodeDest is Error");
				return;
			}
			else {
				NodeDest->node_num = idDest;
				NodeDest->edges = NULL;
				NodeDest->next = *head;
				*head = NodeDest;
			}
		}
		scanf("%d", &weight);
		if (NodeSrc->edges == NULL) {
			NodeSrc->edges = (pedge)malloc(sizeof(edge));
			if (NodeSrc->edges == NULL) {
				return;
			}
			NodeSrc->edges->endpoint = NodeDest;
			NodeSrc->edges->weight = weight;
			NodeSrc->edges->next = NULL;
		}
		else {
			pedge e = NodeSrc->edges;
			NodeSrc->edges = NodeSrc->edges->next;
			NodeSrc->edges = (pedge)malloc(sizeof(edge));
			if (NodeSrc->edges == NULL) {
				return;
			}
			NodeSrc->edges->endpoint = NodeDest;
			NodeSrc->edges->weight = weight;
			NodeSrc->edges->next = e;

		}

		
		scanf("%d",&idDest);
	}
}

void build_graph_cmd(pnode *head) {
	deleteGraph_cmd(head);
	int sizeNode=1;
	char ch;
	scanf("%d", &sizeNode);
	scanf("%c",&ch);
	while (sizeNode > 0) {
		insert_node_cmd(head);
		sizeNode--;
	}

	
}
void printGraph_cmd(pnode head) {
	pnode temp = head;
	while (temp != NULL)
	{
		printf("The Node is %d -> ", temp->node_num);
		pedge tempEdge = temp->edges;
		while (tempEdge != NULL)
		{
			printf("dest %d  weight for edge: %d-> ", tempEdge->endpoint->node_num, tempEdge->weight);
			tempEdge = tempEdge->next;
		}
		printf("\n");
		temp = temp->next;
	}
}

void delete_node_cmd(pnode *head)
{
	int id;
	scanf("%d", &id);
	pnode temp = *head;
	while (temp != NULL) {//Remove the edges is in the node 
		if (temp->edges != NULL&&temp->edges->endpoint->node_num == id) {
			pedge Redge = temp->edges;
			temp->edges = temp->edges->next;
			free(Redge);

		}
		temp = temp->next;
	}
	pnode current = *head, next = *head;//Remove the node with all the out edges
	next = current->next;
	while (next) {
		if (next->node_num == id) {
			current->next = next->next;
			free(next);
			next = current;

		}
		else {
			current = next;
			next = current->next;
		}
	}
}
int findminNode(pnode *head) {
	pnode temp = *head;
	int minweight = infinity;
	int id = 1;
	while (temp != NULL) {
			if (temp->weight <= minweight&&temp->tag==0) {
				minweight = temp->weight;
				id = temp->node_num;
			}
		
		temp = temp->next;
	}
	return id;
}
void setWeight(pnode *head, int key, int weight) {
	pnode temp = *head;
	while (temp != NULL) {
		if (temp->node_num == key) {
			temp->weight = weight;
		}
		temp = temp->next;
	}
}



void shortsPath_cmd(pnode head) {
	int src, dest;
	scanf("%d", &src);
	scanf("%d", &dest);
	pnode temp = head;
	pnode temp2 = head;
   while (temp != NULL) {
      temp->weight = infinity;//set the weight for Node not for edge.
	  temp->tag = 0;//this for check if visit this node
		temp = temp->next;
	}
	setWeight(&head, src, 0);//set the weight for Node not for edge.
	while (temp2 != NULL) {
		int min = findminNode(&head);
		if (searchNode(&head, min)->edges != NULL) {
			pedge e = searchNode(&head, min)->edges;
			if (e != NULL) {
				while (e != NULL) {
					int currentWeight = searchNode(&head, e->endpoint->node_num)->weight;
					int eWeight = e->weight;
					int srcPlusEdge = searchNode(&head, min)->weight + eWeight;
					if (srcPlusEdge < currentWeight) {
						setWeight(&head,e->endpoint->node_num, srcPlusEdge);
						
					}
					e = e->next;
				}
			}
		}
		searchNode(&head, min)->tag = 1;//visit the node
		temp2 = temp2->next;
	}
	if (searchNode(&head, dest)->weight > 0) {
		printf("Dijsktra shortest path: %d\n", searchNode(&head, dest)->weight);
	}
	else {
		printf("Dijsktra shortest path: -1\n");
	}

}
int shortsPath_cmd2(pnode head,int src ,int dest) {
	pnode temp = head;
	pnode temp2 = head;
	while (temp != NULL) {
		temp->weight = infinity;//set the weight for Node not for edge.
		temp->tag = 0;//this for check if visit this node
		temp = temp->next;
	}
	setWeight(&head, src, 0);//set the weight for Node not for edge.
	while (temp2 != NULL) {
		int min = findminNode(&head);
		if (searchNode(&head, min)->edges != NULL) {
			pedge e = searchNode(&head, min)->edges;
			if (e != NULL) {
				while (e != NULL) {
					int currentWeight = searchNode(&head, e->endpoint->node_num)->weight;
					int eWeight = e->weight;
					int srcPlusEdge = searchNode(&head, min)->weight + eWeight;
					if (srcPlusEdge < currentWeight) {
						setWeight(&head, e->endpoint->node_num, srcPlusEdge);

					}
					e = e->next;
				}
			}
		}
		searchNode(&head, min)->tag = 1;//visit the node
		temp2 = temp2->next;
	}
	return searchNode(&head, dest)->weight;
	
}
void TSP_cmd(pnode head) {
	int sizeTsp;
	int *arr;
	scanf("%d", &sizeTsp);
	arr= (int*)malloc(sizeTsp * sizeof(int));
	if (arr == NULL) {
		return;
	}
	int i =0;
	while (i< sizeTsp) {
		scanf("%d", &arr[i]);
		i++;
	}
	int sum=0;
	for (i = 0; i < sizeTsp-1; i++) {
		sum += shortsPath_cmd2(head, arr[i], arr[i + 1]);
	}
	printf("TSP shortest path: %d\n", sum);
	free(arr);
}

