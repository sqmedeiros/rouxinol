#include <bits/stdc++.h>
using namespace std;
 
struct DJK
{
	int node;
	long long weight;
	bool operator < (const DJK & o) const
	{
		return weight > o.weight;
	}
};
 
bool visit[100005];
long long dis[100005];
vector<DJK> g[100005];
priority_queue<DJK> djk;
 
int main()
{
	int n, m;
	scanf(" %d %d",&n,&m);
	while(m--)
	{
		int u, v;
		long long w;
		scanf(" %d %d %lld",&u,&v,&w);
		g[u].push_back({v, w});
	}
	for(int i=2 ; i<=n ; i++)
		dis[i] = 1e15;
	djk.push({1, 0});
	while(!djk.empty())
	{
		int nown = djk.top().node;
		long long noww = djk.top().weight;
		djk.pop();
		if(visit[nown]) continue;
		visit[nown] = 1;
		for(auto x : g[nown])
			if(dis[x.node] > dis[nown] + x.weight)
			{
				dis[x.node] = dis[nown] + x.weight;
				djk.push({x.node, dis[x.node]});
			}
	}
	for(int i=1 ; i<=n ; i++)
		printf("%lld ",dis[i]);
	return 0;
}
