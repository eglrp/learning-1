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
	int visited; // 专门给非递归后序遍历用的
	struct TreeNode *left;
	struct TreeNode *right;
};

typedef struct TreeNode * BitTree;
typedef void ( *CallBack)(BitTree);

void delete_Node(BitTree T)
{
	cout << "delete Node " << T->val << endl;
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

//create a tree on OJ
TreeNode *create_tree_oj(int a[], int len)
{
	TreeNode * head = (TreeNode *)new char[sizeof(struct TreeNode)];
	if(head == NULL)
	{
		return head;
	}

	head->val = a[0];
	head->left = head->right = NULL;
	deque<TreeNode *>tn_deque;
	tn_deque.push_back(head);
	int index = 0;
	TreeNode *cur = NULL;
	TreeNode *temp = NULL;

	while(!tn_deque.empty() && index < len)
	{
		cur = tn_deque.front();
		if(++index && index < len && a[index] != -1)
		{
			temp = (TreeNode *)new char[sizeof(struct TreeNode)];
			temp->val = a[index];
			temp->left = temp->right = NULL;
			cur->left = temp;
			tn_deque.push_back(temp);
		}

		if(++index && index < len && a[index] != -1)
		{
			temp = (TreeNode *)new char[sizeof(struct TreeNode)];
			temp->val = a[index];
			temp->left = temp->right = NULL;
			cur->right = temp;
			tn_deque.push_back(temp);
		}
		tn_deque.pop_front();
	}

	return head;
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
void inorder_norecursive(BitTree T)
{
	stack<BitTree> bt_stack;
	BitTree Cur = T;
	while(Cur != NULL || !bt_stack.empty())
	{
		while(Cur != NULL)
		{
			bt_stack.push(Cur);
			Cur =  Cur->left;
		}

		if(!bt_stack.empty())
		{
			Cur = bt_stack.top();
			visit(Cur, print_Node);
			bt_stack.pop();
			Cur = Cur->right;
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
void postorder_norecursive(BitTree T)
{
	stack<BitTree> bt_stack;
	BitTree Cur = NULL;
	if(T != NULL)
	{
		T->visited = 0;
		bt_stack.push(T);
	}

	while(!bt_stack.empty())
	{
		Cur = bt_stack.top();
		bt_stack.pop();
		if(Cur->visited == 1)
		{
			visit(Cur, print_Node);
		}
		else
		{
			Cur->visited = 1;
			bt_stack.push(Cur);
			if(Cur->right != NULL)
			{
				Cur->right->visited = 0;
				bt_stack.push(Cur->right);
			}
			if(Cur->left != NULL)
			{
				Cur->left->visited = 0;
				bt_stack.push(Cur->left);
			}
		}
	}
}


//非递归层序遍历
void levelorder(BitTree T)
{
	deque<BitTree> bt_queue;
	BitTree Cur = NULL;
	if(T != NULL)
	{
		bt_queue.push_back(T);
	}

	while(!bt_queue.empty())
	{
		Cur = bt_queue.front();
		visit(Cur, print_Node);
		bt_queue.pop_front();
		if(Cur->left != NULL)
		{
			bt_queue.push_back(Cur->left);
		}
		if(Cur->right != NULL)
		{
			bt_queue.push_back(Cur->right);
		}
	}
}






int main(int argc, char const *argv[])
{
	/*
	BitTree T= (BitTree) new char[sizeof(struct TreeNode)]; 
	T->val = 32;
	T->left = T->right = NULL;
	assert(T != NULL);
	init_tree(T);
	*/
	int a[] = {3,9,20,-1,-1,15,7};
	BitTree T =  create_tree_oj(a, 7);
	cout << "pre order : "<< endl;
	preorder_recursive(T);
	cout << " pre order in no rec :" <<endl;
	preorder_norecursive(T);
	cout << "in order : " << endl;
	inorder_recursive(T);
	cout << "in order in no rec : " << endl;
	inorder_norecursive(T);
	cout << "post order : " << endl;
	postorder_recursive(T);
	cout << "post order in no rec : " << endl;
	postorder_norecursive(T);
	cout << " level order : " << endl;
	levelorder(T);
	cout << "destory tree " << endl;
	destroy_tree(T);




	return 0;
}