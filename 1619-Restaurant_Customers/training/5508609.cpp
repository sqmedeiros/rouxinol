/*
  "There is no light without dark
  There is no joy without pain
  You can't have a rainbow without a little rain"
  	  			 ~ Andrew Tate
 
*/
 
#include<bits/stdc++.h>
using namespace std;
 
#define int long long
#define pii pair<int,int>
#define bit(x, i) ((x >> i) & 1)
 
const int mod = 1e9 + 7;
const int maxn = 1e6;
const int base = 31;
 
void file()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
}
 
main()
{
	file();
	int n; cin >> n;
	vector<pii> v;
	for(int i=0;i<n;i++){
		int x, y; cin >> x  >> y;
		v.push_back({x, 1});
		v.push_back({y, -1});
	}
	sort(v.begin(), v.end());
	int ans = 0, cnt = 0;
	for(auto it: v){
		cnt += it.second;
		ans = max(ans, cnt);
	}
	cout << ans;
	return 0;
}
 
