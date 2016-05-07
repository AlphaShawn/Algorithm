/**
 *  Algorithm : Euler's totient function
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.5.7
 * 	Language:  	C++11
 *
 *  Description:
 *  			phi(x) = 小于x的正整数中与x互质的数的个数
 *
 * 				(1) p is prime, then phi(p) = p - 1
 * 				(2) n = p^k, p is prime, them phi(n) = (p-1)*p^(k-1)
 * 					因为n的约数全为p的倍数，p*a < n, a = n/p - 1 =  p^(k-1) - 1
 * 					所以phi(n) = n - 1 - a = (p-1)*p^(k-1)
 * 				(3) if p and q is relatively prime
 * 						then phi(p*q) = phi(q) * phi(p)
 *
 * 				corollary:
 * 				if p is prime then
 * 				(1) if n % p == 0
 * 					suppose n = p^k*m 
 * 					then phi(n*p) = phi(m*p^k*p) = phi(m) * phi(p*(k+1)) = phi(m) * (p-1)*p^k
 * 								  = phi(m) * (p-1)*p(k-1)*p
 * 								  = phi(m)*p;
 * 				(2) if n % p != 0
 * 					then phi(n*p) = phi(n)*phi(p) = phi(n)*(p-1)
 */


#include <iostream>
#include <vector>
using namespace std;
#define MAXN  5500001
#define LL long long

LL phi[MAXN];
bool isPrime[MAXN];

void Eular(LL n) { 
	vector<LL> prime_list;
	for(LL i = 2; i <= n; ++i) {
		if( isPrime[i] ) {
			phi[i] = i - 1;
			prime_list.push_back(i);
		}
		for(LL j = 0; j != prime_list.size(); ++j) {
			if( i*prime_list[j] > n || i*prime_list[j] < 0)
				break;
			isPrime[i*prime_list[j]] = false;
			if(i % prime_list[j] == 0) {
				phi[i*prime_list[j]] = phi[i] * prime_list[j];
				break;
			} else {
				phi[i*prime_list[j]] = phi[i] * ( prime_list[j] - 1 );
			}
		}
	}
}

/**
 * code for hihocoder [http://hihocoder.com/contest/hiho96/problem/1]
 */
int main() {
	LL L, R;
	while(cin>>L>>R) {
		for(LL i = 0; i <=R ; ++i) 
			isPrime[i] = true;
		Eular(R);
		LL n = L, num = phi[L];
		for(LL i = L + 1; i <= R; ++i) {
			if(phi[i] < num) {
				n = i;
				num = phi[i];
			}
		}
		printf("%d\n", n);
	}
}