/**
 *	Algorithm:  Dijkstra
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.3.30
 * 	Language:  	C++11
 *
 * 	Description:  
 * 				  Using adjacent_list
 * 				  Normal version and Heap Version
 *
 *  TODO:
 *  	1.test
 */


#include <iostream>
#include <vector>
#include <queue>


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

	void down(int int)
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
	std::vector<short> color;
	
	PriorityQueue Q(distance);
	Q.insert(start);
	color[s] = 1;

	while (Q.size() > 0)
	{
		int now = Q.front();
		Q.pop();

		/*loop the next vertex link with now*/
		for(int i = G.pos[now]; i != -1; ++i)
		{
			int next = G.v[i];			/*get next vertex*/
			int w = G.w[i];				/*get the weight of the edge*/
			if (w + distance[now] < distance[next])
			{
				distance[next] = w + distance[now];
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
	std::vector<bool> visited;
	dis[s] = 0;
	for(int i = 0; i < G.size; ++i)
	{
		int now = -1, td;
		for(int j = 0; j < G.size; ++j)
			if(now == -1 || (dis[j] < td && !visited[j] ))
			{
				now = j;
				td = dis[j];
			}
		visited[now] = true;
		for(int j = G.pos[now]; j != -1; j = G.pre[j])
		{
			int next = G.v[j];
			if(dis[next] > dis[now]+G.w[j])
				dis[next] = dis[now] + G.w[j];
		}
	}
	return dis;
}