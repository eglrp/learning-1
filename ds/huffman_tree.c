
/*
* 前缀编码：建立不等长编码时必须使任何一个字符的编码都不是另一个字符的前缀，这宗编码称为前缀编码（prefix  code）
* 题目：假设一个文本文件TFile中只包含7个字符{A，B，C，D，E，F，G}，这7个字符在文本中出现的次数为{5，24，7，17，34，5，13}
* 利用哈夫曼树可以为文件TFile构造出符合前缀编码要求的不等长编码。
*/

#include <stdio.h>
#include <string.h>
#include <assert.h>

#define N	7	//带编码字符的个数
#define M	2*N - 1 //数中总节点的


typedef struct _tnode
{
	int weight;
	int parent;
	int left;
	int right;
}TNode;

typedef struct _DCode
{
	char data;	//待编码的字符
	int weight;
	char code[N+1];	//字符的编码
}DCode;


int init_Code(DCode *code)
{
	assert(code != NULL);
	code[0].data = 'A';
	code[0].weight = 5;
	code[1].data = 'B';
	code[1].weight = 24;
	code[2].data = 'C';
	code[2].weight = 7;
	code[3].data = 'D';
	code[3].weight = 17;
	code[4].data = 'E';
	code[4].weight = 34;
	code[5].data = 'F';
	code[5].weight = 5;
	code[6].data = 'G';
	code[6].weight = 13;

	return 0;
}


//left < right
// 主定理 A（n) = A(n/2) + n/2
//时间复杂度n  空间复杂度 n 
//It have problem.because if [a,b] [c,d] if(max(a,b) < min(c, d)). aha, I am so foolish.
int Select_bak(TNode *node, int k, int *left, int *right)
{
	assert(node != NULL);
	int i = 0, j = 0;
	int a[M] = {0};
	for(i = 0, j = 0; i < k ; i++)
	{
		if(node[i].parent != -1)
			continue;
		a[j++] = i;
	}
	int start = 0;
	int end = j;
	while(end > 2)
	{
		for(i = 0, j = 0; i < end; i = i + 2)
		{
			if(i + 1 == end || node[a[i]].weight < node[a[i + 1]].weight)
			{
				a[j++] = a[i];
			}
			else
			{
				a[j++] = a[i + 1]; 
			}
		}
		end = j;
	}
	if(node[a[0]].weight <= node[a[1]].weight)
	{
		*left = a[0];
		*right = a[1];
	}
	else
	{
		*left = a[1];
		*right = a[0];
	}
	return 0;
}

int Select(TNode *node, int k, int *left, int *right)
{
	int i = 0;
	for(i = 0; i < k; i++)
	{
		if(node[i].parent == -1)
			break;
	}
	*left = i;

	for(i = 0; i < k ; i++)
	{
		if(node[i].parent == -1 && node[i].weight < node[*left].weight)
		{
			*left = i;
		}
	}

	for(i = 0; i < k ; i++)
	{
		if(node[i].parent == -1 && i != *left)
			break;
	}
	*right = i;

	for(i = 0; i < k; i++)
	{
		if(node[i].parent == -1 &&  i != *left && node[i].weight < node[*right].weight)
		{
			*right = i;
		}
	}
}


int create_huffman_tree(DCode *code, TNode *node)
{
	assert(code != NULL && node != NULL);

	int i = 0;
	for(i = 0; i < M; i++)
	{
		if(i < N)
		{
			node[i].weight = code[i].weight;
		}
		else
		{
			node[i].weight = 0;
		}
		node[i].parent = node[i].left = node[i].right = -1;
	}

	int left =0, right = 0;
	for(i = N; i < M; i++)
	{
		Select(node, i, &left, &right);//[0,i)
		node[i].left = left;
		node[i].right = right;
		node[i].weight = node[left].weight + node[right].weight;
		node[left].parent = i;
		node[right].parent = i;
	}

	return 0;
}

int Encode(TNode *node, DCode *code)
{
	assert(node != NULL && code != NULL);
	int i = 0; 
	int j = -1;
	int k = -1;
	int start = -1;
	char cd[N + 1];
	cd[N] = '\0';
	for(i = 0; i < N; i++)
	{
		k = i;
		start = N - 1;
		while( (j = node[k].parent) >= 0)
		{
			if(node[j].left == k)
			{
				cd[start--] = '0';
			}
			else
			{
				cd[start--] = '1';
			}
			k = j;
		}
		printf("cd = %s\n", cd + start + 1);
		strcpy(code[i].code, &cd[start + 1]); //here is very good!
	}

	return 0;
}

//脚手架程序
int main(int argc, char const *argv[])
{
	TNode ht[M + 1] = {0};
	DCode hc[N + 1] = {0};
	init_Code(hc);
	create_huffman_tree(hc, ht);
	Encode(ht, hc);

	int i = 0;
	for(i = 0; i < N; i++)
	{
		printf("%c-----%s\n", hc[i].data, hc[i].code);
	}

	return 0;
}

