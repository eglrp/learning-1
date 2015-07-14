#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;



//	Q: 有面值为1元、3元和5元的硬币若干枚，如何用最少的硬币凑够11元
//	d(i) = min{d(i-vj) + 1} vj表示第j个硬币的面值   状态方程

int MinCoin(int value)
{
	int min[32] = {0};
	for(int i = 0; i <= value; i++)
	{
		min[i] = i;
	}
	int v[3] = {1, 3, 5};
	for(int i = 1; i < 12; i++)
	{
		for (int j = 0; j < 3; ++j)
		{
			if(i >= v[j] && min[i] >= (min[i - v[j]] + 1))
			{
				min[i] = min[i - v[j]] + 1;
			}
		}
	}

	return min[value];
}


//一个序列有N个数：A[1],A[2],…,A[N]，求出最长非降子序列的长度 LIS：longest increasing subsequence
//状态方程：d(i) = max{1, d(j) + 1} j < i 且A[j] <= A[i]

//O(n)
int lis(int A[], int n)
{
	int *d  = new int[n];
	for (int i = 0; i < n; ++i)
	{
		d[i] = 1;
	}
	int j = 0;
	int len = 1;

	for (int i = 0; i < n; ++i)
	{
		j = i - 1;
		while(j > 0)
		{
			if(A[j] <= A[i] && d[j] + 1 > d[i])
			{
				d[i] = d[j] + 1;
			}
			j--;
		}
		if(len < d[i]) 
			len = d[i];
	}
	delete []d;

	return len;
}


//二维DP
//平面上有N*M个格子，每个格子中放着一定数量的苹果。你从左上角的格子开始， 每一步只能向下走或是向右走，
//每次走到一个格子上就把格子里的苹果收集起来， 这样下去，你最多能收集到多少个苹果。

//状态转移方程：s[i][j] = A[i][j] + max｛s[i -1][j] , s[i][j - 1]｝
//注意二维数组怎么传参，行存储

int most_apple(int **A,  int row, int column)
{
	int **S = (int **)new int[row];
	for(int i = 0; i < row; i++)
	{
		S[i] = new int[column];
	}

	for(int i = 0; i < row; i++)
	{
		S[i][0] = A[i][0];
	}

	for(int i = 0; i < column; i++)
	{
		S[0][i] = A[0][i];
	}

	for(int i = 1; i < row; i++)
	{
		for (int j = 1; j < column; ++j)
		{
			S[i][j] = max(S[i - 1][j], S[i][j -1]) + A[i][j];
		}
	}

	int rtn = S[row - 1][column - 1];
	for(int i = 0; i < row; i++)
	{
		delete S[i];
	}
	delete S;

	return rtn;
}

//无向图G有N个结点(1<N<=1000)及一些边，每一条边上带有正的权重值。 找到结点1到结点N的最短路径，或者输出不存在这样的路径。
//采用floyd算法，思路也是DP
//参见coding_fun/ds/graph.c ——>Floyd(Graph *G)	立方级的算法


//带状态的DP
//无向图G有N个结点，它的边上带有正的权重值。
//你从结点1开始走，并且一开始的时候你身上带有M元钱。如果你经过结点i， 那么你就要花掉S[i]元(可以把这想象为收过路费)。
//如果你没有足够的钱， 就不能从那个结点经过。在这样的限制条件下，找到从结点1到结点N的最短路径。 或者输出该路径不存在。
//如果存在多条最短路径，那么输出花钱数量最少的那条。 限制：1<N<=100 ; 0<=M<=100 ;
//参见coding_fun/ds/graph.c ---->Dijkstra(Graph *G) 平方级算法






//投资问题
//投资资金 a， 项目总数n，每个项目的利润是Gi (1 << i << n), 求最大的profile
//f(i) 代表前i的项目共投资资金x的最大收益，问题转化成求f(a)的问题
//f(i) = Gi * z + f(i -1) 
//追踪函数:投资的
int max_profile(vector<vector<int> > profit, int resoure)
{
	//k为1时可知F(1) ~F(n)
	Fk(x) = max {fk(xk) + Fk-1(x - xk)} k > 1  (0 <= xk <= 1)
}


//买票问题
//初值 F(1) = T1 F(2) = R1
//递归公式 F(k) = max {F(k - 1) + Tk, F(k - 2) + R(k-1)}  (2 < k <= n)









int main(int argc, char const *argv[])
{
	//test min coin
	cout << MinCoin(11) << endl;

	//test lis
	int a[] = {5, 3, 4, 8, 6, 7};
	cout << lis(a, 6) << endl;

	//test most_apple
	int *A[2];
	int B[][3] = {1,2,3,4,5,6};
	A[0] = B[0];
	A[1] = B[1];
	//注意上面的二维数组传参
	cout << most_apple(A, 2, 3) << endl;
	return 0;
}