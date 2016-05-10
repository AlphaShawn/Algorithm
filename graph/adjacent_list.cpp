/**
 *  Adjacent_list
 *  Author: Alpha Xiao
 *
 * 	
 *  update:
 *  	5.10  alpha xiao
 *  		  1. add assignment operator
 *  		  2. add printGraph() method
 */

#include <iostream>
#include <vector>
#include <stdio.h>


/**
 * store graph with n nodes, m edges
 */
class adjacent_list{
public:

	adjacent_list(int n)
		:pos(n, -1), flag(0)
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

	adjacent_list& operator=(const adjacent_list &rhs) {
		flag = rhs.flag;
		pos = rhs.pos;
		pre = rhs.pos;
		v = rhs.pos;
		w = rhs.w;
		return *this;
	}

	/**
	 * print the graph
	 */
	void printGraph() {
		for(int i = 0; i < pos.size(); ++i) {
			for(int j = pos[i]; j != -1; j = pre[j]) {
				printf("from:%d-to:%d- weight:%d\n", i, v[j], w[j]);
			}
		}
	}

	int flag;				//size of total list, = pre.size() = v.size() = w.size()
	std::vector<int> pos;	//start position of each node. space O(n)
	std::vector<int> pre;	//previous edge, space O(m), value:-1 mean no previous edge
	std::vector<int> v;		//correpsoned node, space O(m)
	std::vector<int> w;		//weight of the edge, space O(m)
};


/**
 * test
 */
int main() {
	adjacent_list G(6);
	G.add_edge(1,2,3);
	G.add_edge(2,3,4);
	adjacent_list tG = G;

	tG.add_edge(4,5,4);
	G.printGraph();
	printf("\n");
	tG.printGraph();

	return 0;
}