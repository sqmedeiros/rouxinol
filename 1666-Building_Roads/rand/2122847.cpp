#include <bits/stdc++.h>
using namespace std;
 
int link[1000001];
int size[1000001];
 
int find(int x){
    while(x != link[x]){
        x = link[x];
    }
    return x;
}
 
bool same(int a, int b){
    return find(a)==find(b);
}
 
void unite(int a,int b){
    a = find(a);
    b = find(b);
    if(size[a]<size[b]){
        size[b] += size[a];
        link[a] = b;
    }
    else{
        size[a] += size[b];
        link[b] = a;
    }
}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    int n,m;
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        link[i] = i;
        size[i] = 1;
    }
    int a,b,ans=n-1;
 
    for(int i=0;i<m;i++){
        cin >> a >> b;
        if(!same(a,b)){
            unite(a,b);
            ans--;
        }
    }
 
    cout << ans << "\n";
    for(int i=2;i<=n;i++){
        if(!same(1,i)){
            unite(1,i);
            ans--;
            cout << 1 << " " << i << "\n";
        }
    }
}
