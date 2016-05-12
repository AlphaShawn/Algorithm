/**
 *	Algorithm: 模线性同余方程组   hihocoder(http://hihocoder.com/contest/hiho97/problem/1)
 *  Author: Alpha Xiao
 *  Date:   5.12
 * 
 *  Description:
 *  		input: give a group of equation:   a % mi = ri   i = 1,2...n
 *  		output: minimum a s.t the equations
 *
 * 			when n = 2,
 * 				a % m1 = r1  ,  a % m2 = r2
 * 			  so there exists  k1, k2 
 * 			  	s.t m1 * k1 + r1 = a = m2 * k2 + r2
 * 			  so we have m1 * k1 - m2 * k2 = r2 - r1
 * 			apply the extended_Euclidean algorithm we can get
 * 			  			k1 and k2 s.t the equation
 * 			At the meantime, we have group of a = k1 * m1 + r1 + lcm(m1,m2) * k
 * 				which is a % lcm(m1,m2) = k1*m1;
 * 			 	It means we combine two equation into one equation, so if we
 * 			 	have n equations, we only need to keep combining the equations
 * 			 	then we will have the final answer
 */


#include <iostream>
using namespace std;
#define LL long long
int N;

/**
 * extended Euclid's Algorithm  Ax+By = gcd(A, B)
 * @param  a 
 * @param  b 
 * @param  x 
 * @param  y 
 * @return   gcd(a, b)
 */
LL e_gcd(LL a, LL b, LL &x, LL &y) {
	if(b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	LL m = e_gcd(b, a%b, x, y);
	LL t = x;
	x = y;
	y = t - (a/b)*y;
	return m;
}


LL gcd(LL a, LL b) {
	if(a%b == 0)
		return b;
	return gcd(b, a%b);
}

int main() {
	while(cin>>N) {
		LL m1, r1, m2, r2;
		scanf("%lld %lld", &m1, &r1);
		N--;
		while(N--) {
			scanf("%lld %lld", &m2, &r2);
			
			LL A, B, C, x, y;
			A = m1;
			B = m2;
			C = r2 - r1;
			LL r = gcd(m1, m2);
			
			if(C % r != 0) {
				printf("-1\n");
				break;
			}
			C = C / r;
			A = A / r;
			B = B / r;

			e_gcd(A, B, x, y);
			
			x = x*C % (B);		// get x
			LL ans = m1*x + r1;	// get a
			m1 = m1/r*m2;		// get lcm(m1, m2)
			r1 = ans%m1;		// get minimum a
		}
		if(r1 < 0)
			r1 += m1;
		printf("%lld\n", r1);
	}
}