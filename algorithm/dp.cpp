#include <iostream>

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





int main(int argc, char const *argv[])
{
	//test min coin
	cout << MinCoin(11) << endl;

	int a[] = {5, 3, 4, 8, 6, 7};
	cout << lis(a, 6) << endl;
	return 0;
}