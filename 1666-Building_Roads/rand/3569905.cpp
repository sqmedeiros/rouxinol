#include <iostream>
#include <map>
#include <tuple>
#include <vector>
#include <queue>
#define ii pair<int,int>
using namespace std;
 
int bfs(int u);
 
vector<pair<vector<int>,int>> g;
queue<int> q;
int main() {
    int n,m,u,v;cin>>n>>m;
    g.resize(n);
    for(int i=0;i<m;i++) {
        cin >> u >> v;
        u--;v--;
        g[u].first.push_back(v);
        g[v].first.push_back(u);
    }
    vector<int> path;
    for(int j=0; j<n;j++){
        if(g[j].second==0){
            path.push_back(j);
            bfs(j);
        }
    }
    cout<<path.size()-1<<endl;
    for(int l=0;l<path.size()-1;l++){
        cout<<path[l]+1<<" "<<path[l+1]+1<<endl;
    }
    return 0;
}
 
int bfs(int u){
    g[u].second=2;
    q.push(u);
    while(q.empty()==false){
        int node = q.front();
        q.pop();
        for(int adjN : g[node].first){
            if(g[adjN].second==0){
                q.push(adjN);
                g[adjN].second=1;
            }
 
        }
    }
 
}
 
