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
			for(int i = 0; i < G.n; ++i) {
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
		while(pre != s) {
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

		Ford_Fulkerson(G, s, t);
		printf("%d\n", G.maxFlow);
	}
}