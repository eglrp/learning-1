#include <iostream>

using namespace std;


class Object
{

};

class Test
{
public:
	void test_print()
	{
		cout << "hello world"  << endl;
	}
};

typedef void (Object::*call_back)();

int main(int argc, char const *argv[])
{
	Object *optr;
	call_back  ptr = (call_back )&Test::test_print;
	Test t;
	optr = (Object *)&t;
	(optr->*(ptr))();
	return 0;
}