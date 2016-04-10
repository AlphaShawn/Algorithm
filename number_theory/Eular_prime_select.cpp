/**
 *	Algorithm:  Eular 素数筛选法
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.4.10
 * 	Language:  	C++11
 *
 * 	Description: 
 * 				  time complexity O(n)
 */


#include <iostream>
#include <vector>
using namespace std;

#define MAXN 1000001
bool isPrime[MAXN];

/**
 * [Eular description]
 * @param  n the number range [2...n]
 * @return   number of prime in range [2...n]
 */
int Eular(int n) { 
	vector<int> prime_list;
	int ans = 0;
	for(int i = 2; i <= n; ++i) {
		if( isPrime[i] ) {
			ans ++;
			prime_list.push_back(i);
		}
		for(int j = 0; j != prime_list.size(); ++j) {
			if( i*prime_list[j] > n )
				break;
			isPrime[i*prime_list[j]] = false;
			if(i % prime_list[j] == 0)
				break;
		}
	}
	return ans;
}


// int work(int n) {
// 	if(n == 2)
// 		return 1;
// 	int ans = 1; // include 2
// 	int maxi = (n-1)/2 - 1;
// 	for(int i = 0; i <= maxi; ++i) {
// 		int now = (i+1)*2+1;
// 		if(isPrime[i]) {
// 			ans++;
// 			for(int j = 3; now*j <= n; j+=2)
// 				isPrime[i*j+3*(j-1)/2] = false;
// 		} 
// 	}
// 	return ans;
// }


void init() {
	for(int i=0;i<MAXN;i++)
		isPrime[i] = true;
}

int main()
{
	int N;
	init();
	while(cin>>N) {
		cout<<work(N)<<endl;
	}
	return 0;
}