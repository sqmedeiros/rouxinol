#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#ifdef TEST
#define getchar_unlocked _getchar_nolock
#endif
#define int long long
#define ins insert
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define pf push_front
#define pp pop
#define ppb pop_back
#define ppf pop_front
#define eb emplace_back
#define g0(a) get<0>(a)
#define g1(a) get<1>(a)
#define g2(a) get<2>(a)
#define g3(a) get<3>(a)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
typedef double db;
typedef long long ll;
typedef pair<int, int> ii;
typedef tuple<int, int, int> iii;
typedef tree<pair<int, int>, null_type, less<pair<int, int> >, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
 
int N, mn, md = -1;
vector<int> adj[200005];
 
void dfs(int n, int d, int e = -1) {
	if (d > md) {
		md = d;
		mn = n;
	}
	for (auto u : adj[n])
		if (u != e)
			dfs(u, d + 1, n);
}
 
main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	for (int i = 1, u, v; i < N; i++) {
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	dfs(1, 0);
	md = -1;
	dfs(mn, 0);
	cout << md << '\n';
}
