#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
 
using namespace std;
 
typedef long long int ll;
typedef long double ld;
 
ll f(ll cur, vector<ll>::iterator it, ll sign, const ll &n, const ll &x){
    if(*it == 0){
        return sign * (x / cur);
    }
    __int128 cur1 = cur, p = (*it), x1 = x;
    if(cur1 * p > x1){
        return f(cur, next(it), sign, n, x);
    }
    return f(cur, next(it), sign, n, x) + f(cur * (*it), next(it), sign * -1, n, x);
}
 
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
    ll x, n, i;
    cin >> x >> n;
    vector<ll> a(n);
    for(i = 0; i < n; i++){
        cin >> a[i];
    }
    a.push_back(0);
    cout << x + f(1, a.begin(), -1, n, x);
    return 0;
}