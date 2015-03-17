#include <iostream>
#include <stack>
#include <cassert>
#include <cstdlib> //srand
#include <ctime> //time(NULL)
#include <deque>
#include <vector>

using namespace std;

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

typedef struct TreeNode * BitTree;
typedef void ( *CallBack)(BitTree);

void delete_Node(BitTree T)
{
	//cout << "delete Node " << T->val << endl;
	delete []T;
	T = NULL;
}

void print_Node(BitTree T)
{
	cout << T->val << " " << endl;
}

void visit(BitTree T, CallBack Call)
{
	assert(T != NULL);
	Call(T);
}

//非AVL
void init_tree(BitTree T)
{
	assert(T != NULL);
	srand(time(NULL));
	int val = 0;
	BitTree cur = T;
	for(int i = 0; i < 10; i++)
	{
		val = rand()%100;
		BitTree Node = (BitTree)new char[sizeof(struct TreeNode)];
		assert(Node != NULL);
		Node->val = val;
		Node->left = Node->right =NULL;
		if(cur->left == NULL)
		{
			cur->left = Node;
		}
		else if(cur->right == NULL)
		{
			cur->right = Node;
		}
		else
		{
			cur = (val %2 == 0)?cur->left:cur->right;
		}
	}
}

//递归后序删除
void destroy_tree(BitTree T)
{
	if(T == NULL)
		return;
	destroy_tree(T->left);
	destroy_tree(T->right);
	visit(T, delete_Node);
}

//递归前序遍历
void preorder_recursive(BitTree T)
{
	if(T == NULL)
		return;
	visit(T, print_Node);
	preorder_recursive(T->left);
	preorder_recursive(T->right);
}

//非递归前序遍历
void preorder_norecursive(BitTree T)
{
	stack<BitTree> bt_stack;
	BitTree Cur = T;
	while(Cur != NULL || !bt_stack.empty())
	{
		if(Cur != NULL)
		{
			if(Cur->right != NULL)
			{
				bt_stack.push(Cur->right);
			}
			if(Cur->left != NULL)
			{
				bt_stack.push(Cur->left);
			}
			visit(Cur, print_Node);
			Cur = NULL;
		}

		if(!bt_stack.empty())
		{
			Cur = bt_stack.top();
			bt_stack.pop();
		}
	}
}

//递归中序遍历
void inorder_recursive(BitTree T)
{
	if(T == NULL)
		return;
	inorder_recursive(T->left);
	visit(T, print_Node);
	inorder_recursive(T->right);
}

//非递归中序遍历
typedef struct 
{
	BitTree Node;
	int visited;
}VNode;
void inorder_norecursive(BitTree T)
{
	if(T == NULL)
		return;
	stack<BitTree> bt_stack;
	bt_stack.push(T);
	BitTree Cur = NULL;
	while(!bt_stack.empty())
	{
		while((Cur = bt_stack.top()) && Cur->left != NULL )
		{
			bt_stack.push(Cur->left);
		}

		Cur = bt_stack.top();
		visit(Cur, print_Node);
		bt_stack.pop();

		if(Cur->right != NULL)
		{
			bt_stack.push(Cur->right);
		}
	}
}


//递归后序遍历
void postorder_recursive(BitTree T)
{
	if(T == NULL)
		return;
	postorder_recursive(T->left);
	postorder_recursive(T->right);
	visit(T, print_Node);
}

//非递归后序遍历







int main(int argc, char const *argv[])
{
	BitTree T= (BitTree) new char[sizeof(struct TreeNode)]; 
	T->val = 32;
	assert(T != NULL);
	init_tree(T);
	cout << "pre order : "<< endl;
	preorder_recursive(T);
	cout << " pre order in no rec :" <<endl;
	preorder_norecursive(T);
	cout << "in order : " << endl;
	inorder_recursive(T);
	cout << "in order in no rec : " << endl;
	inorder_norecursive(T);
	cout << "destory tree " << endl;
	destroy_tree(T);


	return 0;
}