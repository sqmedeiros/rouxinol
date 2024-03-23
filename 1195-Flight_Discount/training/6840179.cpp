#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("bmi,bmi2,lzcnt,popcnt")
using namespace std;
 
 
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#ifdef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
 
 
#define ll long long
#define ld long double
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()
 
#define PI 3.1415926535897932384626433832795l 
const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
const ld EPS = 1e-9;
 
struct box
{
    /* data */
    int u,v;
    ll w;
};
 
vector<ll> shortest_path(int src,int target,const vector<vector<pair<int,ll>>> &graph){
    int n = graph.size();
    int m = graph[0].size();
 
    vector<ll> dist(n,LLONG_MAX);
    dist[src]=0;
    vector<bool> visited(n,false);
 
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
    pq.push({0,src});
 
    while(!pq.empty()){
        auto t = pq.top();
        pq.pop();
        if(visited[t.second]){
            continue;
        }
        visited[t.second]=true;
        for(auto v : graph[t.second]){
            if(t.first+v.second < dist[v.first]){
                dist[v.first]=t.first+v.second;
                pq.push({dist[v.first],v.first});
            }
        }
    }
    return dist;
}
void solve() {
    // Add your solution here
    int n,m;
    cin>>n>>m;
    vector<vector<pair<int,ll>>> graph(n);
    vector<vector<pair<int,ll>>> reverses_graph(n);
    vector<box> edge;
    for(int i=0;i<m;i++){
        int a,b;
        ll c;
        cin>>a>>b>>c;
        a--;
        b--;
        box t;
        t.u=a;
        t.v=b;
        t.w=c;
        edge.push_back(t);
        graph[a].push_back({b,c});
        reverses_graph[b].push_back({a,c});
    }
    
    vector<ll> dist1;
    vector<ll> dist2;
 
    dist1 = shortest_path(0,n-1,graph);
    dist2 = shortest_path(n-1,0,reverses_graph);
 
    ll ans = LLONG_MAX;
    for(box temp:edge){
        ll discount = (ll)floor(temp.w/2);
        ll a=dist1[temp.u];
        ll b=dist2[temp.v];
 
        if(a==LLONG_MAX || b==LLONG_MAX){
            continue;
        }
 
        ans = min(ans,a+discount+b);
    }
    cout<<ans;
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}
// #include <iostream>
// #include <queue>
// #include <vector>
// #include <cstdint>
// using std::cout;
// using std::endl;
// using std::pair;
// using std::vector;
 
// /**
//  * given a start point, and an adjacency list with costs,
//  * this function gives an array with the minimum distances
//  * from all the other nodes to the start node
//  * (the value is INT64_MAX if unreachable)
//  */
// vector<long long> min_costs(int from,
//                             const vector<vector<pair<int, int>>> &neighbors) {
// 	vector<long long> min_costs(neighbors.size(), LLONG_MAX);
// 	min_costs[from] = 0;
// 	std::priority_queue<pair<long long, int>> frontier;
// 	frontier.push({0, from});
// 	while (!frontier.empty()) {
// 		pair<long long, int> curr_state = frontier.top();
// 		frontier.pop();
// 		int curr = curr_state.second;
// 		if (-curr_state.first != min_costs[curr]) { continue; }
 
// 		for (auto [n, nc] : neighbors[curr]) {
// 			long long new_cost = min_costs[curr] + nc;
// 			if (new_cost < min_costs[n]) {
// 				min_costs[n] = new_cost;
// 				frontier.push({-new_cost, n});
// 			}
// 		}
// 	}
// 	return min_costs;
// }
 
// int main() {
// 	int city_num;
// 	int flight_num;
// 	std::cin >> city_num >> flight_num;
// 	vector<vector<pair<int, int>>> neighbors(city_num);
// 	vector<vector<pair<int, int>>> reverse_neighbors(city_num);
// 	for (int f = 0; f < flight_num; f++) {
// 		int from;
// 		int to;
// 		int cost;
// 		std::cin >> from >> to >> cost;
// 		neighbors[--from].push_back({--to, cost});
// 		reverse_neighbors[to].push_back({from, cost});
// 	}
 
// 	vector<long long> start_costs = min_costs(0, neighbors);
// 	vector<long long> end_costs = min_costs(city_num - 1, reverse_neighbors);
// 	long long total_min = INT64_MAX;
// 	for (int c = 0; c < city_num; c++) {
// 		for (auto [n, nc] : neighbors[c]) {
// 			if (start_costs[c] == INT64_MAX || end_costs[n] == INT64_MAX) {
// 				continue;
// 			}
// 			total_min =
// 			    std::min(total_min, start_costs[c] + (nc / 2) + end_costs[n]);
// 		}
// 	}
// 	cout << total_min << endl;
// }
