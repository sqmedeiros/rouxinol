#include<bits/stdc++.h>
using namespace std;
#define ll long long int
 
vector<vector<ll>>adj;
 
pair<ll,ll> maxBfs(ll s, ll n, vector<ll>&val)
{
	pair<ll,ll>result;
	val.clear();
	val.resize(n+1,0);
	vector<ll>visited(n+1,0);
	queue<ll>q;
	q.push(s);
	visited[s] = 1;
	while(!q.empty())
	{
		ll node = q.front();
		q.pop();
		
	
		for(auto i: adj[node])
		{
			if(visited[i] == 0)
			{
				//count--;
				visited[i] = 1;
				q.push(i);
				val[i] = val[node] + 1;
				
			}
		}
		
		
	}
 
	
	result.first = (max_element(val.begin(),val.end()) - val.begin());
	result.second = *max_element(val.begin(),val.end());
	return result;
}
 
 
ll solve()
{
	ll n;
	cin>>n;
	
	adj.clear();
	
	adj.resize(n+4);
	for(int i=0; i<n-1; i++)
	{
		ll u,v;
		cin>>u>>v;
		u--,v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
 
	vector<ll>ans(n,0);
	
	vector<ll>diameters;
	ll temp = maxBfs(0, n,diameters).first;
	auto far = maxBfs(temp,n,diameters);
	ll dist = far.second;
	vector<ll>store = diameters;
	maxBfs(far.first,n,diameters);
	
 
	
	
	for(int i=0; i<n; i++)
	{
		cout<<max(diameters[i],store[i])<<" ";
	/*	if(diameters[i] == dist || store[i] == dist)
			cout<<dist<<" ";
		else
			cout<<dist-1<<" ";
	*/		
	}	
	cout<<endl;
}
 
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	
    ll ignore = 1;
    //cin>>ignore;
    while(ignore--)
    {
    	solve();
	}
}
