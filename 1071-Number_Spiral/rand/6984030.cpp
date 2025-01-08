#include <bits/stdc++.h>
 
using namespace std;
 
 
void solve(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long int x, y, r;
    cin >> x >> y;
    if (x < y){
        if (y % 2 == 1){
            r = y * y;
            cout << r - x + 1 << endl;
        }
        else{
            r = (y - 1) * (y - 1) + 1;
            cout << r + x - 1 << endl;
        }
    }
    else{
        if (x % 2 == 0){
            r = x * x;
            cout << r - y + 1 << endl;
        }
        else{
            r = (x - 1) * (x - 1) + 1;
            cout << r + y - 1 << endl;
        }
    }
}
 
 
int main(){
    int t;
    cin >> t;
    for (int tc = 0; tc < t; tc++){
        solve();
    }
    return 0;
}