/**
 *	Algorithm:  extended Euclid's Algorithm / 
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.4.30
 * 	Language:  	C++11
 *
 * 	Description: 
 *     		According to extended Euclid's theor, there exists x, y s.t
 *     							Ax + By = gcd(A,B)
 *     		then
 *     			Let  Ax + By = gcd(A, B) = gcd(B, A%B) = Bx' + A%B*y'
 *     			Let A = k*B + r  so 
 *     					A%B = r = A - k*B
 *     					Ax + By = Ay' + (x'-ky')B
 *     			then 
 *     					x = y'
 *     					y = x' - ky'
 *     			when B = 0
 *     				then gcd(A, B) = A , A*1 + B*0 = A which means 
 *     						x = 1, y = 0
 *
 */
#include <iostream>

/**
 * extended Euclid's Algorithm  Ax+By = gcd(A, B)
 * @param  a 
 * @param  b 
 * @param  x 
 * @param  y 
 * @return   gcd(a, b)
 */
int e_gcd(int a, int b, int &x, int &y) {
	if(b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	int m = e_gcd(b, a%b, x, y);
	int t = x;
	x = y;
	y = t - (a/b)*y;
	return m;
}


//test
int main() {
	int a, b;
	while(std::cin>>a>>b) {
		int x = 0, y = 0;
		std::cout<<e_gcd(a, b, x, y)<<'\n';
		std::cout<<"x:"<<x<<"y:"<<y<<'\n';
	}
}