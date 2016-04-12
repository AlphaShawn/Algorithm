/**
 *  Problem:    Poj - 1135
 *	Algorithm:  Dijkstra
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.4.12
 * 	Language:  	C++11
 *
 * 	Description:  
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
 * Priority queue. 
 * Referencing distance vector from dijkstra. 
 */
class PriorityQueue
{
public:
	PriorityQueue(const vector<int> &dis)
		:distance(dis)
	{
		for (int i = 0; i < MAX_SIZE; i++)
			q[i] = -1;
		_size = 0;
	}

	int size()
	{
		return _size;
	}

	/*
	 * Return the front value in the queue.
	 * If there is no element in the queue, return -1;
	 */
	int front()
	{
		if (_size >= START_INDEX)
			return q[START_INDEX];
		return -1;
	}

	void pop()
	{
		/*no element exist. do nothing*/
		if (_size < START_INDEX) return;

		swap(START_INDEX,_size);
		q[_size] = -1;
		_size--;
		down(START_INDEX);
	}

	void insert(int v)
	{
		_size++;
		q[_size] = v;
		pos[v] = _size;
		up(_size);
	}

	void update(int v)
	{
		up(pos[v]);
	}
private:

	void up(int index)
	{
		while (index > START_INDEX)
		{
			/*if value of index is smaller than it father, then swap*/
			if (distance[q[index]] < distance[q[index / 2]])
				swap(index, index / 2);
			index /= 2;
		}
	}

	void down(int index)
	{
		while (index <= _size)
		{
			int l = 0xfffffff, r = 0xfffffff;
			/*boundry check*/
			if (index * 2 <= _size)
				l = distance[q[index * 2]];
			if (index * 2 + 1 <= _size)
				r = distance[q[index * 2 + 1]];

			int Min = min(l, r);
			if (Min > distance[q[index]])			/*if the value of index is smaller than both it son, break*/
				break;
			/*pick the smallest one to swap*/
			if (l < r)						
			{
				swap(index * 2, index);
				index = index * 2;
			}
			else
			{
				swap(index * 2 + 1, index);
				index = index * 2 + 1;
			}
		}
	}

	void swap(int i, int j)
	{
		int v1 = q[i], v2 = q[j];
		q[i] = v2;
		q[j] = v1;
		pos[v1] = j;
		pos[v2] = i;
	}

	const static int MAX_SIZE = 1000;
	const static int START_INDEX = 1;
	
	/*size of q*/
	int _size;
	/*priority_queue, start from 1*/
	int q[MAX_SIZE];
	/*record the vertexs' position in q*/
	int pos[MAX_SIZE];
	const vector<int> &distance;
};


vector<int> Dijkstra_Heap(adjacent_list &G, int s)
{
	const int INT_INF = 0x7fffffff;
	std::vector<int> dis(G.size, INT_INF);
	dis[s] = 0;

	/**  color:
	 *	0: not visited
	 *	1: will visited
	 *  2: reached
	 */	
	std::vector<short> color(G.size);
	
	PriorityQueue Q(dis);

	Q.insert(s);
	color[s] = 1;

	while (Q.size() > 0)
	{
		int now = Q.front();
		Q.pop();
		/*loop the next vertex link with now*/
		for(int i = G.pos[now]; i != -1; i = G.pre[i])
		{
			int next = G.v[i];			/*get next vertex*/
			
			int w = G.w[i];				/*get the weight of the edge*/
			if (w + dis[now] < dis[next])
			{
				dis[next] = w + dis[now];
				if (color[next] == 0)	/*not in the priority_queue*/
				{
					color[next] = 1;
					Q.insert(next);
				}
				else if (color[next] == 1) /*already in the priority_queue, update the position*/
					Q.update(next);
			}
		}
		/*set the color to reached*/
		color[now] = 2;
	}	
	return dis;
}


vector<int> Dijkstra_Normal(adjacent_list &G, int s)
{
	const int INT_INF = 0x7fffffff;
	std::vector<int> dis(G.size, INT_INF);
	std::vector<bool> visited(G.size);
	dis[s] = 0;
	for(int i = 0; i < G.size; ++i)
	{
		int now = -1, td = INT_INF;
		for(int j = 0; j < G.size; ++j)
			if( !visited[j] && dis[j] < td )
			{
				now = j;
				td = dis[j];
			}
		if( now == -1 )
			break;
		visited[now] = true;
		for(int j = G.pos[now]; j != -1; j = G.pre[j])
		{
			int next = G.v[j];
			if(!visited[next] && dis[next] > dis[now]+G.w[j])
				dis[next] = dis[now] + G.w[j];
		}
	}
	return dis;
}

int main() {
	int N,M;
	int k = 0;
	while(cin>>N>>M) {
		if( N == 0 && M == 0 )
			return 0;
		k++;
		adjacent_list G(N);
		for(int i = 0; i < M; ++i) {
			int a,b,t;
			std::cin>>a>>b>>t;
			G.add_edge(a-1,b-1,t);
			G.add_edge(b-1,a-1,t);
		}
		vector<int> dis = Dijkstra_Heap(G,0);
		double max1 = dis[0];
		int p = 0;
		for(int i = 0; i < dis.size(); ++i) {
			if( max1 < dis[i] ) {
				max1 = dis[i];
				p = i;
			}
		}
		double max2 = -1;
		int p1,p2;
		for(int i = 0; i <G.size; ++i)
			for(int j = G.pos[i]; j != -1; j = G.pre[j]) {
				if( max2 < dis[i] + dis[G.v[j]] + G.w[j] ) 
				{
					max2 = dis[i] + dis[G.v[j]] + G.w[j];
					p1 = i;
					p2 = G.v[j];
				}
			}
		max2 = max2 / 2;
		std::cout<<"System #"<<k<<std::endl;
		if( !(max1 < max2) ) {
			printf("The last domino falls after %.1f seconds, at key domino %d.\n\n", max1, p + 1);
		}
		else {
			printf("The last domino falls after %.1f seconds, between key dominoes %d and %d.\n\n", max2, p1 + 1, p2 + 1);	
		}
	}

}