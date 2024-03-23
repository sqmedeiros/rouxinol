#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("bmi,bmi2,popcnt,lzcnt,fma,tune=native")
 
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
 
using namespace std;
 
// from https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template<class Fun>
class y_combinator_result {
    Fun fun_;
public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
 
    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};
 
template<class Fun>
decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
 
    int n, m;
    cin >> n >> m;
 
    vector<vector<int> > G(n);
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        G[a-1].emplace_back(b-1);
        G[b-1].emplace_back(a-1);
    }
 
    vector<bool> visited(n, false);
 
    vector<int> ans;
    for (int i = 0; i < n; ++i)
    {
        if (visited[i])
            continue;
 
        if (i > 0)
        {
            ans.emplace_back(i);
        }
 
        y_combinator([&G, &visited](auto dfs, int cur) -> void {
            visited[cur] = true;
            for (auto next : G[cur])
                if (!visited[next]) dfs(next);
        })(i);
    }
    cout << ans.size() << "\n";
    for (auto el : ans)
        cout << 1 << " " << el+1 << "\n";
}
