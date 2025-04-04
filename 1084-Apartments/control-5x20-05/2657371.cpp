#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
 
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
 
const int MOD = 1000000007;
 
deque<int> posi;
vi todo, b;
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n,m,k; cin >> n >> m >> k;
    F0R(i,n) {
        int x; cin >> x;
        todo.pb(x);
    }
    sort(todo.rbegin(),todo.rend());
    b.resize(m);
    F0R(i,m) cin >> b[i];
    sort(all(b));
    
    int ans = 0;
    for (int i: b) {
        while (sz(todo) && todo.back() <= i+k) {
            posi.pb(todo.back());
            todo.pop_back();
        }
        while (sz(posi) && posi.front()+k < i) posi.pop_front();
        if (sz(posi)) {
            ans ++;
            posi.pop_front();
        }
    }
    cout << ans;
}
