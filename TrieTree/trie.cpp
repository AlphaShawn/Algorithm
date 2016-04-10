/**
 *	Algorithm:  trie tree
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.4.10
 * 	Language:  	C++11
 *
 * 	Description:  
 *  			support alphabet trie
 */
#include <iostream>
#include <vector>
#include <string>

#define MAX_NODE_SIZE 26

struct TrieNode
{
	TrieNode(int c = 0):count(c) {
		for(int i = 0; i < MAX_NODE_SIZE; ++i)
			child[i] = NULL;
	}

	int count;
	TrieNode *child[MAX_NODE_SIZE]; 
};

class Trie {
public:
	Trie()
	{
		root = new TrieNode();
	}

	bool insert(std::string s){
		TrieNode *now = root;
		for(int i = 0; i < s.size(); ++i) {
			int k = s[i] - 'a';
			if(now->child[k] != NULL)	// the prefix exists, update count
				now->child[k]->count++;
			else {
				now->child[k] = new TrieNode(1);
			}
			now = now->child[k];
		}
		return true;
	}
	int  search(std::string s) {
		TrieNode* now = root;
		for(int i = 0; i < s.size(); ++i) {
			int k = s[i] - 'a';
			if(now->child[k] == NULL)
				return 0;
			now = now->child[k];
		}
		return now->count;
	}

	~Trie()
	{
		_free(root);
	}

private:
	TrieNode *root;

	void _free(TrieNode *now) {
		for(int i = 0; i < MAX_NODE_SIZE; ++i)
			if(now->child[i])
				_free(now->child[i]);
		delete now;
	}
};

int main()
{
	int N, M;
	while(std::cin>>N) {
		std::string t;
		Trie T;
		for(int i = 0; i < N; ++i) {
			std::cin>>t;
			T.insert(t);
		}

		std::cin>>M;
		for(int i = 0; i < N; ++i) {
			std::cin>>t;
			std::cout<<T.search(t)<<'\n';
		}		
	}
}