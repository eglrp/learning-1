#include <iostream>
#include <fstream>

/*write by fyliu, and if you do not know how to use iostream ,please read it.*/ 
using namespace std;

//out.good() 
//out.is_open();
//out.fail()
int WriteFileText(const char *file)
{
	int i = 3456;
	std::ofstream out(file);
	if(out.good())
	{
		out << i <<endl;
		out << "This is a text." << endl;
	}

	return 0;
}

//in.good()
//in.eof()
//in.getline(char *buf, int len);
//std::getline(iostream &stream, string &str, int deline);
int ReadFileText(const char *file)
{
	std::ifstream in(file);
	if(in.good())
	{
#if 0
		string doc;
		std::getline(in, doc, (char)EOF);
		cout << doc << endl;
#else
		char buf[100] = {0};
		while(!in.eof())
		{
			in.getline(buf, 100);
			cout << buf << endl;
		}
#endif

	}
}

int WriteFile(const char *file)
{
	char buf[100];
	int a[6] = {12, 13, 14, 15, 16, 17};
	memset(buf, 0, 100);
	memcpy(buf, a, sizeof(a));

	ofstream out(file, ios::out | ios::binary | ios::trunc);
	if(out.good())
	{
		out.write(buf, 100);
	}
}

int ReadFile(const char *file)
{
	char *buffer = NULL;
	long size = 0;
	ifstream in(file, ios::in | ios::binary | ios::ate);
	{
		size = in.tellg();
		cout << "size =  " << size <<endl;
		in.seekg(0, ios::beg);
		buffer = new char[size];
		memset(buffer, 0, size);
		in.read(buffer, size);

		ofstream out("test.txt", ios::out | ios::binary | ios::trunc);
		if(out.good())
		{
			out.write(buffer, size);
		}
		delete []buffer;
	}
}


int main(int argc, char const *argv[])
{
	if(argc != 2)
	{
		cout << "error" << endl;
	}

	//WriteFileText(argv[1]);
	//cout << "------------" << endl;
	//ReadFileText(argv[1]);

	//WriteFile(argv[1]);
	cout << "--------------" << endl;
	ReadFile(argv[1]);

	return 0;
}