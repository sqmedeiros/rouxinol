#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
using ll = long long;
using ld = long double;
using str = string;
 
using pi = pair<int,int>;
using pl = pair<ll,ll>;
using pd = pair<ld,ld>;
 
using vl = vector<ll>;
using vd = vector<ld>;
using vi = vector<int>;
 
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<ld>;
 
#define endl "\n"
 
#define f first
#define s second
 
#define all(x)          begin(x), end(x)
#define pb		        push_back
#define sz              size()
#define deb(x)          cout << #x << " = " << x << endl;
#define deb2(x, y)      cout << #x << " = " << x << ", " << #y << " = " << y << endl;
#define logarr(arr,a,b)	for(int z = (a); z < (b); ++z) cout<<(arr[z])<<" "; cout<<"\n";
 
const int mod = 1e9 + 7;
const ll inf = 2e16;
 
template <typename T>
T addM(T a, T b, T mod) {
    T res = (a + 0LL + b)%mod;
    if(res < 0)
        res += mod;
    return res;
}
 
template <typename T>
T mulM(T a, T b, T mod) {
    T res = (a * 1LL * b)%mod;
    if(res < 0)
        res += mod;
    return res;
}
 
template <typename T>
T powM(T a, T b, T mod) {
    T res = 1;
    while(b) {
        if(b&1)
            res = mulM(res,a,mod);
        a = mulM(a,a,mod);
        b >>= 1;
    }
    return res;
}
 
const int N = 1e6, M = 1e6;
int U[M], V[M];
ll W[M];
vector<int> G[N];
 
void solve() {
    int n,m;
    cin>>n>>m;
 
    for(int i=0; i<m; i++) {
        cin>>U[i]>>V[i]>>W[i];
        G[U[i]].pb(i);
    }
 
    priority_queue <pair<ll,int>, vector<pair<ll,int>>, greater <pair<ll,int>>> q;
    ll d[n];
    for(int i=1; i<=n; i++)
        d[i] = inf;
    d[1] = 0;
    q.push({0,1});
    while(!q.empty()) {
        ll w = q.top().f;
        int u = q.top().s;
        q.pop();
 
        if(w > d[u]) 
            continue;
        for(auto e : G[u]) {
            ll cost = W[e];
            int v = U[e] ^ V[e] ^ u;
            if(w + cost < d[v]) {
                d[v] = w + cost;
                q.push({d[v],v});
            }
        }
    }
    for(int i=1; i<=n; i++)
        cout<<d[i]<<" ";
 
 
}
 
int main() {
	cin.tie(0)->sync_with_stdio(0);
    int t=1;
    //cin>>t;
    while(t--) {
        solve();
    }
	return 0;
}
 
