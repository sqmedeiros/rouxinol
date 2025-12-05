/*
              __________
             |\         \
             | \         \
             |  \_________\
             |  |         |
   __________|  | (O)     |
  /          \  |         |
  |           \ |         |
   \___________\|_________|
    \                     |
     \                    |
      \                   |
       |                  |
       |__________________|
*/
#include <bits/stdc++.h>
#define int long long
#define MOD 1000000007  
#define pii pair<int,int>
#define float long double
#define NMAX 200005
using namespace std;
int n,a[NMAX],child[NMAX];
vector<int>adj[NMAX];
void dfs(int u,int par) {
    for (int v:adj[u])
        if (v != par) {
            dfs(v,u);
            child[u]+=child[v]+1;
        }
}
main() {
    cin>>n;
    for (int i=2;i<=n;i++) {
        int par;
        cin>>par;
        adj[par].push_back(i);
    }
    dfs(1,0);
    for (int i=1;i<=n;i++)
        cout<<child[i]<<" ";
}
