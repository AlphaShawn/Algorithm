/**
 *	Algorithm:  Kruskal - Minimum Spanning tree
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.4.5
 * 	Language:  	C++11
 *
 * 	Description:  
 * 				  
 *
 *  TODO:
 *   	support more parameter type
 *
 *  Update:  
 *      4.8  compare bug.
 */

#include <iostream>
#include <vector>
#include <algorithm>

#define INTMAX 0x7fffffff

struct edge
{
	int from, to;
	int w;
	static bool compare(const edge &lhs, const edge &rhs) {
		return lhs.w > rhs.w ? 0 : 1;
	}
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

private:

	int findFather(int x)
	{
		if(vec[x] < 0)
			return x;
		else 
			/* path compression */
			return vec[x] = findFather(vec[x]);
	}

	std::vector<int> vec;
};

/**
 * 
 */
std::vector<edge> Kruskal(std::vector<edge> &G, int v) {

	std::sort(G.begin(), G.end(), edge::compare);
	UnionSet U(v);
	std::vector<edge> ans;
	int k = -1;
	while(ans.size() != v-1) {
		++k;
		if( U.isInSameSet(G[k].from, G[k].to) )
			continue;
		ans.push_back(G[k]);
		U.union_ele(G[k].from, G[k].to);
	}
	return ans;
}

int main()
{

}