/**
 *  Algorithm : MPLA - minimum path length augmenting
 *  
 *  Author: 	Alpha Xiao
 * 	Date  :		2016.5.12
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

	void updateLevelGraph(int s) {
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
	int n, m;
	std::vector<std::vector<int>> c;
	std::vector<std::vector<int>> f;
	std::vector<std::vector<int>> r;
	std::vector<int> level;
	int maxFlow;
};

// find a path from now -> t according to G.level
bool dfs(Network &G, const int &now, const int &t, std::vector<int> &path) {
	if( now == t)
		return true;
	for(int i = 0; i < G.n; ++i) {
		if(i == now)
			continue;
		if(G.r[now][i] > 0 && G.level[now] + 1 == G.level[i]) {
			path[i] = now;
			if(dfs(G, i, t, path))
				return true;
		}
	} 
	return false;
}

void augment(Network &G, const std::vector<int> &path, const int &s, const int &t) {

	//get min flow
	int now = path[t];
	int next = t;
	int minFlow = INTMAX;
	while(next != s) {
		minFlow = min(minFlow, G.r[now][next]);
		next = now;
		now = path[now];
	}	

	// update R
	now = path[t];
	next = t;
	while(next != s) {
		G.r[now][next] -= minFlow;
		G.r[next][now] += minFlow;
		G.f[now][next] += minFlow;
		G.f[next][now] -= minFlow;
		next = now;
		now = path[now];
	}	
	G.maxFlow += minFlow;
}

void Ford_Fulkerson(Network &G, int s, int t) {
	
	G.createResidual();
	G.updateLevelGraph(s);
	// while t is still in the level graph, which mean s can reach t
	while(G.level[t] != -1) {
		while(true) {
			std::vector<int> path(G.n, -1);
			bool flag = dfs(G, s, t, path);
			if(!flag)
				break;
			augment(G, path, s, t);
		}
		G.updateLevelGraph(s);
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

		Ford_Fulkerson(G, s, t);
		printf("%d\n", G.maxFlow);
	}
}