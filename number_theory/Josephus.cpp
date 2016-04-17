/**
 * 	Problem:	约瑟夫问题
 *	Algorithm:  递推
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.4.17
 * 	Language:  	C++11
 *
 *  Description:
 *  			1. f[n] = (f[n-1]+K)%n
 *  			2. if f[n - n/k] = s'
 *  				  f[n] = s' + n - n%k,  			if s' <= n%k
 *  				  	   = s' - n%k + (s'-n%k)/(k-1), if s' > n%k
 */


#include <iostream>
#include <vector>
#include <stdio.h>
#include <queue>
using namespace std;

long long Josephus(long long N, long long K) {
	if(K == 1)
		return N-1;
	if(N == 1)
		return 0;
	if(N < K) {
		long long ans = 0;
		for(long long i = 2; i <= N; ++i) {
			ans = (ans + K)%i;
		}
		return ans;
	}
	long long ans = Josephus(N-N/K, K);
	if( ans < N%K ) 
		return ans + N - N%K;
	else
		return ans - N%K + (ans-N%K)/(K-1);
}

int main() {
	long long N, K;
	int t;
	cin>>t;
	while(t--)
	{
		cin>>N>>K;
		cout<<Josephus(N, K)<<endl;
	}
}