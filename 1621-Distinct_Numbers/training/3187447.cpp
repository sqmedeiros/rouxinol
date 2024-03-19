/*CP is fun!
DANGER: always put brackets around 1<<j like.. (1<<j)
binary lifting-> reverse mein
Fenwick tree mein testcase ke andar wali max value size ko add() function mein rakhna (MAX global wali MAT RAKHNA PLEASE!)....hazar baar galti kar chuka hoon bohot annoying hai ! Cmon!!!!
*/
#include <bits/stdc++.h>
#define pb push_back
#define int long long
#define ll long long
#pragma GCC optimize("O3") //how good is this? lol
//#pragma GCC target("sse,sse2,sse3,sse4,popcnt,fma")
#pragma GCC optimize("unroll-loops")
using namespace std;
const int MAXN=2e3+5;
const int MAXL=32;
const int MOD=998244353;
const int MAX=2e7+5;
const int MAXA=5e3+5;
const int INF=2e18;
 
int powerm(int a,int b) { //m-> mod
    if(b==0) {
        return 1;
    }
    int curr=a,res=1;
    for(int i=0;i<MAXL;i++) {
        if((1LL<<i)&b) {
            res=(res*curr)%MOD;
        }
        curr=(curr*curr)%MOD;
    }
    return res;
}
