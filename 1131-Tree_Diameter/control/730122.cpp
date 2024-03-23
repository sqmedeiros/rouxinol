#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
ll pos,m=-1;
vector<ll> v[200005];
ll dfs(ll cur,ll par,ll h)
{
	if(m<h)
	{
		m=h;
		pos=cur;
	}
	for(auto x:v[cur]) if(x!=par) dfs(x,cur,h+1);
}
int main()
{
	ll n,i,x,y;
	cin>>n;
	for(i=0;i<n-1;i++)
	{
		cin>>x>>y;
		v[x].pb(y);
		v[y].pb(x);
	}
	dfs(1,-1,0);
	m=-1;
	dfs(pos,-1,0);
	cout<<m;
}
