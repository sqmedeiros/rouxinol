        #include <bits/stdc++.h>
        #include <ext/pb_ds/assoc_container.hpp>
        using namespace __gnu_pbds;
        using namespace std;
         
        #define ff              first
        #define ss              second
        #define int64         long long
        #define pb              push_back
        #define mp              make_pair
        #define pii             pair<int,int>
        #define vi              vector<int>
        #define mii             map<int,int>
        #define pqb             priority_queue<int>
        #define pqs             priority_queue<int,vi,greater<int> >
        #define setbits(x)      __builtin_popcountll(x)
        #define zrobits(x)      __builtin_ctzll(x)
        #define mod             1000000007
        #define inf             1e18
        #define ps(x,y)         fixed<<setprecision(y)<<x
        #define mk(arr,n,type)  type *arr=new type[n];
        #define w(x)            int x; cin>>x; while(x--)
        mt19937                 rng(chrono::steady_clock::now().time_since_epoch().count());
         
        typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;
         
         
        void solve(){
            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
        // #ifndef ONLINE_JUDGE
        //     freopen("input.txt", "r", stdin);
        //     freopen("output.txt", "w", stdout);
        // #endif
        }
          void solve1(){
            int k;
            cin>>k;
            int n;
            cin >> n;   
            vector<int> dp(n+1,0);    
            vector<int> deno(k);
            for(int i=0;i<k;i++){
                cin>>deno[i];
            }
            dp[0]=1;
            for(int i=1;i<n+1;i++){     //0(N)
                for(int j=0;j<k;j++){ //O(K)
                    if(i>=deno[j]){
                        dp[i]=(dp[i]+dp[i-deno[j]]) %mod;
                    }
                }
            }   
            cout<<dp[n];
        }
         
            int32_t main()
            {
                solve(); 
                solve1();
            }
