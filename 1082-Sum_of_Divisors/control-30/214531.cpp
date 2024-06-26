﻿#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <set>
#include <map>
#include <math.h>
#include <cmath>
#include <queue>
#include <iomanip>
#include <bitset>
#include <unordered_map>
#include <stack>
#include <memory.h>
#include <list>
#include <random>
#include <unordered_set>
#include <complex>
#include <assert.h>
#include <deque>
#define LL long long
#define ll long long
#define ld long double
#define ull unsigned ll
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define pii pair<int, int> 
#define pll pair<ll, ll> 
#define vi vector<int>
#define vpii vector<pii>
#define vpll vector<pll>
#define vll vector<ll>
#define vpii vector<pii>
#define vvi vector<vector<int>>
#define endl '\n'
#define forn(it,from,to) for(ll (it)=from; (it)<to; (it)++)
const ll  Inf = 1e18;
const ld  eps = 1e-7;
ll LINF = (ll)2e18;
using namespace std;
ll mod = 1e9 + 7;
ll mod5 = 1e9 + 9;
ll mod3 = 998244353;
ll mod4 = 1000003;
ll mod2 = 1e9 + 123;
const int MAXN = 201000; // число вершин
const int INF = 1000000000; // константа-бесконечность
 
int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#else
	//freopen("lines.in", "r", stdin);
	//freopen("javacert.out", "w", stdout);
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0); cout.setf(ios::fixed); cout.precision(20);
	ll n;
	cin >> n;
	ll ans = 0;
	for (ll i = 1; i * i <= n; i++) {
		ll q = n / i;
		q %= mod;
		ans += (q - (i - 1) + mod) * i;
		ans %= mod;
		ll tmp = q * (q + 1) / 2 - i * (i + 1) / 2;
		ans += tmp;
		ans %= mod;
	}
	cout << ans;
	return 0;
}
