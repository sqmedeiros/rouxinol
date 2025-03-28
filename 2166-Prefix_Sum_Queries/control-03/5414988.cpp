/*
Prefix Sum Queries
 
    Task Submit Results Statistics 
 
    Time limit: 1.00 s Memory limit: 512 MB 
 
Given an array of n
integers, your task is to process q queries of the following types:
 
    update the value at position k
 
to u
 
what is the maximum prefix sum in range [a,b]
 
    ?
 
Input
 
The first input line has two integers n and q: the number of values and queries.
 
The second line has n integers x1,x2,…,xn: the array values.
 
Finally, there are q lines describing the queries. Each line has three integers: either "1 k u" or "2 a b".
 
Output
 
Print the result of each query of type 2.
 
Constraints
 
    1≤n,q≤2⋅105
 
 
−109≤xi,u≤109
 
1≤k≤n
 
1≤a≤b≤n
 
 
Example
 
Input:
8 4
1 2 -1 3 1 -5 1 4
2 2 6
1 4 -2
2 2 6
2 3 4
 
Output:
5
2
0
*/
 
/*
Time Complexity: $\mathcal O(N\log N)$
 
In this problem, we're given an array $a$ and we're asked to answer 2 types of
queries
 
update the value at position $i$ to $x$
calculate the maximum prefix sum in the range $[a, b]$
 
Solution 1 - Segment Tree
 
In each segment tree node, we will store
 
$\texttt{sum}$: the sum of the elements in the range
$\texttt{pref}$: the maximum prefix sum in the range
 
 
To calculate $\texttt{seg}[i]$,
 
The $\texttt{sum}$ would be equal to $\texttt{left}.\texttt{sum} + \texttt{right}.\texttt{sum}$.
The maximum prefix has to end at either the left segment ($\texttt{left}.\texttt{pref}$), or at the right segment ($\texttt{left}.\texttt{sum} + \texttt{right}.\texttt{pref}$), so $\texttt{pref}$ would equal $\max(\texttt{left}.\texttt{pref}, \texttt{left}.\texttt{sum} + \texttt{right}.\texttt{pref})$.
 
 
Now we can build and update any value in our segment tree.
 
To answer an query, we can split the range $[l, r]$ into $\mathcal O(\log N)$ segments. To calculate the answer, we just repeatedly merge these segments until there is one left and take the $\texttt{pref}$.
 
*/
 
#include <bits/stdc++.h>
using namespace std;
 
const int N = 200010;
const int S = 1 << 18;
 
int n, q, a[N];
 
struct node {
	long long sum, pref;
	node(long long sum, long long pref) : sum(sum), pref(pref) {}
	node(long long x = 0) : sum(x), pref(max(0LL, x)) {}
	friend node operator+(const node& a, const node& b) {
		return {a.sum + b.sum, max(a.pref, a.sum + b.pref)};
	}
} tt[S << 1];
 
void build(int k = 1, int l = 1, int r = n) {
	if (l == r) { tt[k] = node(a[l]); return; }
	int m = (l + r) >> 1;
	build(k << 1, l, m);
	build(k << 1 | 1, m + 1, r);
	tt[k] = tt[k << 1] + tt[k << 1 | 1];
}
 
void update(int i, int x, int k = 1, int l = 1, int r = n) {
	if (l == r) { tt[k] = node(x); return; }
	int m = (l + r) >> 1;
	if (i <= m) update(i, x, k << 1, l, m);
	else update(i, x, k << 1 | 1, m + 1, r);
	tt[k] = tt[k << 1] + tt[k << 1 | 1];
}
 
node query(int ql, int qr, int k = 1, int l = 1, int r = n) {
	if (ql > r || qr < l) return 0;
	if (ql <= l && qr >= r) return tt[k];
	int m = (l + r) >> 1;
	node q1 = query(ql, qr, k << 1, l, m);
	node q2 = query(ql, qr, k << 1 | 1, m + 1, r);
	return q1 + q2;
}
 
int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	build();
	for (int i = 0, t, x, y; i < q; ++i) {
		scanf("%d%d%d", &t, &x, &y);
		if (t == 1) update(x, a[x] = y);
		else printf("%lld\n", query(x, y).pref);
	}
}
 
/*
We can use a segment tree with lazy propagation to solve this
problem. Let $\texttt{ps}[i]$ be the sum of $a_1, a_2, \dots a_i$. We can
maintain a segment tree consisting of the maximum $\texttt{ps}$ in the range of
$[l,r]$.
 
To update the value at position $i$ to $x$, we add $x-a_i$ to each of the values
in the range $[i,N]$.
 
To answer a query of type 2, our answer would be
$\max_{i \in [a, b]}(\texttt{ps}[i]) - \texttt{ps}[{a-1}]$.
*/
 
/*
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
 
template<class T> struct LSegTree {
	int N; vector<T> t, lz; T U=-1e18;
	T F(T i, T j) { return max(i,j); } LSegTree() {}
	LSegTree(int N) : N(N), t(4*(N+1),U), lz(4*(N+1),0) {}
	void pull(int i) { t[i] = F(t[i*2],t[i*2+1]); }
	void push(int i, int l, int r) {
		t[i]+=lz[i];
		if(l!=r) lz[i*2]+=lz[i], lz[i*2+1]+=lz[i];
		lz[i]=0; }
	void build(vector<ll> &v) { build(v,1,0,N); }
	void build(vector<ll> &v, int i, int l, int r) {
		if(l==r) { t[i]=v[l]; return; } int m=(l+r)/2;
		build(v,i*2,l,m); build(v,i*2+1,m+1,r); pull(i);
	}
	void upd(int L, int R, T v) { upd(L,R,v,1,0,N); }
	void upd(int L, int R, T v, int i, int l, int r) {
		push(i,l,r); if(R<l || L>r) return;
		if(L<=l && R>=r) { lz[i]+=v; push(i,l,r); return; }
		int m=(l+r)/2; upd(L,R,v,i*2,l,m);
		upd(L,R,v,i*2+1,m+1,r); pull(i);
	}
	T qry(int L, int R) { return qry(L,R,1,0,N); }
	T qry(int L, int R, int i, int l, int r) {
		push(i,l,r); if(R<l || L>r) return U;
		if(L<=l && R>=r) return t[i]; int m=(l+r)/2;
		return F(qry(L,R,i*2,l,m), qry(L,R,i*2+1,m+1,r));
	}
};
 
int n, q;
vector<ll> a, ps;
LSegTree<ll> st;
 
int main() {
 
	cin >> n >> q;
	a = ps = vector<ll>(n+1);
	for(int i=1; i<=n; i++) cin >> a[i];
 
	// construct ps
	ps[0] = 0;
	for(int i=1; i<=n; i++) ps[i] = ps[i-1] + a[i];
 
	// construct the segment tree
	st = LSegTree<ll>(n);
	st.build(ps);
 
	// queries
	while(q--) {
		int t; cin >> t;
		if(t==1) {
			// update a[i] to x
			int i; ll x; cin >> i >> x;
			st.upd(i, n, x-a[i]); a[i]=x;
		} else {
			// max ps in the range [a,b] - ps[a-1]
			int a, b; cin >> a >> b;
			cout << st.qry(a-1,b) - st.qry(a-1,a-1) << '\n';
		}
	}
 
}
 
*/
