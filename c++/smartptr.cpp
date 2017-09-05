#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

//class Item_base;

typedef string	Item_base;

class Sales_item
{
	public:
		Sales_item():p(NULL),use(new size_t(1)){}
		Sales_item(const Item_base&);
		Sales_item(const Sales_item &i);
		Sales_item & operator=(Sales_item &);
		~Sales_item(){decr_usr();}

	public:
		const Item_base * operator->() const{
			if(p)
			  	return p;
			else
				throw out_of_range("Error!!!\n");
		}

		Item_base * operator->() {
			if(p)
				return p;
			else
				throw out_of_range("Error!!!\n");
		}

		
		const Item_base & operator*() const{
			if(p)
				return *p;
			else
				throw out_of_range("Error!!!\n");
		}

		Item_base & operator *(){
			if(p)
				return *p;
			else
				throw out_of_range("Error!!!\n");
		}
	private:
		void decr_usr()
		{
			if(--*use == 0)
			{
				delete p;
				delete use;
			}
		}	
			
	private:
		Item_base *p;
		size_t *use;
		
};


Sales_item::Sales_item(const Item_base &rhs)
{
	p = new Item_base;
	use = new size_t(1);
	*p = rhs;
}

Sales_item::Sales_item(const Sales_item &i)
{
	++*i.use;
	if(--*use == 0)
	{
		delete p;
	}
	p = i.p;
	use = i.use;
}

//here we do not self-check
Sales_item & Sales_item::operator=(Sales_item &rhs)
{
	++*rhs.use;
	decr_usr();
	p = rhs.p;
	use = rhs.use;

	return *this;	
}



int main(void)
{
	Sales_item a("hello");
	Sales_item b("world");
	cout << *a << endl;

	a = b;
	cout << *a <<endl;

	a->insert(0, "fyliu ");
	cout << *a << endl;
}


