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
	/**
	 * Constructor. 
	 * Using data, distance to leaf node, left\right child pointers
	 */
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
	/**
	 * Empty constructor
	 */
	Leftist_Tree()
		:root(NULL)
	{}

	/**
	 * Constructor. 
	 * Construct a tree with one node.
	 */
	Leftist_Tree(int x)
	{
		root = new Node(x, 0, NULL, NULL);
	}

	/**
	 * Insert x into tree.
	 * First construct a empty node then merge into current tree.
	 * @param  x value of the node
	 */
	bool insert(int x){
		Node* node = new Node(x, 0, NULL, NULL);
		root = _merge(root, node);
		return true;
	}


	/**
	 * Remove the root node and return its value.
	 * Merge root's left and right child tree.
	 * @return value of root.
	 */
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


	/**
	 * Get the root value
	 * @return root value 
	 */
	int top(){
		if(root != NULL)
			return root->data;
		else
			throw std::runtime_error("empty tree");
	}


	/**
	 * Merge two tree. using private method _merge
	 * @param rht Tree to be merged.
	 */
	void merge(Leftist_Tree &rht){
		root = _merge(root, rht.root);
	}


	/**
	 * print tree elements by recursion.
	 */
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


	/**
	 * Free space. 
	 */
	~Leftist_Tree()
	{
		if(root)
			_free(root);
	}
private:

	/**
	 * Merge two tree
	 * @param  l root of left tree
	 * @param  r root of right tree
	 * @return   root pointer of merged tree.
	 */
	Node* _merge(Node* &l, Node* &r){
		if( l == NULL || r == NULL)			/* one of the root is empty, return another */
			return l == NULL? r:l;
		if(l->data > r->data)				/* Let the left tree's root value is smaller */
			std::swap(l, r);
		l->right = _merge(l->right, r);		/* recursively merge tree. */

		if(l->left == NULL || l->left->dist < l->right->dist)	/* balance tree according to dist to leaf node*/
			std::swap(l->left, l->right);

		if(l->right == NULL)				/* update root distance value*/
			l->dist = 0;
		else
			l->dist = l->right->dist + 1;
		return l;
	}


	/**
	 * Free space by recursive.
	 * @param t pointer to node which is to be freeed.
	 */
	void _free(Node* t)
	{
		if(t->left)
			_free(t->left);
		if(t->right)
			_free(t->right);
		free(t);
	}

	/* private variable.*/
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
