#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

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


/*
 *     A  B  C  D  E
 *	A  0  1  0  0  0
 *	B  0  0  1  0  0
 *	C  0  0  0  1  0
 *	D  0  0  0  0  0
 *	E  0  0  0  0  0
 */
int create_graph(Graph *G)
{
	if(G == NULL)
	{
		return - 1;
	}
	memset(G, 0, sizeof(Graph));

	int i = 0;
	G->n = 5; 
	G->e = 3;
	for( i = 0; i < G->n; i++)
	{
		G->ver[i].num = i;
		G->ver[i].data = i + 1;
	}
	G->edge[0][1] = 1;
	G->edge[1][2] = 1;
	G->edge[2][3] = 1;

	return 0;
}

int create_graph_for_floyd(Graph * G)
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

int print_graph(Graph *G)
{
	int i, j;
 	printf("图的邻接矩阵如下:\n");
 	printf("   ");
 	for(i=0;i<G->n;i++)
 	 printf("%3c",'A' + i);printf("\n");
 	for(i=0;i<G->n;i++)
 	{
  		printf("%3c",'A' + i);
  		for(j=0;j<G->n;j++)
   		printf("%3d",G->edge[i][j]);
  		printf("\n");
 	}
 	return 0;
}

//DFS

int dfs_exist[MAX_VER] = {0};

void dfs(Gnode v, Graph *G)
{
	assert(G != NULL);
	dfs_exist[v.num] = 1;
	printf(" %3c",  'A'+ v.num);
	int i = 0;
	for(i = 0; i < G->n; i++)
	{
		if(G->edge[v.num][i] == 1 && dfs_exist[i] == 0)
		{
			dfs(G->ver[i], G);
		}
	}
}

int search_graph_dfs(Graph *G)
{
	if(G == NULL)
	{
		return -1;
	}

	int i = 0;
	for(i = 0 ; i < G->n; i++)
	{
		if(dfs_exist[i] == 0)
		{
			dfs(G->ver[i], G);
		}
	}
	return 0;
}


//BFS
typedef Gnode TYPE;
typedef struct _queue
{
	int front;
	int end;
	TYPE data[MAX_VER];
}Queue;



int  is_queue_empty(Queue * Q)
{
	assert(Q != NULL);
	if(Q->front == Q->end)
	{
		return 1;
	}
	return 0;
}

int is_queue_full(Queue *Q)
{
	assert(Q != NULL);
	if((Q->end + 1) % MAX_VER == Q->front)
	{
		return 1;
	} 
	return 0;
}

Queue * queue_init()
{
	Queue * queue = (Queue *)malloc(sizeof(Queue));
	assert(queue != NULL);
	memset(queue, 0, sizeof(Queue));
	queue->front = queue->end = 0;

	return queue;
}

int queue_push(TYPE node, Queue * Q)
{
	if(is_queue_full(Q))
	{
		return -1;
	}
	Q->data[Q->end] = node;
	Q->end = (Q->end + 1) % MAX_VER;
	return 0;
}

int queue_pop(Queue *Q)
{
	if(is_queue_empty(Q))
	{
		return -1;
	}
	TYPE node = Q->data[Q->front];
	Q->front = (Q->front + 1)% MAX_VER;

	return node.num;
}

int queue_top(Queue *Q)
{
	assert(Q != NULL);
	return Q->data[Q->front].num;
}


void queue_realse(Queue * Q)
{
	if(Q != NULL)
	{
		free(Q);
		Q = NULL;
	}
}


void bfs(Gnode v, Graph * G)
{
	assert(G != NULL);
	dfs_exist[v.num] = 1;
	Queue * Q= queue_init();
	assert(Q != NULL);
	queue_push(v, Q);

	int i = 0;
	int num = 0;
	while(is_queue_empty(Q) == 0)
	{
		num = queue_top(Q);
		for(i = 0; i < G->n; i++)
		{
			if(G->edge[num][i] == 1 && dfs_exist[i] == 0)
			{
				dfs_exist[i] = 1;
				queue_push(G->ver[i], Q);
			}
		}
		queue_pop(Q);
		printf(" %3c", 'A' + num);
	}
	queue_realse(Q);
}

int serach_graph_bfs(Graph *G)
{
	assert(G != NULL);
	int i = 0;
	memset(dfs_exist, 0, MAX_VER);
	for(i = 0; i < G->n; i++)
	{
		if(dfs_exist[i] == 0)
		{
			bfs(G->ver[i], G);
		}
	}
	return 0;
}


//Warshall算法，求有向图的传递闭包
//O(n^3)
int Warshall(Graph *G)
{
	assert(G != NULL);
	int R[MAX_VER][MAX_VER];
	int i = 0, j = 0, k = 0;
	memset(R, 0, sizeof(int) * MAX_VER *MAX_VER);
	memcpy(R, G->edge, sizeof(int) *MAX_VER * MAX_VER);
	for(i = 0; i < G->n; i++)
	{
		for(j = 0; j < G->n; j++)
		{
			for(k = 0; k < G->n; k++)
			{
				if(R[j][i] == 1 && R[i][k] == 1)
				{
					R[j][k] = 1;
				}
			}
		}
	}
	//print
	memcpy(G->edge, R, sizeof(int) *MAX_VER *MAX_VER);
	print_graph(G);
}


//Floyd算法,求图的最短路径
//O(n^3)
int Floyd(Graph *G)
{
	assert(G != NULL);
	int D[MAX_VER][MAX_VER];
	int k = 0, i = 0, j = 0;
	memset(D, 0, sizeof(int) * MAX_VER *MAX_VER);
	memcpy(D, G->edge, sizeof(int) *MAX_VER *MAX_VER);
	for(k = 0; k < G->n; k++)
	{
		for(i = 0; i < G->n; i++)
		{
			for(j = 0; j < G->n; j++)
			{
				if(D[i][j] > (D[i][k] + D[k][j]))
				{
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
	}

	//print
	memcpy(G->edge, D, sizeof(int) *MAX_VER *MAX_VER);
	print_graph(G);
}

//Dijkstra算法，求图的最短路径




int main(int argc, char const *argv[])
{
	Graph *G = (Graph *)malloc(sizeof(Graph));
	assert(G != NULL);
	//create_graph(G);
	//print_graph(G);
	//search_graph_dfs(G);
	//serach_graph_bfs(G);
	//Warshall(G);
	//printf("\n");


	create_graph_for_floyd(G);
	Floyd(G);
	printf("\n");

	return 0;
}
