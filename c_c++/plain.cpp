#include <iostream>
#include <string>
#include <string.h>

using namespace std;

class Encrypt
{
	public: 
		Encrypt()
		{
		//	key = NULL;
		//	plaintext = NULL;
		//	cipphertext = NULL;
		}
		virtual ~Encrypt() {}
		virtual bool EncryptPro();
		virtual bool DecryptPro();
		
	public:
		string GetPlainText() const;
		bool SetPlainText(const char *text);
		string GetClippherText() const;
		bool SetClippherText(const char *text);
		string GetKey() const;
		bool SetKey(const char *text);
	private:
		bool IsNumberChar(string text)
		{
			if(text.empty())
			{
				return false;
			}
			for(int i = 0; i < text.length(); i++)
			{
				if(text.at(i) <= '0' && text.at(i) >= '9')
				{
					return false;
				}

				return true;
			}
		}

	private:
		string key;//ÃÜÔ¿
		string plaintext;//Ã÷ÎÄ
		string cipphertext;//ÃÜÎÄ
};

string Encrypt::GetPlainText() const
{
	return plaintext;
}

bool Encrypt::SetPlainText(const char* text)
{
	if(text == NULL || strlen(text) <= 0 || !IsNumberChar(text))
	{
		return false;
	}
	plaintext = text;

	return true;
}

string Encrypt::GetClippherText() const
{
	return cipphertext;
}

bool Encrypt::SetClippherText(const char *text) 
{
	if(text == NULL || strlen(text) <= 0 || !IsNumberChar(text))
	{
		return false;
	}

	cipphertext = text;

	return true;
}

string Encrypt::GetKey() const
{
	return key;
}

bool Encrypt::SetKey(const char *text)// don't greater than 20 
{
	if(text == NULL || strlen(text) <= 0 || !IsNumberChar(text))
	{
		return false;
	}

	key = text;

	return true;
}

bool Encrypt:: EncryptPro()
{
	if(key.empty() || plaintext.empty())
	{
		return false;
	}

	cipphertext.erase();

	for(int i = 0, j = 0; i < plaintext.length(); i++, j++, j%=key.length())
	{
		int a = (int)(plaintext[i] - '0');
		int k = (int)(key[j] - '0');
		a = (a + k)% 10;
		cipphertext += (char)(a + '0');
	}

	return true;
}

bool Encrypt::DecryptPro()
{
	if(key.empty() || cipphertext.empty())
	{
		return false;
	}
	plaintext.erase();
	for(int i, j = 0; i < cipphertext.length(); i++, j++, j%=key.length())
	{
		int a = (int) (cipphertext[i] - '0');
		int k = (int)(key[i] - '0');
		a= (a + 10 - k)%10;
		plaintext += (char)(a + '0');
	}

	return true;
}


int main(void)
{
	Encrypt test;
	string key, password, cipp;
	cout << "Please Enter Your secret key:" << endl;
	cin >> key;
	if(cin)
	{
		test.SetKey(key.c_str());
	}
	cout <<test.GetKey() << endl;
	cout << "Please Enter Your password:" << endl;
	cin >> password;
	if(cin)
	{
		test.SetPlainText(password.c_str());
	}
	test.EncryptPro();
	cout << "Your cipphertext is :" << endl;
	cout << test.GetClippherText() << endl;	
	cout << "Your plaintext is :" << endl;
	cout << test.GetPlainText() << endl;

	return 0;
}



























