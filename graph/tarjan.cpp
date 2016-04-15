/**
 *	Algorithm:  tarjan
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.4.14
 * 	Language:  	C++11
 *
 * 	Description:  
 * 				  Using adjacent_list
 *
 *  TODO:
 *  	1.test  	poj 2762
 */

#include <iostream>
#include <vector>
#include <stack>

#define MIN(x,y) (x)>(y)?(y):(x)

/**
 * store graph with n nodes, m edges
 */
class adjacent_list{
public:

	adjacent_list(int n)
		:pos(n, -1), size(n), flag(0)
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


class tarjan{
public:
	tarjan(adjacent_list &tG)
		:G(tG)
	{}

	void work() {
		visited.resize(G.size, 0);
		dfn.resize(G.size, 0);
		low.resize(G.size, 0);
		flag = 0;
		SCC.clear();
		for(int i = 0; i < G.size; ++i) {
			dfs(i);
		}
	}

	std::vector<int>& getDFN(){
		return dfn;
	}

	std::vector<int>& getLOW(){
		return low;
	}

	std::vector<std::vector<int> >& getStrongConnectedComponent(){
		return SCC;
	}

private:

	void dfs(int now) {
		dfn[now] = low[now] = ++flag;
		dfsStack.push(now);
		visited[now] = 1;
		for(int i = G.pos[now]; i != -1; i = G.pre[i]) {
			int next = G.v[now];
			if( !visited[next] ) {
				dfs(next);
				low[now] = MIN(low[now], low[next]);
			} else {
				low[now] = MIN(low[now], dfn[next]);
			}
		}
		if(dfn[now] == low[now]) {
			std::vector<int> tVec;
			int t;
			do {
				t = dfsStack.top();
				dfsStack.pop();
				tVec.push_back(t);	
				visited[t] = 2;
			} while(t != now);
			SCC.push_back(tVec);
		}
	}

	adjacent_list &G;			// graph, addjacent list
	std::vector<short> visited;	// 0:not visited  1:in stack  2:visited and out of stack
	std::vector<int> dfn;		// the dfs time 
	std::vector<int> low;		// the lowest time of dfs regard to connected vertex
	std::stack<int> dfsStack;	// dfs stack
	std::vector<std::vector<int> > SCC; //  store the strongly connected components
	int flag;					// time of dfs
};


int main()
{

}