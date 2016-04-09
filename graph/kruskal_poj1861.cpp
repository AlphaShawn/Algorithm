/**
 *  Problem:  Poj - 1861 - Kruskal
 *  
 *  Author:     Alpha Xiao
 *  Date  :     2016.4.8
 *  Language:   C++11
 *
 *  Description:  
 *                
 *  http://poj.org/problem?id=1861.
 */


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define INTMAX 0x7fffffff

struct edge
{
    edge(int a, int b, int t):from(a),to(b),w(t){}
    int from, to;
    int w;
    static bool compare(const edge &lhs, const edge &rhs) {
        return lhs.w > rhs.w ? 0 : 1;
    }
};

class UnionSet
{
public:
    UnionSet(int size)
        :vec(size+1, -1)
    {}

    void union_ele(int x,int y)
    {
        int xf = findFather(x);
        int yf = findFather(y);
        if( xf == yf )
            return ;
        if(vec[xf] > vec[yf])
            swap(xf,yf);
        vec[xf] = vec[xf] + vec[yf];
        vec[yf] = xf;
    }

    bool isInSameSet(int x,int y)
    {
        return findFather(x) == findFather(y);
    }

private:

    int findFather(int x)
    {
        if(vec[x] < 0)
            return x;
        else 
            return vec[x] = findFather(vec[x]);
    }

    vector<int> vec;
};


vector<edge> Kruskal(vector<edge> &G, int v) {

    sort(G.begin(), G.end(), edge::compare);
    UnionSet U(v);
    vector<edge> ans;
    int k = -1;
    while(ans.size() != v-1) {
        ++k;
        if( U.isInSameSet(G[k].from, G[k].to) )
            continue;
        ans.push_back(G[k]);
        U.union_ele(G[k].from, G[k].to);
    }
    return ans;
}

int main()
{
    int N, M;
    while(cin>>N>>M) {
        vector<edge> vec;
        int a, b, t;
        for(int i = 0; i < M; ++i) {
            cin>>a>>b>>t;
            vec.push_back(edge(a,b,t));
        }
        vector<edge> ans = Kruskal(vec, N);
        cout<<ans[ans.size()-1].w<<endl;
        cout<<N-1<<endl;
        for(int i = 0; i < ans.size(); ++i) {
            cout<<ans[i].from<<' '<<ans[i].to<<endl;
        }
    }
}