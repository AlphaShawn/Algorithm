/**
 *	Algorithm:  KMP
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.4.1
 * 	Language:  	C++11
 *
 * 	Description:  
 *  				KMP string matching algorithm.				 
 */
#include <iostream>
#include <string>
#include <vector>


/**
 * KMP
 * @param  s1 [source]
 * @param  s2 [target]
 * @return    start positon of matching substr in s1
 *            -1: s2 is not found in s1
 */
int KMP(std::string s1, std::string s2)
{
	// next[i] = max k such that s2[0..k] = s2[i-k...i]
	// next[i] = -1 mean no such k exists.a
	std::vector<int> next(s2.size(), -1);

	// calculate next array.
	for(int i = 1; i != s2.size(); ++i) {
		int t = next[i-1];
		while(true) {
			if(s2[t+1] == s2[i]) {
				next[i] = t+1;
				break;
			} else if( t != -1 ) {
				t = next[t];
			} else {
				break;
			}
		}
	}

	int t = 0;	 // pointer of s2
	for(int i = 0; i != s1.size(); ++i) {
		while(t > 0 && s1[i] != s2[t])
			t = next[t-1] + 1;
		if(s1[i] == s2[t])
			t++;
		if( t == s2.size())
			return i-s2.size()+1;
	}
	return -1;
}

int main()
{
	std::string s1 = "dbsaqeabccasdabcab";
	std::string s2 = "abcabs";
	int t = KMP(s1, s2);
	std::cout<<t<<'\n';
	if( t!= -1)
		std::cout<<s1.substr(t, s2.size())<<'\n';
}