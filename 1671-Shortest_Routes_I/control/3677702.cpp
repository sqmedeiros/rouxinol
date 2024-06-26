/**                  _ _              _____ ___
 *  _ __   _____   _(_) | ____      _|___ // _ \
 * | '_ \ / _ \ \ / / | |/ /\ \ /\ / / |_ \ (_) |
 * | | | |  __/\ V /| |   <  \ V  V / ___) \__, |
 * |_| |_|\___| \_/ |_|_|\_\  \_/\_/ |____/  /_/
 **/
#include <bits/extc++.h>
#ifndef nevikw39
#define nevikw39 cin.tie(nullptr), ios::sync_with_stdio(false)
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("abm,bmi,bmi2,mmx,sse,sse2,sse3,ssse3,sse4,popcnt,fma,tune=native")
#pragma comment(linker, "/stack:200000000")
struct
{
    template <typename T>
    auto &operator<<(const T &x) { return *this; }
} __cerr;
#define cerr __cerr
#else
#pragma message("hello, nevikw39")
#endif
#pragma message("GL; HF!")
#define ALL(X) begin(X), end(X)
#define ST first
#define ND second
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
template <typename T, typename Tag = rc_binomial_heap_tag, typename Cmp = greater<T>>
using _heap = __gnu_pbds::priority_queue<T, Cmp, Tag>;
template <typename K, typename M = null_type>
using _hash = gp_hash_table<K, M>;
template <typename K, typename M = null_type, typename Cmp = less<K>, typename T = rb_tree_tag>
using _tree = tree<K, M, Cmp, T, tree_order_statistics_node_update>;
 
int main()
{
    nevikw39;
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        g[a - 1].emplace_back(b - 1, c);
    }
    vector<int64_t> d(n, INT64_MAX >> 1);
    _heap<pair<int64_t, int>> pq;
    vector<_heap<pair<int64_t, int>>::point_iterator> itrs(n);
    itrs[0] = pq.push({d[0] = 0, 0});
    while (pq.size())
    {
        int t = pq.top().ND;
        pq.pop();
        itrs[t] = nullptr;
        for (const auto &[i, w] : g[t])
            if (d[i] > d[t] + w)
            {
                if (itrs[i] != nullptr)
                    pq.modify(itrs[i], {d[i] = d[t] + w, i});
                else
                    itrs[i] = pq.push({d[i] = d[t] + w, i});
            }
    }
    for (const auto &i : d)
        cout << i << ' ';
    cout << '\n';
    return 0;
}
