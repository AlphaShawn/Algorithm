/**
 *	Algorithm:  Euclid's Algorithm / 
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.4.10
 * 	Language:  	C++11
 *
 * 	Description: 
 * 				compute the greatest common divisor of two numbers.
 */
#include <iostream>


/**
 * @param  a 
 * @param  b 
 * @return   greatest common divisor of a and b.
 */
int gcd(int a, int b) {
	if(b == 0) {
		return a;
	}
	return gcd(b, a%b);
}

//test
int main(){
	int a, b;
	while(std::cin>>a>>b) {
		std::cout<<gcd(a, b)<<'\n';
	}
	return 0;	
}