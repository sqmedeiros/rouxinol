#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
using namespace std;
 
const int N=2e5+5;
int n,k,close[N];
vector<pair<int,int>> ev;
multiset<int> s;
 
int main() {
	#ifdef kvutxdy
	freopen("C:/Users/khanh/OneDrive/RoadtoPurple/Code/Codeforces/input.in", "r", stdin);
	#endif
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>k;
	for(int i=1;i<=n;++i){
		int l,r;
		cin>>l>>r;
		ev.emplace_back(l,i);
		ev.emplace_back(r,-i);
		close[i]=r;
	}
	sort(ev.begin(),ev.end());
	int res=n;
	for(auto it:ev){
		if(it.se<0){
			if(s.count(close[-it.se])) s.erase(close[-it.se]);
		}
		else{
			s.insert(close[it.se]);
		}
		while((int)s.size()>k){
			--res;
			auto y=--s.end();
			s.erase(y);
		}
	}
	cout<<res;
}
