#include <iostream>
#include <queue>

using namespace std;

#define MAX_VER		100
#define	MAX 		100
//
typedef struct vertex {
	int num;
	int data;
}Gnode;

typedef struct graph {
	int n;
	int e;
	Gnode ver[MAX_VER];
	int edge[MAX_VER][MAX_VER];
}Graph;


int create_graph_for_dijkstra(Graph * G)
{
	assert(G != NULL);
	memset(G, 0, sizeof(Graph));

	int i = 0;
	G->n = 4;
	G->e = 5;
	for(i = 0; i < G->n; i++)
	{
		G->ver[i].num = i;
		G->ver[i].data = i + 1;
	}

	G->edge[0][0] = 0;
	G->edge[0][1] = MAX;
	G->edge[0][2] = 3;
	G->edge[0][3] = MAX;
	G->edge[1][0] = 2;
	G->edge[1][1] = 0;
	G->edge[1][2] = MAX;
	G->edge[1][3] = MAX;
	G->edge[2][0] = MAX;
	G->edge[2][1] = 7;
	G->edge[2][2] = 0;
	G->edge[2][3] = 1;
	G->edge[3][0] = 6;
	G->edge[3][1] = MAX;
	G->edge[3][2] = MAX;
	G->edge[3][3] = 0;
}

struct node
{
	int id;	//顶点id
	int weight;		//顶点到起始点的距离
	friend bool operator<(node a, node b) //实现最小堆所需
	{
		return a.weight < b.weight;
	}
};

void dijkstra(Graph *G, int s)	//s :源节点的num
{
	for()
}

