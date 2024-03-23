#include<bits/stdc++.h>
 
using namespace std;
 
using ll=long long int;
const int nmax= 510;
 
ll dst[nmax][nmax];
 
void floyd(ll node)
{
    for(int k=1 ; k<=node ; k++)
    {
        for(int i=1 ; i<=node ; i++)
        {
            for(int j=1 ; j<=node ; j++)
            {
                if(dst[i][k]+dst[k][j]<dst[i][j])
                {
                    dst[i][j]=dst[i][k]+dst[k][j];
                }
            }
        }
    }
}
 
int main()
{
     ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
    for(int i=0 ; i<=nmax ; i++)
    {
        for(int j=0 ; j<=nmax ; j++)
        {
            if(i==j)
            {
                dst[i][j]=0;
            }
            else
            {
                dst[i][j]=1e18+10;
            }
        }
    }
 
    ll n,m,q;
 
    cin>>n>>m>>q;
 
    for(int i=0 ; i<m ; i++)
    {
        ll u,v,w;
 
        cin>>u>>v>>w;
 
        dst[u][v]= min(w,dst[u][v]);
        dst[v][u]=min(w,dst[v][u]);
    }
 
    floyd(n);
 
 
    for(ll i=0 ; i<q ; i++ )
    {
        ll u,v;
        cin>>u>>v;
 
        if(dst[u][v]==1e18+10)
        {
            cout<<-1<<"\n";
        }
        else
        {
            cout<<dst[u][v]<<"\n";
        }
    }
 
    return 0;
}
