#include "bits/stdc++.h"
 
#define int long long
 
#define all(x) x.begin(), x.end()
 
using namespace std;
 
const int N = 505;
int dis[N][N];
 
void floyd(){
	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= N; ++j) {
			if(i == j) dis[i][j] = 0;
			else if(dis[i][j] == 0)
			dis[i][j] = 1e18;
		}
	}
	
	for(int k = 1; k <= N; ++k)
	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= N; ++j) {
			dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
		}
	}
}
 
signed main() {
	int n, m, q;
	cin >> n >> m >> q;
	
	
	for(int i = 1; i <= m; ++i) {
		int x, y, w;
		cin >> x >> y >> w;
		
		if(dis[x][y] != 0) {
			dis[x][y] = min(dis[x][y], w);
		} else dis[x][y] = w;
		
		if(dis[y][x] != 0) {
			dis[y][x] = min(dis[y][x], w);
		} else dis[y][x] = w;
	}
	
	floyd();
	
	for(int i = 1; i <= q; ++i) {
		int x, y;
		cin >> x >> y;
		
		if(dis[x][y] == 1e18) cout << "-1\n";
		else cout << dis[x][y] << "\n";
	}
	
}
 
 
 
 
 
 
 
 
 
