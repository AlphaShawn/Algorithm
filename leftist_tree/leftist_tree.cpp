/**
 *	Algorithm:  Leftist_Tree(heap)
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.3.19
 * 	Language:  	C++11
 *
 * 	Description:  A Leftist tree(heap) class.
 * 					1.support insert(), pop(), top(), empty() operation
 * 					2.support quick merge.
 * 				  
 * 	TODO:	
 * 		  Test http://acm.hdu.edu.cn/showproblem.php?pid=1512
 * 		  		
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

	Leftist_Tree(int x)
	{
		root = new Node(x, 0, NULL, NULL);
	}

	bool insert(int x){
		Node* node = new Node(x, 0, NULL, NULL);
		root = _merge(root, node);
		return true;
	}

	int pop(){
		int ans = root->data;
		Node* tmp = root;
		if(root->left == NULL)
			root = NULL;
		else
			root = _merge(root->left, root->right);			
		free(tmp);
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

	void print()
	{
		print_tree(root);
	}

	void print_tree(Node *node)
	{
		if(node == NULL) return;
		std::cout<<node->data<<' ';
		if(node->left)
		{
			std::cout<<"left:"<<node->left->data;
		}
		if(node->right)
		{
			std::cout<<"right:"<<node->right->data;
		}
		std::cout<<std::endl;
		print_tree(node->left);
		print_tree(node->right);
	}

	~Leftist_Tree()
	{
		if(root)
			_free(root);
	}
private:

	Node* _merge(Node* &l, Node* &r){
		if( l == NULL || r == NULL)
			return l == NULL? r:l;
		if(l->data > r->data)
			std::swap(l, r);
		l->right = _merge(l->right, r);

		if(l->left == NULL || l->left->dist < l->right->dist)
			std::swap(l->left, l->right);

		if(l->right == NULL)
			l->dist = 0;
		else
			l->dist = l->right->dist + 1;
		return l;
	}

	void _free(Node* t)
	{
		if(t->left)
			_free(t->left);
		if(t->right)
			_free(t->right);
		free(t);
	}

	Node* root;
};

int main()
{
	int N, M, t1, t2;
	std::cin>>N;
	std::vector<Leftist_Tree> T;
	for(int i=0; i<N; i++)
	{
		std::cin>>t1;
		T.push_back(Leftist_Tree(t1));
	}

}	
