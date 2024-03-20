#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <cmath>
using namespace std;
 
struct node {
    long long max_prefix;
    long long sum;
};
 
long long n_nodes, n_tests, s = 1;
node tree[520000];
 
node find_max(node a, node b) {
    node result;
    result.max_prefix = max(a.max_prefix, b.max_prefix + a.sum);
    result.sum = a.sum + b.sum;
    return result;
}
 
void update(long long node, long long value) {
    tree[node].sum = value;
    tree[node].max_prefix = max(value, 0LL);
    while (node > 1) {
        node >>= 1;
        tree[node] = find_max(tree[node * 2], tree[node * 2 + 1]);
    }
}
 
node read(long long number, long long first, long long last, long long f, long long l) {
    if (first == f && last == l)
        return tree[number];
    int m = (f + l) / 2;
    if (last <= m)
        return read(number * 2, first, last, f, m);
    if (m < first)
        return read(number * 2 + 1, first, last, m + 1, l);
    return find_max(read(number * 2, first, m, f, m), read(number * 2 + 1, m + 1, last, m + 1, l));
}
 
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n_nodes >> n_tests;
    while (s <= n_nodes)
        s <<= 1;
    for (long long i = s; i < s + n_nodes; i++) {
        cin >> tree[i].sum;
        tree[i].max_prefix = max(tree[i].sum, 0LL);
    }
    for (int i = s - 1; i > 0; i--)
        tree[i] = find_max(tree[i * 2], tree[i * 2 + 1]);
    for (long long i = 0; i < n_tests; i++) {
        long long type;
        cin >> type;
        if (type == 1) {
            long long position, value;
            cin >> position >> value;
            update(position + s - 1, value);
        }
        else {
            long long first, last;
            cin >> first >> last;
            cout << read(1, first - 1, last - 1, 0, s - 1).max_prefix << '\n';
        }
    }
}
