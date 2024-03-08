#include <bits/stdc++.h>
#define fi first
#define se second
#define REP(i, a, b) for (int i = (a); i <= (b); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FORD(i, a, b) for(int i = (a); i > (b); --i)
#define REPD(i, a, b) for(int i = (a); i >=(b); --i)
#define TR(it, a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define endl '\n'
#define mp make_pair
#define pb push_back
#define ins insert
#define all(x) (x).begin(),(x).end()
#define SZ(x) ((int)(x).size())
#define unmap unordered_map
#define lb lower_bound //first pos >= val
#define ub upper_bound // first pos > val
#define debug(a) cout << a << endl
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef pair <ll, ll> pll;
typedef pair <int, int> pii;
typedef vector <int> vi;
typedef vector <ll> vll;
 
const ll maxN = 1e18;
const ll minN = -1e18;
const ll MOD = 1e9 + 7;
const ll MOD1 = 998244353;
const int bignumlen = 2200;
const int Blen = 8;
const ll base = 100000000;
const int baseHash = 31;
const ld PI = acos(-1);
 
//Remember limit for IT, etc...
const ll limit = 2e5 + 5;
const ll limit1 = 1e6 + 5;
const ll limit2 = 1e3 + 5;
//If TLE let's use int instead of ll because it's as slow as your WPM :)))
 
ll n, m;
vll g[limit];
ll dist[limit], trace[limit];
bool visit[limit];
vll ans;
 
void bfs(ll i) {
    queue <ll> q;
    visit[i] = true;
    trace[i] = 0;
    dist[i] = 1;
    q.push(i);
 
    while (!q.empty()) {
        ll u = q.front();
        q.pop();
 
        for (auto it : g[u]) {
            if (!visit[it]) {
                trace[it] = u;
                dist[it] = dist[u] + 1;
                q.push(it);
                visit[it] = true;
            }
        }
    }
 
}
 
void solveProblem() {
    bfs(1);
    if (visit[n]) {
        cout << dist[n] << endl;
        ll temp = n;
        ans.pb(n);
        while (temp != 0) {
            if (trace[temp] != 0) ans.pb(trace[temp]);
            temp = trace[temp];
        }
 
        reverse(all(ans));
        for (auto it : ans) cout << it << " ";
    }
 
    else cout << "IMPOSSIBLE";
}
 
void fastInput() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}
 
void readInput() {
    cin >> n >> m;
    REP(i, 1, m) {
        ll u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
}
 
int main() {
    fastInput();
    readInput();
    solveProblem();
}
 
