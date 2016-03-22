/**
 *	Algorithm:  sort, quick-sort
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.3.22
 * 	Language:  	C++11
 *
 * 	Description:  
 * 				  quick-sort:  
 * 				  		1.implement two methods of partition.
 * 				  			normal partition and Dijkstra 3-way partitioning
 * 				  		2.randomized pivot.
 */

#include <iostream>
#include <vector>
#include <utility>

class Sort
{
public:
	static void sort(std::vector<int> &vec)
	{
		quick_sort(vec, 0, vec.size()-1);
	}

	static void quick_sort(std::vector<int> &vec, int l, int r)
	{
		if( l >= r )
			return;
		//randomize
		int t = rand()%(r-l+1)+l;
		std::swap(vec[l], vec[t]);
		//int p =  partition(vec, l, r);
		std::pair<int, int> p = three_way_partition(vec, l ,r);
		quick_sort(vec, l, p.first-1);
		quick_sort(vec, p.second, r);
	}

	/**
	 * invariant:   [low, low] : x
	 * 				[low+1, l] : <= x
	 * 				[l, r]	   : to be determined
	 * 				[r+1, high]: > x
	 */
	static int partition(std::vector<int> &vec, int l, int r)
	{
		int low = l;
		int x = vec[l];
		while(r>l)
		{
			if(vec[r] <= x)
			{
				l++;
				std::swap(vec[l], vec[r]);
			}
			r--;
		}
		std::swap(vec[low], vec[l]);
		return l;
	}


	/**
	 * invariant: [low, pi-1] : < x
	 * 			  [pi, l-1]   : =x
	 * 			  [l, r]	  : to do determined
	 * 			  [r+1, high] : >x
	 */
	static std::pair<int, int> three_way_partition(std::vector<int> &vec, int l, int r)
	{
		int x = vec[l];
		int pi = l;
		while(l<r)
		{
			while(!(vec[l] > x) && l < r)
			{
				if(vec[l] < x)
				{
					std::swap(vec[l], vec[pi]);
					pi++;
				}
				l++;
			}
			while(vec[r] > x && r > l)
				r--;
			if( l < r )
			{
				std::swap(vec[l], vec[r]);
				r--;
			}
		}
		return std::make_pair(pi,l);
	}

private:

};


/*simple test*/
int main()
{
	int a[]={3,2,5,6,8,1,2,3,5,7,9,0,2,1,41,2312,512,32};
	std::vector<int> vec(a,a+17);
	Sort::sort(vec);
	for(int i=0;i<vec.size();i++)
		std::cout<<vec[i]<<' ';
}