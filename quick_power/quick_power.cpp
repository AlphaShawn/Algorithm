/**
 *	Algorithm:  quick_power
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.3.23
 * 	Language:  	C++11
 *
 * 	Description: 
 * 				  A quick method to compute x^n
 *
 *  Update Date: 
 *  		2016.4.2  add mul_mod. avoid big number overflow.
 */


#include <iostream>
#include <vector>

 class Power
 {
 public:

 	static int mul_mod(int a, int b, int m)
 	{
 		int s = 0;
		while(b)
		{
			if(b&1)
			{
				s = s + a;
				if(s > m)
					s -= m;
			}
			a <<= 1;
			if( a > m )
				a -= m;
			b >>= 1; 
		}
		return s;
 	}

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
 				ans = mul_mod(ans, x, m);
 			x = mul_mod(x, x, m);
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