#include <bits/stdc++.h>
using namespace std;
 
#define ll long long int
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define pp pop_back
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define cont(it,x) for (auto it=x.begin(); it!=x.end(); it++){cout << *it << ' ';} cout << '\n';
#define contp(it,x) for (auto it=x.begin(); it!=x.end(); it++){cout << it->first << ' ' << it->second << '\n';}
#define printvvec(x) for(int _=0;_<x.size();_++){for(int __=0;__<x[_].size(); __++){cout<<x[_][__]<<' ';}cout<<'\n';}
#define printp(x) cout<<x.first<<' '<< x.second<<'\n';
#define fo(i,start,end) int i=start;i<end;i++
#define foi(i,start,end) int i=start;i<=end;i++
#define fot(it, x) auto it=x.begin();it!=x.end();it++
#define printadj(n,x) for (int i=0; i<n; i++) {cout<<i<<": ";for(int j=0;j<x[i].size();j++){cout<<adj[i][j]<<' ';}cout<<'\n';}
#define int long long int
 
// min-heap
class comp{
public:
    bool operator() (int& a, int& b) {
        return a > b;
    }
};
 
// sort pair
bool comp1(pair<int,int> a, pair<int,int> b) {
    return(a.second < b.second);
}
 
// string to int
int string_to_int(string s) {
    stringstream a(s);
    int x;
    a >> x;
    return x;
}
 
// gcd
int gcd(int a, int b) {
    if (b == 0) return a;
    int temp = gcd(b, a%b);
    return temp;
}
 
int n, e;
vector<vector<pair<int,int>>> adj;
vector<int> dist;
vector<int> visit;
 
void dijkstra(int s) {
    dist[s] = 0;
    priority_queue<pair<int,int>> pq;
    pq.push({0,s});
    while (!pq.empty()) {
        int top = pq.top().second;
        pq.pop();
        if (!visit[top]) {
            visit[top] = true;
            for (auto i: adj[top]) {
                int b = i.first;
                int w = i.second;
                dist[b] = min(dist[b], dist[top]+w);
                pq.push({-dist[b], b});
            }
        }
    }
}
 
void best() {
    int __ = 1;
    // cin >> __;
    while(__--) {
        cin >> n >> e;
        adj.resize(n+1);
        dist.resize(n+1, INT64_MAX);
        visit.resize(n+1, false);
        for (int i=0; i<e; i++) {
            int x, y, z;
            cin >> x >> y >> z;
            adj[x].pb({y,z});
        }
        dijkstra(1);
        for (int i=1; i<dist.size(); i++) cout << dist[i] << " ";
    }
}
 
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    #ifndef ONLINE_JUDGE
        //freopen("in", "r", stdin);
        //freopen("out", "w", stdout);
    #endif
    
    best();
    
    return 0;
}
