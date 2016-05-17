/**
 *  Algorithm : sap
 *  
 *  Author: 	Alpha Xiao
 * 	Date  :		2016.5.17
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


void sap(Network &G, int s, int t) {
	G.createResidual();
	std::vector<int> level(G.n, 0);
	std::vector<int> gap(G.n, 0);
	std::vector<int> path(G.n, -1);
	gap[0] = G.n;
	path[s] = s;

	int now = s, v;
	while(level[s] < G.n) {
		for(v = 0; v < G.n; ++v) {
			if(G.r[now][v] > 0 && level[now] == level[v] + 1)
				break;
		}
		if( v < G.n) {					// find next level vertex
			path[v] = now;
			now = v;

			if( now == t ) {			//reach end vertex
				int minFlow = INTMAX;	// get augment amount
				for(int i = t; i != s; ) {
					int pre = path[i];
					minFlow = min(minFlow, G.r[pre][i]);
					i = pre;
				}
				G.maxFlow += minFlow;	// update R
				for(int i = t; i != s; ) {
					int pre = path[i];
					G.r[pre][i] -= minFlow;
					G.r[i][pre] += minFlow;
					G.f[pre][i] += minFlow;
					G.f[i][pre] -= minFlow;
					i = pre;
				}
				now = s;				// restart from source
			}
		} else {		 				//do not find
			gap[level[now]]--;
			if(gap[level[now]] == 0)
				break;

			int minLevel = G.n;			// get minimum level vertex
			for(int i = 0; i < G.n; ++i) {
				if(G.r[now][i] > 0 && level[i] < minLevel)
					minLevel = level[i];
			}

			level[now] = minLevel + 1;	// update now vertex level
			gap[level[now]]++;
			now = path[now];			//path[s] = s, so do not need special judge
		}

	}
}

//test
//
int main() {
	int N, F, D;
	while(std::cin>>N>>F>>D) {
		// [1,N*2] cows, [N*2+1,N*2+F] foods, [N*2+F+1, N*2+F+D] drinks, 0 source, N*2+F+D+1 t
		Network G(N * 2 + F + D + 2); 
		int s = 0, t = N * 2 + F + D + 1;
		for(int i = N * 2 + 1; i <= N * 2 + F; ++i)
			G.c[s][i] = 1;
		for(int i = N * 2 +F + 1; i <= N * 2 + F + D; ++i)
			G.c[i][t] = 1;
		for(int i = 1; i <= N; ++i)
			G.c[i][i+N] = 1;

		int a, b, tmp;
		for(int i = 1; i <= N; ++i) {
			scanf("%d %d", &a, &b);
			while(a--) {
				scanf("%d", &tmp);
				G.c[tmp + N * 2][i] = 1;
			}
			while(b--) {
				scanf("%d", &tmp);
				G.c[N + i][N * 2 + F + tmp] = 1;
			}
		}
		
		// for(int i = 0; i < G.n; ++i) {
		// 	for(int j = 0; j < G.n; ++j) {
		// 		printf("%d ", G.c[i][j]);
		// 	}
		// 	printf("%d\n");
		// }

		sap(G, s, t);
		printf("%d\n", G.maxFlow);
	}
}