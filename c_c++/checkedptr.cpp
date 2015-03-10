#include <iostream>
#include <stdexcept>
using namespace std;

class CheckedPtr
{
	public:
		CheckedPtr(int *b, int *e):beg(b),end(e),cur(b){}
		CheckedPtr(const CheckedPtr &);
		CheckedPtr& operator=(const CheckedPtr&);

	public:
		friend bool operator==(const CheckedPtr &lhs, const CheckedPtr & rhs);
		friend bool operator!=(const CheckedPtr &lhs, const CheckedPtr & rhs);
		CheckedPtr& operator++();
		CheckedPtr& operator--();
		const CheckedPtr operator++(int);
		const CheckedPtr operator--(int);
		int & operator[](const size_t index);
		const int & operator[](const size_t index) const;
		int & operator*();
		const int & operator*() const;
	private:
		
		int *beg;
		int *end;
		int *cur;
};

//you can use default ,here put it out only for demo
CheckedPtr::CheckedPtr(const CheckedPtr &other)
{
	beg = other.beg;
	end = other.end;
	cur = other.cur;
}

//you can use default ,here put it out only for demo
CheckedPtr& CheckedPtr::operator=(const CheckedPtr& other)
{
	beg = other.beg;
	end = other.end;
	cur = other.cur;

	return *this;
}

//prefix,more efficiency
CheckedPtr & CheckedPtr::operator++()
{
	if(cur == end)
	{
		throw out_of_range("Error!!!");
	}
	++cur;
	return *this;
}

//prefix
CheckedPtr & CheckedPtr::operator--()
{
	if(cur == beg)
	{
		throw out_of_range("Error!!!");
	}
	--cur;
	return *this;
}

//suffix
//return value must be const, why?
const CheckedPtr CheckedPtr::operator++(int)
{
	CheckedPtr ret(*this);
	++*this;
	return ret;
}

//suffix
const CheckedPtr CheckedPtr::operator--(int)
{
	CheckedPtr ret(*this);
	--*this;
	return ret;
}

int & CheckedPtr::operator[](const size_t index)
{
	if(beg + index >= end || beg + index < beg)
	{
		throw out_of_range("Error!!!");
	}

	return *(beg + index);
}

const int & CheckedPtr::operator[](const size_t index) const
{
	if(beg + index >= end || beg + index < beg)
	{
		throw out_of_range("Error!!!");
	}

	return *(beg + index);
}

int & CheckedPtr::operator *()
{
	if(cur == end)
	{
		throw out_of_range("Error!!!");
	}

	return *cur;
}

const int & CheckedPtr::operator *() const
{
	if(cur == end)
	{
		throw out_of_range("Error!!!");
	}

	return *cur;
}

bool operator==(ChecKedPtr &lhs, CheckedPtr &rhs)
{
	return (lhs.beg == rhs.beg && lhs.end == rhs.end && lhs.cur == rhs.cur);
}

bool operator !=(const CheckedPtr &lhs, const CheckedPtr &rhs)
{
	return !(lhs == rhs);
}






int main(void)
{
	CheckedPtr ptr((int *)0, (int *)4);
	++ptr;
	++ptr;

	return 0;
}














