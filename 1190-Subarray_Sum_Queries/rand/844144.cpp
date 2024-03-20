#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
#define int long long
#define fi first
#define se second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define yn(x) ((x) ? "YES" : "NO")
 
typedef pair <int, int> ii;
typedef pair <int, ii> iii;
 
template <class T> using ordered_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T> using ordered_multiset = tree <T, null_type, less_equal <T>, rb_tree_tag, tree_order_statistics_node_update>;
 
const int siz = 2e5 + 10;
const int SIZ = 1e6 + 10;
const int mod = 1e9 + 7;
const int maxx = 2e9;
const int MAXX = 1e18;
const string file = "5";
 
struct data {
    int curSum, preSum, sufSum, maxSum;
 
    data(int _curSum, int _preSum, int _sufSum, int _maxSum) {
        curSum = _curSum;
        preSum = _preSum;
        sufSum = _sufSum;
        maxSum = _maxSum;
    }
 
    data(int value) {
        curSum = preSum = sufSum = maxSum = value;
    }
 
    data() {
    }
 
    data operator + (const data &d) {
        data res;
        res.curSum = curSum + d.curSum;
        res.preSum = max(preSum, curSum + d.preSum);
        res.sufSum = max(d.sufSum, d.curSum + sufSum);
        res.maxSum = max(max(maxSum, d.maxSum), sufSum + d.preSum);
        return res;
    }
};
 
int a[siz];
data seg[4 * siz];
 
void buildSeg(int node, int start, int finish) {
    if (start == finish) {
        seg[node] = data(a[start]);
        return;
    }
 
    int mid = (start + finish) / 2;
    buildSeg(2 * node, start, mid);
    buildSeg(2 * node + 1, mid + 1, finish);
 
    seg[node] = seg[2 * node] + seg[2 * node + 1];
}
 
void updatePos(int node, int start, int finish, int index, int value) {
    if (start == finish) {
        a[start] = value;
        seg[node] = data(value);
        return;
    }
 
    int mid = (start + finish) / 2;
    if (index <= mid) {
        updatePos(2 * node, start, mid, index, value);
    }
    else {
        updatePos(2 * node + 1, mid + 1, finish, index, value);
    }
 
    seg[node] = seg[2 * node] + seg[2 * node + 1];
}
 
data getSum(int node, int start, int finish, int left, int right) {
    if (right < start || finish < left) {
        return data(0LL, -MAXX, -MAXX, -MAXX);
    }
 
    if (left <= start && finish <= right) {
        return seg[node];
    }
 
    int mid = (start + finish) / 2;
    data s1 = getSum(2 * node, start, mid, left, right);
    data s2 = getSum(2 * node + 1, mid + 1, finish, left, right);
 
    return s1 + s2;
}
 
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
 
//    freopen ((file + ".INP").c_str(), "r", stdin);
//    freopen ((file + ".OUT").c_str(), "w", stdout);
 
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
 
    buildSeg(1, 1, n);
 
    while (q--) {
        int k, x;
        cin >> k >> x;
 
        updatePos(1, 1, n, k, x);
        cout << max(getSum(1, 1, n, 1, n).maxSum, 0LL) << "\n";
    }
 
//    cerr << "Time: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
 
    return 0;
}
