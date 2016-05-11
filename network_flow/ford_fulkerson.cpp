/**
 *  Algorithm : Ford-Fulkerson
 *  
 *  Author: 	Alpha Xiao
 * 	Date  :		2016.5.11
 * 	Language:  	C++11
 *
 * 	Description:  
 * 				  Using adjacent_matrix
 *
 */

#include <iostream>
#include <vector>
#include <queue>

#define INTMAX 0x7fffffff
#define min(x,y) (x)>(y)?(y):(x)

/**
 * store graph with n nodes, m edges
 */
class Network{
public:
	Network(int tn, int tm = 0) 
		:c(n,std::vector<int>(n,0)), f(n,std::vector<int>(n,0)), n(tn), m(tm), maxFlow(0)
	{}


	void createResidual() {
		r = c;
	}

	int n, m;
	std::vector<std::vector<int>> c;
	std::vector<std::vector<int>> f;
	std::vector<std::vector<int>> r;
	int maxFlow;
};


void Ford_Fulkerson(Network &G, int s, int t) {
	
	G.createResidual();
	while(true) {
		std::vector<int> path(G.n, -1);
		std::vector<int> bflow(G.n, INTMAX);
		std::queue<int> Q;
		Q.push(s);
		while(path[t] == -1 && !Q.empty()) {
			int now = Q.front();
			Q.pop();
			for(int i = 1; i < G.n; ++i) {
				if( i == now )
					continue;
				if(path[i] == -1 && G.r[now][i] > 0) {
					path[i] = now;
					bflow[i] = min(G.r[now][i], bflow[now]);
					Q.push(i);
				} 
			}
		}
		//calculate delta
		if(path[t] == -1) 
			break;
		int minFlow = bflow[t];
		int now = t, pre;
		while(now != s) {
			now = path[now];
			minFlow = min(minFlow, bflow[now]);
		}
		
		//update R	
		now = path[t];
		pre = t;
		while(now != -1) {
			G.r[now][pre] -= minFlow;
			G.r[pre][now] += minFlow;
			G.f[now][pre] += minFlow;
			G.f[pre][now] -= minFlow;
			pre = now;
			now = path[now];
		}	

		G.maxFlow += minFlow;
	}
}

//test
int main() {
	Network G(5);
	G.c[1][2] = 1000000;
	G.c[2][4] = 1000000;
	G.c[1][3] = 1000000;
	G.c[3][4] = 1000000;
	G.c[2][3] = 1;
	Ford_Fulkerson(G, 1, 4);
	printf("%d\n", G.maxFlow);
}