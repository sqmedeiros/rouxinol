#include<bits/stdc++.h>
using namespace std;
//#define ll int;
using ll = long long;
vector<ll>graph[1000005];
ll dp[1000005];
ll visit[1000005]={0};
int inf=100000005;
ll n,m;
vector<ll>v;
vector<ll>vt;
ll p=0;
 
void gama(ll i,ll w)
{
   // cout<<i<<" ";
   visit[i]=1;
    vt.push_back(i);
    //cout<<w<<"g ";
    if(w>0)
    {
        for(ll j=0;j<graph[i].size();j++)
         {
             if(visit[graph[i][j]]==0)
             {
              if(dp[graph[i][j]]==w)
                {
                     gama(graph[i][j],w-1);
                }
             }
          }
    }
    
}
 
void alpha(ll i,ll c)
{
    v.push_back(i);
    dp[i]=1;
    while(v.size()>0)
    {
        ll x=v[0];
        auto it = v.begin();
          v.erase(it);
 
        for(ll j=0;j<graph[x].size();j++)
        {
            if((dp[x]+1)<dp[graph[x][j]])
            {
                dp[graph[x][j]]=dp[x]+1;
                v.push_back(graph[x][j]);
            }
        }
    }
}
int main()
{
    ll i;
    cin>>n>>m;
    ll g=m;
    while(g--)
    {
        ll u,v;
        cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        
    }
    for(i=1;i<=n;i++)
    {
         dp[i]=inf;
    }
    
 
          alpha(n,1);
          ll ans=dp[1];
          if(ans>100002)
          {
              cout<<"IMPOSSIBLE"<<endl;
          }
          else
          {
              cout<<ans<<endl;
             gama(1,ans-1);
             for(i=0;i<ans;i++)
             {
                 cout<<vt[i]<<" ";
             }
          }
 
    
    return 0;
}
