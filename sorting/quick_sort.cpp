/**
 *	Algorithm:  sort, quick-sort
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.3.22
 * 	Language:  	C++11
 *
 * 	Description:  
 * 				  
 * 	TODO:	
 * 		 	three-way-partition.
 */

#include <iostream>
#include <vector>


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
		int p =  partition(vec, l, r, l);
		quick_sort(vec, l, p-1);
		quick_sort(vec, p+1, r);
	}

	static int partition(std::vector<int> &vec, int l, int r, int pivot)
	{
		std::swap(vec[l], vec[pivot]);
		l++;
		while(l<r)
		{
			while(vec[l] <= vec[pivot] && l<r) l++;
			while(vec[r] >= vec[pivot] && r>l) r--;
			if(l<=r)
			{
				std::swap(vec[l],vec[r]);
				l++,
				r--;
			}
		}
		std::swap(vec[pivot], vec[r]);
		return r;
	}

	static pair<int, int> three_way_partition(std::vector<int> &vec, int l, int r, int pivot)
	{

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