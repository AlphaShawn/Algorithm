/**
 *	Algorithm:  max_heap
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.3.18
 * 	Language:  	C++11
 *
 * 	Description:  A max_heap class.
 * 					1.support insert(), pop(), top(), empty() operation
 * 					2.support quick build heap.
 * 				  Use array to implement binary tree. 
 * 				  Array use std::vector.
 */


#include <iostream>
#include <vector>

/**
 * Because of index of vector start from 0,
 * the computation of left_son, right_son, parent is slightly different.
 */
#define LEFT_SON(node) ((node<<1)+1)
#define RIGHT_SON(node) ((node<<1)+2)
#define PARENT(node) ((node-1)>>1)

class Heap 
{
public:
	/**
	 * empty constructor
	 */
	Heap(){}

	Heap(std::vector<int> tvec)
		:vec(tvec)
	{
		for(int i = vec.size()>>1; i>=0; i--)
		{
			printHeap();
			shiftDown(i);
		}
	}


	bool insert(int x) {
		vec.push_back(x);
		shiftUp(vec.size()-1);
		return true;
	}

	int pop(){
		int ans = vec[0];
		std::swap(vec[0], vec[vec.size()-1]);
		vec.pop_back();
		shiftDown(0);
		return ans;
	}

	int top(){
		return vec[0];
	}

	bool empty(){
		return vec.empty();
	}


	void printHeap() {
		for(int i = 0; i < vec.size(); i++)
			std::cout<<vec[i]<<' ';
		std::cout<<std::endl;
	}

private:

	void shiftDown(int p) {
		int i = p, size = vec.size();
		while( i < size )
		{
			int left = LEFT_SON(i);
			int right = RIGHT_SON(i);
			int k = i;
			if( left < size && vec[k] < vec[left] )
				k = left;
			if( right < size && vec[k] < vec[right] )
				k = right;
			if( k != i)
			{
				std::swap(vec[i], vec[k]);
				i = k;
			}
			else
				break;
		} 
	}

	void shiftUp(int node){
		while( node > 0)
		{
			int p = PARENT(node);
			if(vec[p] < vec[node])
			{
				std::swap(vec[node], vec[p]);
				node = p;
			}
			else
				break;
		}
	}

	/**
	 * vec: array store element of heap.
	 */
	std::vector<int> vec;
};

/*
	simple test.
 */

int main()
{
	std::vector<int> tvec;
	tvec.push_back(3);
	tvec.push_back(1);
	tvec.push_back(2);
	tvec.push_back(5);
	tvec.push_back(9);
	tvec.push_back(8);
	tvec.push_back(7);
	Heap h(tvec);
	h.printHeap();
	return 0;
}
