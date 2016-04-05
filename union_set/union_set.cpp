/**
 *	Algorithm:  Union_set
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.3.22
 * 	Language:  	C++11
 *
 * 	Description:  Union_set
 * 					1.Support union of set, query of whether in the same set.
 * 					2.Use path compression and weighted tree
 *      			3.Each set, its root is a negative number, and the absolute 
 * 				      value of it is the size of the set.
 *
 *  update:
 *  	4.5  comments
 */

#include <iostream>
#include <vector>

class UnionSet
{
public:
	/**
	 * Constructor.
	 * The initialize value of each element is -1,
	 * which means they are the only element in 
	 * their set.
	 */
	UnionSet(int size)
		:vec(size+1, -1)
	{}

	/**
	 * Union x set and y set
	 * @param x 
	 * @param y 
	 */
	void union_ele(int x,int y)
	{
		int xf = findFather(x);
		int yf = findFather(y);
		if( xf == yf )
			return ;
		//xf size is smaller, swap them, then xf is bigger
		if(vec[xf] > vec[yf])
			std::swap(xf,yf);
		//then union yf to xf
		vec[xf] = vec[xf] + vec[yf];
		vec[yf] = xf;
	}

	/**
	 * Judge whether x and y in the same set.
	 * @param  x 
	 * @param  y 
	 * @return   same set return true, o.w return false
	 */
	bool isInSameSet(int x,int y)
	{
		return findFather(x) == findFather(y);
	}

private:

	int findFather(int x)
	{
		if(vec[x] < 0)
			return x;
		else 
			/* path compression */
			return vec[x] = findFather(vec[x]);
	}

	std::vector<int> vec;
};


/**
 * simple test
 */
int main()
{
	UnionSet u(8);
	while(1)
	{
		int x, y;
		std::cin>>x;
		switch(x)
		{
			case 1:
				std::cin>>x>>y;
				u.union_ele(x,y);
				break;
			case 2:
				std::cin>>x>>y;
				std::cout<<u.isInSameSet(x,y);
				break;
		}
	}
}