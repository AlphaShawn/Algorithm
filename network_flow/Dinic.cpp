/**
 *  Algorithm : Dinic (Successive shortest augmenting path algo)
 *  
 *  Author: 	Alpha Xiao
 * 	Date  :		2016.5.13
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
		:level(n, -1), c(n,std::vector<int>(n,0)), f(n,std::vector<int>(n,0)), n(tn), m(tm), maxFlow(0)
	{}


	void createResidual() {
		r = c;
	}

	void updateLevelGraph() {
		std::queue<int> Q;
		Q.push(s);
		for(int i = 0; i < n; ++i) 
			level[i] = -1;
		level[s] = 1;
		while(!Q.empty()) {
			int now = Q.front();
			Q.pop();
			for(int i = 0; i < n; ++i) {
				if(i == now)
					continue;
				if(r[now][i] > 0 && level[i] == -1) {
					level[i] = level[now] + 1;
					Q.push(i);
				}
			}
		}
	}
	int n, m, s, t;
	std::vector<std::vector<int>> c;
	std::vector<std::vector<int>> f;
	std::vector<std::vector<int>> r;
	std::vector<int> level;
	int maxFlow;
};

int dfs(Network &G, const int &now, int flow) {
	if( now == G.t )
		return flow;
	int tf = flow;
	for(int i = 0; i < G.n; ++i) {
		if( i == now )
			continue;
		if( G.r[now][i] > 0 && G.level[i] == G.level[now] + 1) {
			int t = dfs(G, i, min(flow,G.r[now][i]));
			G.r[now][i] -= t;	//update R and F
			G.r[i][now] += t;
			G.f[now][i] += t;
			G.f[i][now] -= t;
			flow -= t;			//remaining flow
		}
	}
	return tf - flow;
}

void Dinic(Network &G) {
	
	G.createResidual();
	G.updateLevelGraph();
	// while t is still in the level graph, which mean s can reach t
	while(G.level[G.t] != -1) {
		G.maxFlow += dfs(G, G.s, INTMAX);	// find augumenting path and do augumenting at the same time.
		G.updateLevelGraph();
	}
}

//test
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
		G.s = s;
		G.t = t;
		Dinic(G);
		printf("%d\n", G.maxFlow);
	}
}