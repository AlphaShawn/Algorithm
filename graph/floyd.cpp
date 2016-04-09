/**
 *	Algorithm:  Floyd
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.4.9
 * 	Language:  	C++11
 *
 * 	Description:  
 * 				  Using adjacent_matrix
 *
 *  TODO:
 *  	1.test
 */

#include <iostream>

/**
 * map: the adjacent matrix of graph
 * return: map[i][j] means the shortest path weight value of i->j
 */
std::vector<std::vector<int>> Floyd(std::vector<std::vector<int>> map) {
	int size = map.size();
	for(int k = 0; k < size; ++k)
		for(int i = 0;  i < size; ++i)
			for(int j = 0; j < size; ++j) {
				if( k == i || k == j )
					continue;
				if( map[i][k] + map[k][j] < map[i][j] )
					map[i][j] = map[i][k] + map[k][j];
			}
	return map;
}


int main()
{

}