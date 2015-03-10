#include <iostream>

using namespace std;

class RefPtr
{
	friend class TestPtr;

	char *ptr;
	size_t count;

	RefPtr(char *p):ptr(p), count(1){}

	~RefPtr(){
		cout << "delete" << *ptr << endl;
		delete ptr;
	}
	
};

class TestPtr
{
	public:
		TestPtr(char *p):ptr(new RefPtr(p)){}
		TestPtr(const TestPtr&src):ptr(src.ptr)
		{
			++ptr->count;
		}
		TestPtr& operator= (const TestPtr &src)
		{
			++src.ptr->count;
			if(--ptr->count == 0)
			{
				delete ptr;
			}
			ptr = src.ptr;
			printf("count = %d\n", ptr->count);
			return *this;
		}

		~TestPtr()
		{
			if(--ptr->count == 0)
			{
				delete ptr;
			}
		}

		void print(){cout << ptr->count << endl;}
	private:
		RefPtr *ptr;
};



int main(void)
{
	char *m = new char[6];
	char *n   = new char[6];
	strcpy(m, "abc");
	strcpy(n, "def");

	TestPtr a(m);
	a.print();

	TestPtr b(n);
	b.print();
/*

	a = b;
	a.print();
	b.print();
*/

	
	return 0;
}







