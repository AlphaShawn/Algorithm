/**
 *	Algorithm:  quick_power
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.3.23
 * 	Language:  	C++11
 *
 * 	Description: 
 * 				  A quick method to compute x^n
 */


#include <iostream>
#include <vector>

 class Power
 {
 public:

 	static int power(int x, int n, int m = 0)
 	{
 		if(m == 0)
 			return quick_power(x, n);
 		return quick_power_mod(x, n, m);
 	}

 	/**
 	 * ex.
 	 * 		2^9 = 2^(1001) = 2^(1000) * 2^(1)
 	 */
 	static int quick_power(int x, int n)
 	{	
 		/* only support positive power*/
 		if(n < 0)
 			return 0;
 		int ans = 1;
 		while(n > 0)
 		{
 			if((n&1) == 1)
 				ans = ans * x;
 			x = x*x;
 			n >>= 1;
 		}
 		return ans;
 	}


 	static int quick_power_mod(int x, int n, int m)
 	{	
 		/* only support positive power*/
 		if(n < 0)
 			return 0;
 		int ans = 1;
 		while(n > 0)
 		{
 			if((n&1) == 1)
 				ans = (ans * x) % m;
 			x = (x*x)%m;
 			n >>= 1;
 		}
 		return ans;
 	}
 };


/* test */
 int main()
 {
 	std::cout<<Power::power(2,3)<<'\n';
 	std::cout<<Power::power(2,10)<<'\n';
 	std::cout<<Power::power(2,20)<<'\n';
 }