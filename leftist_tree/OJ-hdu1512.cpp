/**
 * OJ-HDU-1512 http://acm.hdu.edu.cn/showproblem.php?pid=1512
 * Status:Exe.Time:3900MS	Exe.Memory:15548K	
 * Author: Xiao YuWei
 * Date: 2016.3.27
 *
 * Algorithm:
 * 			Leftist tree + union-find-set
 * 
 * Note:
 * 		Organization of code is not very well.
 */

#include <iostream>
#include <vector>

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
		//if(root)
		//	_free(root);
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
		if(l->data < r->data)				/* Let the left tree's root value is larger */
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


class UnionSet
{
public:
	/**
	 * Constructor.
	 * The initialize value of each element is -1,
	 * which means they are the only element in 
	 * their set.
	 */
	UnionSet(int size)
		:vec(size+1, -1)
	{}

	void union_ele(int x,int y)
	{
		int xf = findFather(x);
		int yf = findFather(y);
		if( xf == yf )
			return ;
		//xf size is smaller, swap them, then xf is bigger
		if(vec[xf] > vec[yf])
			std::swap(xf,yf);
		//then union yf to xf
		vec[xf] = vec[xf] + vec[yf];
		vec[yf] = xf;
	}

	bool isInSameSet(int x,int y)
	{
		return findFather(x) == findFather(y);
	}

	int findFather(int x)
	{
		if(vec[x] < 0)
			return x;
		else 
			/* path compression */
			return vec[x] = findFather(vec[x]);
	}
private:
	std::vector<int> vec;
};

int main()
{
	int N, M, t1, t2;
	while(std::cin>>N)
	{
		
		UnionSet S(N);
		std::vector<Leftist_Tree> T;
		for(int i=0; i<N; i++)
		{

			std::cin>>t1;
			T.push_back(Leftist_Tree(t1));
		}
		std::cin>>M;
		for(int i=0; i<M; i++)
		{
			std::cin>>t1>>t2;
			t1--;t2--;
			if(S.isInSameSet(t1,t2))
			{
				std::cout<<-1<<'\n';
				continue;
			}
			else
			{
				int t1p = S.findFather(t1);
				int t2p = S.findFather(t2);
				//std::cout<<t1p<<':'<<T[t1p].top()<<' '<<t2p<<':'<<T[t2p].top()<<'\n';
				T[t1p].insert(T[t1p].pop()/2);
				T[t2p].insert(T[t2p].pop()/2);
				T[t1p].merge(T[t2p]);
				S.union_ele(t1,t2);
				if(S.findFather(t1) != t1p)
					T[S.findFather(t1)] = T[t1p];
				std::cout<<T[t1p].top()<<'\n';
			}
		}
	}
}