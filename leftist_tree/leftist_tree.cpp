/**
 *	Algorithm:  Leftist_Tree(heap)
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.3.18
 * 	Language:  	C++11
 *
 * 	Description:  A Leftist tree(heap) class.
 * 					1.support insert(), pop(), top(), empty() operation
 * 					2.support quick merge.
 * 				  
 * 	TODO:	
 * 		  Test http://acm.hdu.edu.cn/showproblem.php?pid=1512
 *  	  detailed comments.
 */

#include <iostream>
#include <exception>

struct Node
{
	Node(int d, int dis, Node* l, Node* r)
		:data(d), dist(dis), left(l), right(r)
	{}
	int data;
	int dist;
	Node *left, *right;
};

class Leftist_Tree
{
public:
	Leftist_Tree()
		:root(NULL)
	{}

	bool insert(int x){
		Node* node = new Node(x, 0, NULL, NULL);
		root = _merge(root, node);
		return true;
	}

	int pop(){
		int ans = root->data;
		Node* tmp = root;
		if(tmp->left == NULL)
		{
			free(root);
			root = NULL;
		}
		else
		{
			root = _merge(root->left, root->right);
			free(tmp);
		}
		return ans;
	}

	int top(){
		if(root != NULL)
			return root->data;
		else
			throw std::runtime_error("empty tree");
	}

	void merge(Leftist_Tree &rht){
		root = _merge(root, rht.root);
	}

	~Leftist_Tree()
	{
		free(root);
	}
private:

	Node* _merge(Node* &l, Node* &r){
		if( l == NULL || r == NULL)
			return l == NULL? r:l;
		if(l->data > r->data)
			std::swap(l, r);
		l->right = _merge(l->right, r);

		if(l->left == NULL || l->left->dist < l->right->dist)
				swap(l->left, r->right)

		if(l->right == NULL)
			l->dist = 0;
		else
			l->dist = l->right.dist + 1;
		return l;
	}

	void free(Node* t)
	{
		if(t->left)
			free(t->left);
		if(t->right)
			free(t->right);
		free(t);
	}

	Node* root;
};

int main()
{

}