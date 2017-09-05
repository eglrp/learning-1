#include <iostream>
#include <vector>
#include <boost/function.hpp>

using namespace std;

bool Max(int a, int b)
{
	return a > b;
}


void test1()
{
	boost::function<bool(int, int)> f;
	f = &Max;
	const char *a = f(2, 5)?"True":"false";
	cout << a << endl;
}



class notify
{
public:
	//typedef void(*func_type)(int);
	typedef boost::function<void (int)>  func_type;
	void add_func(func_type func)
	{
		vec.push_back(func);
	}

	void change(int n)
	{
		_value = n;
		for(int i = 0; i < vec.size(); i++)
		{
			vec[i](_value);
		}
	}


private:
	vector<func_type> vec;
	int _value;
};


//basic function
void print_value(int value)
{
	cout << value << "you are here"<< endl;
}


//a function object which have status
class status_func
{
public:
	void operator() (int i)
	{
		static bool first = true;
		if(first == true)
		{
			_last_value = 1;
			cout << _last_value << endl;
			first = false;
		}
		else
		{
			cout << _last_value << endl;
			_last_value = i;
		}
	}
private:
	int _last_value;
};



void test2()
{
	notify n;
	//n.add_func(&print_value);
	//n.change(12);

/*
	status_func a;
	a(12);
	a(13);
	a(14);
*/

	status_func a;
	n.add_func(a);//here input a 

/*
	//you can also
	n.add_func(status_func());
*/

	n.change(46);
	n.change(67);
	n.change(32);
}


//a function object which have a good use
template <typename T>
class func_type
{
public:
	func_type(void (T::*f)(const char *), T * object):Obj(object),pFunc(f) {}

	void operator () (const char *name)
	{
		(Obj->*pFunc)(name);
	}

private:
	T *Obj;
	void (T::*pFunc)(const char*);

};

class name_house
{
public:
	void print(const char *name)
	{
		cout << "My name is "<< name << endl; 
	}
};


void test3()
{
	name_house A;
	//error ,C++不允许通过已绑定的成员函数地址来构造成员函数指针。
	//func_type<name_house> test(&A.print, &A);
	func_type<name_house> test(&name_house::print, &A);

	test("fyliu");
}


//怎样传递类实例里面的成员函数给boost::function 

//1>传值
void test4()
{
	boost::function<void (name_house, const char*)>	f;
	f = &name_house::print;

	f(name_house(), "fyliu");
	
}

//2>传引用
void test5()
{
	boost::function<void (name_house&, const char*)>	f;
	f = &name_house::print;
	name_house A;
	f(A, "fyliu");
}


//3>传指针
void test6()
{
	boost::function<void (name_house*, const char*)>	f;
	f = &name_house::print;
	name_house A;
	f(&A, "fyliu");
}

//boost::ref 
//boost::function的缺省行为是复制它要调用的函数对象。
//booost::ref 会通知boost::function 保存一个函数对象的引用  boost::cref const 引用

class keep_status
{
public:
	keep_status():_total(0) {}
	int operator () (int i)
	{
		_total += i;
		return _total;
	}

	int total()
	{
		return _total;
	}
private:
	int _total;
};

void test7()
{
	boost::function <int(int)> f;
	keep_status ks;
	//f =  ks;
	f = boost::ref(ks);

	
	cout << f(10) << endl;
	cout << ks.total() << endl;
}


int main(int argc, char const *argv[])
{
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	test7();

	return 0;
}


