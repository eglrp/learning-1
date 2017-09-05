#include <iostream>


using namespace std;

class MyExcepction
{
public:
	 explicit MyExcepction(int errorId)
	{
		cout << "MyExcepction is called"<<endl;
		m_errorId = errorId;
	}
	MyExcepction(MyExcepction &myExp)
	{
		cout << "Copy Excepction is called" << endl;
		this->m_errorId= myExp.m_errorId;
	}
	~MyExcepction()
	{
		cout << "~MyExcepction() is called" << endl;
	}
	int getErrorCode()
	{
		return m_errorId;
	}
private:
	int m_errorId;

};


int main(int argc, char const *argv[])
{
	int throwErrorCode = 110;
	cout <<"input test code:" << endl;
	cin >> throwErrorCode;

	try
	{
		if(throwErrorCode == 110)
		{
			MyExcepction myStru(110);
			throw &myStru;
		}
		else if(throwErrorCode == 119)
		{
			MyExcepction  myStru(119);

			throw myStru;
		}
		else if(throwErrorCode == 120)
		{
			MyExcepction *pMyStru = new MyExcepction(120);
			throw pMyStru;
		}
		else 
		{
			//throw MyExcepction(throwErrorCode);
		}
	}
	catch(MyExcepction *pMyExcepction)
	{
		cout << "catch(MyExcepction *pMyExcepction)" << endl;
		cout << "error code "<< pMyExcepction->getErrorCode() << endl;
	}
	catch(MyExcepction object)
	{
		cout << "catch(MyExcepction object)" << endl;
		cout << "error code "<< object.getErrorCode() << endl;

	}catch(...)
	{

		cout << "catch(...)"<<endl;
		throw;
	}

	int temp;
	cin >> temp;

	return 0;
}
