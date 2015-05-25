#include <iostream>

using namespace std;

#define MAX_CHAR_NUM	26

enum NODE_TYPE 
{
	TYPE_COMPLETED,
	TYPE_UNCOMPLETED
};

struct _Node
{
	enum NODE_TYPE	type;
	char ch;
	int count;	//这个字段利于单词的删除
	_Node * child[MAX_CHAR_NUM];
};

_Node * ROOT = NULL;

int index(char ch)
{
	return ch - 'a';
}

_Node * create_node(char ch)
{
	_Node *node = (_Node *)new char[sizeof(struct _Node)];
	node->type = TYPE_UNCOMPLETED;
	node->ch = ch;
	node->count = 1;
	for (int i = 0; i < MAX_CHAR_NUM; ++i)
	{
		node->child[i] = NULL;
	}

	return node;
}

void _init()
{
	ROOT = create_node(' ');
}

void insert_string(char str[], int len)
{
	_Node * pNode = ROOT;
	for (int i = 0; i < len; ++i)
	{
		if(pNode->child[index(str[i])] == NULL)
		{
			pNode->child[index(str[i])] = create_node(str[i]);
		}
		else
		{
			pNode->child[index(str[i])]->count++;
		}
		pNode = pNode->child[index(str[i])];
	}
	pNode->type = TYPE_COMPLETED;
}

bool search_string(char str[], int len)
{
	int i = 0;
	_Node *pNode = ROOT;
	for(i = 0; i < len; i++)
	{
		if(pNode->child[index(str[i])] == NULL)
		{
			break;
		}
		pNode = pNode->child[index(str[i])];
	}

	return i == len && pNode->type == TYPE_COMPLETED;
}


void delete_trie_node(_Node *node)
{
	for (int i = 0; i < MAX_CHAR_NUM; ++i)
	{
		if(node->child[i] != NULL)
		{
			delete_trie_node(node->child[i]);
		}
	}
	delete node;
}

bool delete_string(char str[], int len)
{
	if(search_string(str, len) == false)
		return false;
	_Node *pNode = ROOT;
	for (int i = 0; i < len; ++i)
	{
		if(pNode->child[index(str[i])]->count == 1)
		{
			delete_trie_node(pNode->child[index(str[i])]);
			break;
		}
		else
		{
			pNode->child[index(str[i])]->count--;
		}
		pNode = pNode->child[index(str[i])];
	}

	return true;
}


//trie树、哈希表、红黑树

int main(int argc, char const *argv[])
{
	_init();
	insert_string("hello", 5);
	insert_string("helag", 5);
	insert_string("aonondag", 8);
	bool test = search_string("hello", 5);
	cout << test << endl;
	delete_string("hello", 5);
	test = search_string("hello", 5);
	cout << test << endl;
	test = search_string("aonondag", 8);
	cout << test << endl;
	return 0;
}

