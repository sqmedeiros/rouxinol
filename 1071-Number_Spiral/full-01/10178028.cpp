#include <bits/stdc++.h>
#define ll long long
 
using namespace std;
 
void solve() {
    ll x, y; cin>>x>>y;
    ll temp;
    if(x >= y) {
        if(x==1) {
            cout<<1<<"\n";
        }
        else {
            temp = x&1? (x-1)*(x-1)+1:x*x;
            cout<<(x&1?temp + y - 1:temp - y + 1)<<"\n";
        }
    }
    else {
        temp = y&1 ? y*y : (y-1)*(y-1) + 1;
        cout<<(y&1?temp - x + 1:temp + x - 1)<<"\n";
    }
}
 
int main() {
    int t; cin>>t;
    while(t--) {
        solve();
    }
    return 0;
}