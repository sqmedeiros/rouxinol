#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
 
vector<ll> adj[300005];
 
ll mxdist, idx;
 
ll dfs(ll node, ll par, ll dist){
	if(adj[node].size() == 1 && adj[node][0] == par){
		if(dist > mxdist){
			idx = node;
			mxdist = dist;	
		}
	}
	for(auto i: adj[node]){
		if(i==par) continue;
		dfs(i, node, dist+1);	
	}
}
 
 
int main(){
	std::ios_base::sync_with_stdio(0);
	ll n;
	cin >> n;
	for(ll i=0;i<n-1;i++){
		ll u,v;
		cin >> u >> v;
		adj[u-1].push_back(v-1);
		adj[v-1].push_back(u-1);
	}
	
	dfs(0, -1, 0);
	mxdist = 0;
	dfs(idx, -1, 0);
	cout << mxdist << "\n";
}
