#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;;

typedef struct edge_ {
	int weight;
	pnode endpoint;
	struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
	int node_num;
	int weight;
	int tag;
	pedge edges;
	struct GRAPH_NODE_ *next;
} node, *pnode;
void setWeight(pnode *head, int key, int weight);
int findminNode(pnode *head);
void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
pnode searchNode(pnode *head, int key);
int shortsPath_cmd2(pnode head, int src, int dest);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
void shortsPath_cmd(pnode head);
void TSP_cmd(pnode head);

#endif
