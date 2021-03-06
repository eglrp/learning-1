#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;


//最长公共子串,暴力法, O(n^2 * m)
string LongestCommonSubstring_bak(const string &str1, const string &str2)
{
	string out;
	int longest = 0, length = 0;
	int start = -1;
	int m = 0, n = 0; 
	for (int i = 0; i < str1.size(); ++i)
	{
		for (int j = 0; j < str2.size(); ++j)
		{
			m = i;
			n = j;
			length = 0;
			while(m < str1.size() && n < str2.size() && str1[m] == str2[n])
			{
				length++;
				m++;
				n++;
			}
			//检查替换
			if(longest < length)
			{
				longest = length;
				start = i;
			}
		}
	}
	if(start == -1)
		return out;
	out = str1.substr(start, longest);
	return out;
}

//最长公共子串,采用DP去重
//L[i, j]代表以s[i]和s[j]为结尾的相同子串的长度。
//DP公式 L[i + 1, j + 1] = (s[i] == t[j]?L[i, j] + 1:0)
//O(n^2)
string LongestCommonSubstring(const string &str1, const string &str2)
{
	int size1 = str1.size();
	int size2 = str2.size();
	int longest = 0;
	int start = -1;
	string out;
	std::vector<std::vector<int> > table(size1, vector<int>(size2, 0));

	for (int i = 0; i < size2; ++i)
	{
		if(str1[0] == str2[i])
			table[0][i] = 1;
	}

	for (int i = 1; i < size1; ++i)
	{
		if(str1[i] == str2[0])
			table[i][0] = 1;
		for(int j = 1; j < size2; j++)
		{
			if(str1[i] == str2[j])
				table[i][j] = table[i - 1][j - 1] + 1;
		}
	}

	for (int i = 0; i < size1; ++i)
	{
		for(int j = 0; j < size2; ++j)
		{
			if(longest < table[i][j])
			{
				longest = table[i][j];
				start = i - longest + 1;
			}
		}
	}

	if(start == -1)
		return out;
	out = str1.substr(start, longest);

	return out;
}

//最大连续子序列
//采用滚动数组
vector<int> MaxSubArray(vector<int> & l)
{
	std::vector<int> out;
	int begin = -1, end = -1;
	int sum = 0;
	int max = 0;
	int first = 0;
	for(int i = 0; i < l.size(); ++i)
	{
		if(sum == 0)
			first = i;
		sum += l[i];
		if(sum < 0)
			sum = 0;
		if(max < sum)
		{
			begin = first;
			end = i;
			max = sum;
		}
	}

	if(begin == -1 || end == -1)
		return out;
	for (int i = begin; i <= end; ++i)
	{
		out.push_back(l[i]);
	}
	return out;
}

//最大连续子序列
//采用DP
//EndMax[n] = max{EndMax[n - 1] + a[n] , a[n]}
//SubMax[n] = max{SubMax[n - 1], EndMax[n]}
vector<int> MaxSubArray_DP(vector<int> & l)
{
	int EndMaxBegin = 0, EndMaxEnd = 0;
	int SubMaxBegin = 0, SubMaxEnd = 0;

	int EndMax = 0, SubMax = 0;

	std::vector<int> v;

	for(int i = 0; i < l.size(); i++)
	{
		if(EndMax + l[i] < l[i] )
		{
			EndMax = l[i];
			EndMaxBegin = i;
			EndMaxEnd = i;
		}
		else
		{
			EndMax = EndMax + l[i];
			EndMaxEnd = i;
		}

		if(SubMax < EndMax)
		{
			SubMax = EndMax;
			SubMaxBegin = EndMaxBegin;
			SubMaxEnd = EndMaxEnd;
		}
	}

	for (int i = SubMaxBegin; i <= SubMaxEnd; ++i)
	{
		v.push_back(l[i]);
	}

	return v;
}



//最长递增子序列 LIS：longest increasing subsequence
//一个序列的最长递增子序列，是以该序列所有节点为尾节点的最长子序列。

int lis(vector<int> &l, vector<int> &out)
{
	std::vector<int> len(l.size(), 1);
	std::vector<int> pre(l.size(), 0);
	int max = 0;
	int j = 0;
	int z = 0;
	for (int i = 0; i < l.size(); ++i)
	{
		j = i - 1;
		while(j >= 0)
		{
			if(l[i] > l[j] && len[i] < len[j] + 1)
			{
				len[i] = len[j] + 1;
				pre[i] = j;
			}
				
			j--;
		}

		if(max < len[i])
		{
			max = len[i];
			z = i;
		}
	}

	int temp = max;
	while(temp--)
	{
		out.push_back(l[z]);
		z = pre[z];
	}
	reverse(out.begin(), out.end());

	return max;
}

//LIS DP
//递推表达式
//
//时间复杂度O(n^2)
int lis_dp(vector<int> &l)
{
	if(l.size() == 0)
		return 0;
	std::vector<int> dp(l.size(), 1);
	int max = dp[1];
	for (int i = 2; i < l.size(); ++i)
	{
		for(int j = 1; j < i; j++)
		{
			if(l[i] > l[j] && dp[j] + 1 > dp[i])
			{
				dp[i] = dp[j] + 1;
			}
		}
		if(dp[i] > max)
		{
			max = dp[i];
		}
	}

	return max;
}




//最长公共子序列

//字符串编辑距离


//求最长的不重复字符子串
int lengthOfLongestSubstring(string s) {
	int EndStringBegin = 0, EndStringEnd = 0;
	int SubStringBegin = 0, SubStringEnd = 0;
	map<char , int > my_map;
	int maxlen = 0;

	for (int i = 0; i < s.size(); ++i)
	{
	 	if(my_map.count(s[i]) != 0)
	 	{
	 		for(int j = my_map[s[i]] - 1; j >= EndStringBegin; j--)
	 		{
	 			my_map.erase(s[j]);
	 		}
	 		EndStringBegin = my_map[s[i]] + 1;
	 		EndStringEnd = i;
	 		cout << EndStringBegin << " " << EndStringEnd << endl;
	 		my_map[s[i]] = i;
	 	}
	 	else
	 	{
	 		EndStringEnd = i;
	 		my_map[s[i]] = i;

	 	}

	 	if(EndStringEnd - EndStringBegin  + 1 > maxlen)
	 	{
	 		maxlen = EndStringEnd - EndStringBegin + 1;
	 		SubStringBegin = EndStringBegin;
	 		SubStringEnd = EndStringEnd;
	 	}
	}

	return maxlen; 
}



int main(int argc, char const *argv[])
{

/*
	string out;
	out = LongestCommonSubstring("abcd", "abc");
	cout << out<< endl;
*/

	int a[] = {5, -6, 4, 2};
	std::vector<int> v(a, a + 4);
	std::vector<int> out = MaxSubArray_DP(v);
	cout << "[ ";
	for (int i = 0; i < out.size(); ++i)
	{
		cout << out[i] << " ";
	}
	cout << "]"<<endl;


/*
	int a[] = {5, -6, 4, 2, 3};
	std::vector<int> v(a, a + 5);
	std::vector<int> out;
	int num = lis(v, out);
	cout << num << endl;
	cout << "[ ";
	for (int i = 0; i < out.size(); ++i)
	{
		cout << out[i] << " ";
	}
	cout << "]"<< endl;
*/


	return 0;
}