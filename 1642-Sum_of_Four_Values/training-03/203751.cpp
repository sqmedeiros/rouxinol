#pragma GCC optimize ("Ofast")
#include<bits/stdc++.h>
#define pb push_back
#define __V vector
#define all(x) x.begin(), x.end()
#define oit ostream_iterator
#define mod 1000000007ll
using namespace std;
void doin() {
	cin.tie();
	cout.tie();
	ios::sync_with_stdio(0);
#ifndef ONLINE_JUDGE
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif
}
template<typename X, typename Y>
istream& operator>>(istream& in, pair<X, Y> &a) {
	in >> a.first >> a.second;
	return in;
}
template<typename T>
void getv(T& i) {
	cin >> i;
}
template<typename T, typename ... Ns>
void getv(vector<T>& v, int n, Ns ... ns) {
	v.resize(n);
	for (auto& i : v)
		getv(i, ns...);
}
template<typename T>
void getv1(T& i) {
	cin >> i;
}
template<typename T, typename ... Ns>
void getv1(vector<T>& v, int n, Ns ... ns) {
	v.resize(n + 1);
	for (int i = 1; i <= n; i++)
		getv1(v[i], ns...);
}
#ifdef _WIN32
#define getchar_unlocked() _getchar_nolock()
#define _CRT_DISABLE_PERFCRIT_LOCKS
#endif
inline void getch(char &x) {
	while (x = getchar_unlocked(), x < 33) {
		;
	}
}
inline void getstr(string &str) {
	str.clear();
	char cur;
	while (cur = getchar_unlocked(), cur < 33) {
		;
	}
	while (cur > 32) {
		str += cur;
		cur = getchar_unlocked();
	}
}
template<typename T> inline bool sc(T &num) {
	bool neg = 0;
	int c;
	num = 0;
	while (c = getchar_unlocked(), c < 33) {
		if (c == EOF)
			return false;
	}
	if (c == '-') {
		neg = 1;
		c = getchar_unlocked();
	}
	for (; c > 47; c = getchar_unlocked())
		num = num * 10 + c - 48;
	if (neg)
		num *= -1;
	return true;
}
typedef unsigned long long ull;
typedef long long ll;
typedef float ld;
typedef ll _I;
typedef pair<_I, _I> pi;
typedef pair<ld, ld> pd;
typedef map<_I, _I> mii;
typedef __V <_I> vi;
typedef __V <char> vc;
typedef __V <ld> vd;
typedef __V <vd> vvd;
typedef __V <pi> vpi;
typedef __V <__V<_I>> vvi;
typedef __V <__V<char>> vvc;
typedef __V <__V<pi>> vvpi;
using AntonTsypko = void;
using arsijo = AntonTsypko;
using god = arsijo;
uniform_real_distribution<double> double_dist(0, 1);
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int main() {
	doin();
	ll n, x;
	cin >> n >> x;
	vi a, b;
	getv(a, n);
	map<int, vpi> s;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			s[a[i] + a[j]].pb( { i, j });
		}
	}
	for (auto& i : s)
		sort(all(i.second));
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			auto& b = s[x-a[i]-a[j]];
			auto it = lower_bound(all(b),pi({i, j}));
			if(it != b.begin()) {
				auto t = it-1;
				if(t->first != i && t->second != i && t->first != j && t->second != j) {
					cout << i+1 << " " << j+1 << " " << t->first+1 << " " << t->second+1 << "\n";
					return 0;
				}
			}
			if(it != b.end()) {
				auto t = it;
				if(t->first != i && t->second != i && t->first != j && t->second != j) {
					cout << i+1 << " " << j+1 << " " << t->first+1 << " " << t->second+1 << "\n";
					return 0;
				}
				if(++it != b.end()) {
					auto t = it;
					if(t->first != i && t->second != i && t->first != j && t->second != j) {
						cout << i+1 << " " << j+1 << " " << t->first+1 << " " << t->second+1 << "\n";
						return 0;
					}
				}
			}
		}
	}
	cout << "IMPOSSIBLE";
	return 0;
}
