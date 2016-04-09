/**
 *	Algorithm:  Prim - Minimum Spanning tree
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.4.5
 * 	Language:  	C++11
 *
 * 	Description:  
 * 				  
 *
 *  TODO:
 *  	using heap to reduce time complex
 *
 *  Update:
 *  	4.9   fixed bugs.
 */

#include <iostream>
#include <vector>


class adjacent_list{
public:

	adjacent_list(int n)
		:pos(n, -1), flag(0), size(n)
	{}

	/**
	 * add edge x->y with weight = tw
	 */
	void add_edge(int x, int y, int tw = 0)
	{
		pre.push_back(pos[x]);
		v.push_back(y);
		w.push_back(tw);
		pos[x] = flag++;
	}

	int size;
	int flag;				//size of total list, = pre.size() = v.size() = w.size()
	std::vector<int> pos;	//start position of each node. space O(n)
	std::vector<int> pre;	//previous edge, space O(m), value:-1 mean no previous edge
	std::vector<int> v;		//correpsoned node, space O(m)
	std::vector<int> w;		//weight of the edge, space O(m)
};

#define INTMAX 0x7fffffff
/**
 * [Prim description]
 * @param  G graph G(V,E)
 * @return   a minimum spanning tree built on G
 */
adjacent_list Prim(adjacent_list &G) {

	std::vector<int> dist(G.size, INTMAX);
	std::vector<int> parent(G.size, -1);		/* record the edge of MST */
	std::vector<bool> S(G.size, false);
	dist[0] = 0;

	for(int i = 0; i < G.size; ++i) {
		int min = INTMAX;
		int next;
		for(int j = 0; j < G.size; ++j) //pick minimum vertex into tree
		if(min > dist[j] && !S[j]) {
			next = j;
			min = dist[j];
		}

		S[next] = true;

		/* update dist array using the minimum vertex */
		for(int j = G.pos[next]; j != -1; j = G.pre[j]) {
			int node = G.v[j];
			int value = G.w[j];
			if(S[node])
				continue; 
			if( dist[node] > value + dist[next] ) {
				dist[node] = value + dist[next];
				parent[node] = next;
			}
		}
	}

	adjacent_list ans(G.size);
	for(int i = 0; i < G.size; ++i)
	if(parent[i] != -1)
	{
		ans.add_edge(i, parent[i]);
		ans.add_edge(parent[i], i);
	}
}


int main()
{

}