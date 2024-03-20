#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
using pll = pair<ll, ll>;
 
#define F first
#define S second
#define ep emplace
#define eb emplace_back
#define ALL(x) x.begin(), x.end()
 
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
 
void debug() {
	cout << endl;
}
template<class T, class ...U> void debug(T a, U ...b) {
	cout << a << ' ';
	debug(b...);
}
/*-----------------------------------------*/
 
const int N = 2e5 + 5;
ll pre[N], arr[N]; 
 
 
struct Node {
	static Node mem[N * 2], *pmem;
	ll mx, tag;
	Node *lc, *rc;
	Node(ll x) {
		mx = x;
		tag = 0;
		lc = rc = 0;
	}
	Node() {}
} Node::mem[2 * N], *Node::pmem = mem;
 
void push(Node *node, int l, int r) {
	if(node->tag && l != r) {
		node->lc->mx += node->tag;
		node->lc->tag += node->tag;
		node->rc->mx += node->tag;
		node->rc->tag += node->tag;
	}
	node->tag = 0;
}
void pull(Node* node) {
	node->mx = max(node->lc->mx, node->rc->mx);
}
 
Node* build(int l, int r) {
	Node *node = new(Node::pmem++) Node;
	if(l == r) {
		node->mx = pre[l];
		return node;
	}
	int m = (l + r) >> 1;
	node->lc = build(l, m);
	node->rc = build(m + 1, r);
	pull(node);
}
 
void upd(Node *node, int ql, int qr, ll x, int l, int r) {
	if(ql <= l && r <= qr) {
		node->mx += x;
		node->tag += x;
		return;
	}
	if(r < ql || qr < l) return;
	int m = (l + r) >> 1;
	push(node, l, r);
	upd(node->lc, ql, qr, x, l, m);
	upd(node->rc, ql, qr, x, m + 1, r);
	pull(node);
}
 
ll qry(Node *node, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) {
		return node->mx;
	}
	if(r < ql || qr < l) return -LINF;
	int m = (l + r) >> 1;
	push(node, l, r);
	return max(qry(node->lc, ql, qr, l, m), qry(node->rc, ql, qr, m + 1, r));
}
 
void solve() {
	int n, q; cin >> n >> q;
	for(int i = 1; i <= n; ++i) {
		cin >> arr[i];
		pre[i] = pre[i - 1] + arr[i];
	}
	Node *root = build(1, n);
	while(q--) {
		int op, a, b; cin >> op >> a >> b;
		if(op == 1) {
			upd(root, a, n, b - arr[a], 1, n);
			arr[a] = b;
		}
		else {
			ll tmp = (a - 1 == 0 ? 0 : qry(root, a - 1, a - 1, 1, n));
			cout << max(0ll, qry(root, a, b, 1, n) - tmp) << '\n';
		}
	}
}
 
signed main() {
	cin.tie(0), ios::sync_with_stdio(0);
	solve();
}
