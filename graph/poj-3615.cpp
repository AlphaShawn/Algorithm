/**
 *  Problem:    Poj - 3615
 *	Algorithm:  Floyd
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.4.13
 * 	Language:  	C++11
 *
 * 	Description:  
 * 				have to use scanf and printf to speed up input and output.
 */
#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

#define MAX(x,y) (x)>(y)?(x):(y)
#define MIN(x,y) (x)>(y)?(y):(x)


/**
* map: the adjacent matrix of graph
* return: map[i][j] means the shortest path weight value of i->j
*/
void Floyd(std::vector<std::vector<int> > &map) {
	int size = map.size();
	for(int k = 0; k < size; ++k)
		for(int i = 0;  i < size; ++i)
			for(int j = 0; j < size; ++j) {
				if( k == i || k == j )
					continue;
				if(map[i][k] == -1 || map[k][j] == -1)
					continue;
				if(map[i][j] == -1)
					map[i][j] = MAX(map[i][k], map[k][j]);
				else 
			  		map[i][j] = MIN(map[i][j], MAX(map[i][k],map[k][j]));
		  	}
}


int main()
{
	int N, M, T;
	while(cin>>N>>M>>T) {
	    vector<vector<int> > map(N, vector<int>(N,-1));
	    for(int i = 0; i < M; ++i) {
	    	int a, b, t;
	    	//cin>>a>>b>>t;
	    	scanf("%d %d %d", &a, &b, &t);
	    	map[a-1][b-1] = t;
	    }
	    Floyd(map);
	    for(int i = 0; i < T; ++i) {
	    	int a, b;
	    	scanf("%d %d", &a, &b);
	    	//cin>>a>>b;
	    	printf("%d\n", map[a-1][b-1]);
	    	//cout<<map[a-1][b-1]<<endl;
	    }
	}
	return 0;
}
