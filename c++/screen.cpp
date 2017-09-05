#include <iostream>
#include <string>

using namespace std;

class Screen
{
	public:
		typedef string::size_type index;
		char get() const { return contents[cursor];}
		inline char get(index ht, index wd) const;
		index get_cursor() const;
		Screen(index ht, index wd, const string &str);

		Screen & move(index r, index c);
		Screen & set(char);
		Screen & display(ostream &os);
		const Screen & display(ostream &os) const;
	private:
		void do_display(ostream &os) const;
	private:
		string contents;
		index cursor;
		index height, width;
		
};

Screen::Screen(index ht, index wd, const string &str =""):
	cursor(0),height(ht),width(wd)
{
	contents.assign(height *width, ' ');
	if(str.size() != 0)
	{
		contents.replace(0, str.size(), str);
	}
}

char Screen::get(index ht, index wd) const
{
	index row = ht * width;
	return contents[row + wd];	
}

inline Screen::index Screen::get_cursor() const
{
	return cursor;
}

Screen & Screen::set(char c)
{
	contents[cursor] = c;
	return *this;
}

Screen & Screen::move(index r, index c)
{
	/*行列均从零开始*/
	if(r >= height || c >= width)
	{
		cerr << "invalid row or column" << endl;
		throw EXIT_FAILURE;
	}
	index row = r * width;
	cursor = row + c;
	return *this;	
}	

Screen & Screen::display(ostream &os)
{
	do_display(os);
	return *this;
}

const Screen & Screen::display(ostream &os) const
{
	do_display(os);
	return *this;
}

inline void Screen::do_display(ostream &os) const
{
	string::size_type index = 0;
	while(index != contents.size())
	{
		os << contents[index];
		if((index + 1)%width == 0)
		{
			os << '\n';
		}
		++index;
	}
}

int main(void)
{
	Screen myscreen(5, 6, "aaaaaabbbbbbccccccddddddeeeeee");
	myscreen.move(2, 0).set('#').display(cout);
	Screen::index a = myscreen.get_cursor();
	cout << a << endl;
	const Screen testscreen(2,3, "aaabbb");
	testscreen.display(cout);

	return 0;
}



