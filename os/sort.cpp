#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <cstdlib>

using namespace std;

class Solution
{
	public:
		void insert_sort(vector<int> &v)
		{
			for (int i = 0; i < v.size(); ++i)
			{
				for (int j = i;  j > 0 && v[j - 1] > v[j]; j--)
				{
					swap(v[j -1], v[j]);
				}
			}
		}
	private:
		void debug_message(void *message)
		{
			struct timeval tv;
			gettimeofday(&tv, NULL);
			printf("%s : %d\n", message, tv.tv_sec + tv.tv_usec/1000000);
		}
};


int main(int argc, char const *argv[])
{
	srand(time(NULL));	
	std::vector<int> v;
	for(int i = 0; i < 100; i++)
	{
		v.push_back(rand()/10000);
	}
	debug_message("BEGIN");
	insert_sort(v);
	debug_message("END");
	for (int i = 0; i < 100; ++i)
	{
		cout << " "<<v[i];
	}
	cout << endl;

	return 0;
}

