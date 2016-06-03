/**
 *  Algorithm : Euler's totient function
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.6.3
 * 	Language:  	C++11
 *
 *  Description:
 *  	Cantor Expansion and Reverse CantorExpansion
 *
 *		n-length permutation num[1...n] the ordinal of the sequence is:
 *			X = a[1]*(n-1)! + a[2]*(n-2)! + ... + a[n]*0!
 *		 	a[i] = the number of elements s.t num[k] < num[i], i < k <=n
 *		
 * 
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/**
 * [Cantor_expansion description]
 * @param  s permutation of number
 * @return   the ordinal of this permutation
 */
int CantorExpansion(string s) {
	int n = s.size();
	int ordinal = 0;
	int k = 1;
	for(int i = n - 2; i >= 0 ; --i) {
		int count = 0;
		for(int j = i + 1; j < n; ++j)
			if(s[i] > s[j])
				count ++;
		ordinal += count * k;
		k = k * (n-i);
	}
	return ordinal;
}

string ReverseCantorExpansion(int ordinal, int n) {
	int k = 1;
	for(int i = 1; i < n; ++i)
		k *= i;
	vector<bool> used(n, false);
	string ans;
	for(int i = 0; i < n; ++i) {
		int t = ordinal / k;
		ordinal = ordinal % k;
		int j = 0;
		for(; j < n && t >= 0; ++j) {
			if(used[j] == false)
				--t;
		}
		ans += (j + '0');
		used[j-1] = true;
		if(n-i-1 > 0)
			k = k/(n-i-1);
	}
	return ans;
}

int main() {
	string s = "123";
	cout<<CantorExpansion(s)<<endl;
	s = "213";
	cout<<CantorExpansion(s)<<endl;
	s = "231";
	cout<<CantorExpansion(s)<<endl;

	cout<<ReverseCantorExpansion(0,3)<<endl;
	cout<<ReverseCantorExpansion(2,3)<<endl;
	cout<<ReverseCantorExpansion(3,3)<<endl;
	return 0;
}