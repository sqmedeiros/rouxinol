#include <bits/stdc++.h>
using namespace std;
 
template <class T>
using v = vector<T>;
 
template <class T>
using p = pair<T, T>;
using ll = long long;
using dd = long double;
using mpi = map<int, int>;
using mpl = map<ll, ll>;
 
#define all(x) x.begin(), x.end()
#define f first
#define s second
 
// BIG NUMBERS (MODULAR)
const ll N = 998244353;
const ll M = (ll)1e9 + 7;
 
// binary exponentiation
ll binpow(ll a, ll n)
{
    ll res = 1;
    ll cnt = a;
    while (n > 0)
    {
        if (n % 2 == 0)
        {
            n /= 2;
            cnt *= cnt % M;
            cnt %= M;
            continue;
        }
        res *= cnt % M;
        cnt *= cnt % M;
        n /= 2;
    }
    return res % M;
}
 
// binary search implementation for square roots
ll SQRT(ll a)
{
    ll l = 0;
    ll r = 20000000000;
    while (l < r)
    {
        ll mid = (l + r) / 2;
        if (mid * mid > a)
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    return l - 1;
}
 
// MULTITEST TOGGLE
const bool test = true;
/*-------------------------------------------------------------------------------*/
 
void solve()
{
    ll x, y;
    cin >> x >> y;
    ll z = max(x, y);
    ll mid = z * z - z + 1;
    ll diff = abs(x - y);
    if (z % 2)
    {
        if (x <= y)
        {
            cout << mid + diff << endl;
        }
        else
        {
            cout << mid - diff << endl;
        }
    }
    else
    {
        if (x > y)
        {
            cout << mid + diff << endl;
        }
        else
        {
            cout << mid - diff << endl;
        }
    }
}
int main()
{
    /*Command Line
    g++ forkiespad.cpp -o forkiespad
    forkiespad.exe
    */
    ios::sync_with_stdio();
    cin.tie(0);
    // testcases
    int t;
    if (test)
    {
        cin >> t;
    }
    else
        t = 1;
 
    while (t--)
    {
        solve();
    }
}
 
/*
-try out more cases
-attack the problem creatively/at different angles
-what am i missing?
-CHECK YOUR CODE
-pay attention to BOUNDS
-errors - out of bounds, edge case(n=0, n=1?), integer overflow, etc.
-WHEN IN DOUBT, USE LONG LONG
-check the for loops
-watch out for division errors (use double and ll when needed)
*/
