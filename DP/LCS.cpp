/**
 *	Algorithm:  Longest Common Subsequence
 *	
 * 	Author: 	Alpha Xiao
 * 	Date  :		2016.3.28
 * 	Language:  	C++11
 *
 * 	Description:  
 * 				  f[i][j] = f[i-1][j-1] + 1 			if S1[i] == S2[j]
 * 				  			max(f[i-1][j], f[i][j-1])	if S1[i] != S2[j]
 * 				  space compression.
 * 				  Space: O(S2.size())
 * 				  Time : O(mn)
 * 	update:
 * 		add reconstruct version. use O(mn) space
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define MAX(x,y) ((x)>(y)?(x):(y));

/**
 * Calculate the LCS of s1,s2
 * @return the LCS of s1 and s2
 */
int LCS(string s1, string s2)
{
	vector<int> f[2];
	f[0].resize(s2.size()+1, 0);
	f[1].resize(s2.size()+1, 0);
	int m = 0;
	for(int i=1; i<=s1.size(); i++)
	{
		for(int j=1; j<=s2.size(); j++)
		{
			if( s1[i-1] == s2[j-1] )
				f[m][j] = f[m^1][j-1] + 1;
			else
				f[m][j] = MAX(f[m^1][j], f[m][j-1]);
		}
		m ^= 1;
	}
	return MAX(f[m][s2.size()],f[m^1][s2.size()]);
}

string LCS_Reconstruct(string s1, string s2) 
{
	std::vector< std::vector<int> > f(s1.size()+1, std::vector<int>(s2.size()+1, 0));
	/**
	 * remark the way of f[][] getting value
	 * 1: up
	 * 2: left
	 * 3: up-left
	 */
	std::vector< std::vector<short> > g(s1.size()+1, std::vector<short>(s2.size()+1, 0));
	for(int i = 1; i <= s1.size(); ++i) {
		for(int j = 1; j <= s2.size(); ++j)
		{
			if( s1[i-1] == s2[j-1] ) {
				f[i][j] = f[i-1][j-1] + 1;
				g[i][j] = 3;
			} else if(f[i-1][j] > f[i][j-1]){
				f[i][j] = f[i-1][j];
				g[i][j] = 1;
			} else {
				f[i][j] = f[i][j-1];
				g[i][j] = 2;
			}
		}
	}
	
	int x = s1.size(), y = s2.size();
	string ans;
	while(x > 0 && y > 0) {
		if(g[x][y] == 3) {
			ans = s1[x-1] + ans;
			--x;--y;
		} else if( g[x][y] == 2) 
			--y;
		else 
			--x;
	}
	return ans;
}

int main()
{
	//cout<<LCS("absdqwsa", "dasbdsaq")<<'\n';
	std::cout<<LCS_Reconstruct("yabsdqwsa", "ydasbdsaq")<<"\n";
}