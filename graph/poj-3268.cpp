/**
 * 	Problem:	poj-3268
 *	Algorithm:  SPFA
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.4.14
 * 	Language:  	C++11
 *
 */


#include <iostream>
#include <vector>
#include <stdio.h>
#include <queue>
using namespace std;


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

/**
 * SPFA
 * @param  s start vertex
 * @param  G Graph stored in adjacent list
 * @return  A vector store shortest distance from s to other vertex.
 */
std::vector<int> SPFA(int s, adjacent_list &G)
{
	/* store the distance from s to each vertex*/
	std::vector<int> dis(G.size, -1);
	dis[s] = 0;

	std::queue<int> Q;
	Q.push(s);

	std::vector<bool> inQueue(G.size, 0);
	inQueue[s] = true;

	while(!Q.empty())
	{
		int now = Q.front();
		Q.pop();
		for(int i = G.pos[now]; i!=-1; i = G.pre[i])
		{
			int next = G.v[i];
			/* shorten the distance, then add to queue. */
			if(dis[next] == -1 || dis[now] + G.w[i] < dis[next])
			{
				dis[next] = dis[now] + G.w[i];
				if(!inQueue[next])	
				{
					Q.push(next);
					inQueue[next] = true;
				}
			}
		}
		inQueue[now] = false;
	}
	return dis;
}

int main() {
	int N, M, X;
	
	while(cin>>N>>M>>X) {
		adjacent_list G(N), revG(N);
		for(int i = 0; i < M; ++i) {
			int a,b,t;
			std::cin>>a>>b>>t;
			G.add_edge(a-1,b-1,t);
			revG.add_edge(b-1,a-1,t);
		}
		vector<int> dis = SPFA(X-1, G);
		vector<int> revDis = SPFA(X-1, revG);
		int ans = -1;
		for(int i = 0; i < N; ++i) {
			ans = ans > dis[i] + revDis[i]?ans:dis[i] + revDis[i];
		}
		printf("%d\n", ans);
	}
}