#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("bmi,bmi2,lzcnt,popcnt")
 
#include <bits/stdc++.h>
 
using namespace std;
 
const int MOD = 1e9 + 7;
using ll = long long;
using dbl = long double;
//#define int ll
 
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vii = vector<pii>;
using vvii = vector<vii>;
using vll = vector<ll>;
 
#define ff first
#define ss second
#define pb push_back
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define tc int t; cin>>t; while(t--)
#define fightFight cin.tie(0) -> sync_with_stdio(0)
 
void solve() {
    int n;
    cin >> n;
    set<int> st;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        st.insert(x);
    }
    cout << sz(st) << "\n";
}
 
signed main() {
    fightFight;
    solve();
}
