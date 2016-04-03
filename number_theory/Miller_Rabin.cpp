/**
 *	Algorithm:  Miller_Rabin
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.4.2
 * 	Language:  	C++11
 *
 * 	Description: 
 * 				  random algorithm to decide whether a number is prime.
 * 				  Fermat theory:
 * 				  		a^(n-1) = 1 (mod n) if n is prime number
 * 				  二次探测原理:
 * 			   			if n is prime and a^2 = 1 (mod n) then a = 1 or a = n-1
 *
 * 				  if n < 2^64, it is it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, and 41.
 * 				  wiki:https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
 */


unsigned long long mod_mul(unsigned long long a, unsigned long long b, unsigned long long m)
{
	unsigned long long s = 0;
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

unsigned long long quick_power_mod(unsigned long long x, unsigned long long n, unsigned long long m)
{	
	/* only support positive power*/
	if(n < 0)
		return 0;
	unsigned long long ans = 1;
	while(n > 0)
	{
		if((n&1) == 1)
			ans = mod_mul(ans, x, m);
		x = mod_mul(x, x, m);
		n >>= 1;
	}
	return ans;
}

bool Miller_Rabin(unsigned long long n)
{
	if( n<2 )
		return false;
	if( n == 2 )
		return true;
	if( (n & 1) == 0 )
		return false;
	unsigned long long q = n-1;
	int j = 0;
	while((q&1) == 0)
	{
		q = q>>1;
		j++;
	}

	int S = 20;
	for(int i = 0; i < S; i++)
	{
		unsigned long long a = rand()%(n-2)+2;
		
		unsigned long long  tmp = quick_power_mod(a, q, n);
		for(int i = 0; i < j; ++i)
		{
			unsigned long long y = mod_mul(tmp, tmp, n);
			if( y == 1 && tmp != 1 && tmp != n-1)	//
				return false;
			tmp = y;
		}
		if( tmp != 1) //Fermat
			return false;
	}	
	return true;
}

int main()
{

}