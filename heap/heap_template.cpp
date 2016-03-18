/**
 *	Algorithm:  heap_template
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.3.18
 * 	Language:  	C++11
 *
 * 	Description:  Heap implement in template class.
 * 					1. support insert(), pop(), top(), empty() operation
 * 					2. support quick build heap.
 * 					3. order of element based on compare function user given.
 * 				  
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

template<class type>
class Heap 
{
public:

	Heap(bool(*c)(type, type))
		:cmp(c)
	{}

	/**
	 * 
	 */
	Heap(std::vector<type> tvec, bool(*c)(type, type))
		:vec(tvec), cmp(c)
	{
		for(int i = vec.size()>>1; i>=0; i--)
			shiftDown(i);
	}


	bool insert(type x) {
		vec.push_back(x);
		shiftUp(vec.size()-1);
		return true;
	}

	type pop(){
		type ans = vec[0];
		std::swap(vec[0], vec[vec.size()-1]);
		vec.pop_back();
		shiftDown(0);
		return ans;
	}

	type top(){
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
			if( left < size && cmp(vec[left], vec[k]) )
				k = left;
			if( right < size && cmp(vec[right], vec[k]) )
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
			if( cmp(vec[node], vec[p]) )
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
	std::vector<type> vec;
	bool (*cmp)(type, type);
};

/*
	simple test.
 */

bool cmp(int x,int y)
{
	return x<y? true:false;
}

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
	Heap<int> h(tvec, cmp);
	h.printHeap();
	std::cout<<"finished.";
	return 0;
}
