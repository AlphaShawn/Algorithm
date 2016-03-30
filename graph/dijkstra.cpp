/**
 *	Algorithm:  Dijkstra
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.3.30
 * 	Language:  	C++11
 *
 * 	Description:  
 * 				  Using adjacent_list
 *
 *  TODO:
 *  	1.detailed comments
 *  	2.test
 */


#include <iostream>
#include <vector>
#include <queue>


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

vector<int> Dijkstra(adjacent_list &G, int s)
{
	const int INT_INF = 0x7fffffff;
	std::vector<int> dis(G.size, INT_INF);
	std::vector<bool> visited;
	dis[s] = 0;
	for(int i = 0; i < G.size; ++i)
	{
		int now = -1, td;
		for(int j = 0; j < G.size; ++j)
			if(now == -1 || (dis[j] < td && !visited[j] ))
			{
				now = j;
				td = dis[j];
			}
		visited[now] = true;
		for(int j = G.pos[now]; j != -1; j = G.pre[j])
		{
			int next = G.v[j];
			if(dis[next] > dis[now]+G.w[j])
				dis[next] = dis[now] + G.w[j];
		}
	}
	return dis;
}