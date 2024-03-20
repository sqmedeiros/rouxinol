#pragma GCC optimize("Ofast") 
        #pragma GCC target("avx,avx2,fma")
 
            #include <bits/stdc++.h>
            using namespace std;
            typedef long long ll;
            typedef vector<long long> vl;
            typedef vector<int> vi;
            #define PB push_back 
            #define MP make_pair
            #define ln "\n"
            #define max(a, b) (a < b ? b : a) 
            #define min(a, b) ((a > b) ? b : a) 
            //#define mod 1e9 + 7 
            #define forn(i,e) for(ll i=0; i<e; i++)
           
            #define vasort(v) sort(v.begin(), v.end())
            #define vdsort(v) sort(v.rbegin(), v.rend())
            
            #define F first
            #define S second
             
            #define out1(x1) cout << x1 << ln
            #define out2(x1,x2) cout << x1 << " " << x2 << ln
            #define out3(x1,x2,x3) cout << x1 << " " << x2 << " " << x3 << ln
            #define out4(x1,x2,x3,x4) cout << x1 << " " << x2 << " " << x3 << " " << x4 << ln
            #define out5(x1,x2,x3,x4,x5) cout << x1 << " " << x2 << " " << x3 << " " << x4 << " " << x5 << ln
            #define out6(x1,x2,x3,x4,x5,x6) cout << x1 << " " << x2 << " " << x3 << " " << x4 << " " << x5 << " " << x6 << ln
             
            #define in1(x1) cin >> x1
            #define in2(x1,x2) cin >> x1 >> x2
            #define in3(x1,x2,x3) cin >> x1 >> x2 >> x3
            #define in4(x1,x2,x3,x4) cin >> x1 >> x2 >> x3 >> x4
            #define in5(x1,x2,x3,x4,x5) cin >> x1 >> x2 >> x3 >> x4 >> x5
            #define in6(x1,x2,x3,x4,x5,x6) cin >> x1 >> x2 >> x3 >> x4 >> x5 >> x6
             
            #define arrin(a,n) forn(i,n) cin >> a[i];
            #define arrout(a,n) forn(i,n) {cout << a[i] << " ";} cout << ln;
             
            #define zoom ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
            int nxt() {int x; cin >> x; return x;}
            const ll INF = int(1e9) + 99;
            ll gcd(ll a, ll b)  {if (b == 0) return a;  return gcd(b, a % b);  } 
            //ll fact(ll n)    {ll t=1;if(n==0 ||n==1) return t; for(int i=2;i<=n;i++) t*=i; return t;} 
            const int N = int(2e5) + 99;
            vl plist;
           
 
    ll power(ll x,ll y,ll mod)
    {
        x=(x%mod+mod)%mod;
        if(x<=1)
            return x;
        ll z=x,ans=1;;
        while(y>0)
        {
            if(y&1)
                ans*=z;
 
            z=(z*z)%mod;
            y>>=1;
            ans%=mod;
 
        }
        return ans;
    }
      ll modInverse(ll a, ll m) 
    { 
        ll g = gcd(a, m); 
        if (g != 1) 
            {cout << "Inverse doesn't exist"; return 0;}
        else
        { 
            // If a and m are relatively prime, then modulo inverse 
            // is a^(m-2) mode m 
            return  power(a, m-2, m); 
        } 
    } 
 char a[1001][1001];
 int sx[]={-1,1,0,0};
 int sy[]={0,0,-1,1};
char sz[]={'D','U','R','L'};
string s1="";
 vector<vi> adj(100001);
 vector<int> visit(100001,0);
 vector<int> depth(100001,-1);
 vector<int> parent(100001,-1);
 static int flag=0,k1=0;
 void dfs(int i,int par,int k)
 {
    if(flag)
        return;
    parent[i]=par;
    for (auto x:adj[i])
        {
            if(x==par)
                continue;
            if(visit[x]==k && flag==0)
            {
                vi arr;
                arr.PB(x);
                int n=i;
                while(n!=-1)
                {
                    arr.PB(n);
                    if(n==x)
                        break;
                    n=parent[n];
 
                }
                out1(arr.size());//cout<<k1++<<ln;
                arrout(arr,arr.size());
                flag=1;
 
                return;
            }
            if(visit[x]==0)
                {visit[i]=k;dfs(x,i,k);}
        }
 
 }
 
    void solve()
    {  
        ll l,x=1,r,c,g,n,y,m,x1=0,x2=0,y1,y2,x3=0,ans=1e17-7,
        ans1=1e9+7,ans13=0,ans2=1,ans3=1,ans4=1,ans5=1e9+7,
        flag1=1,flag2=-1;int k=1;
        //cout<<"PARINI";
        cin>>n>>m;
        //vi vx(m),vy(m);
        forn(i,m)
        {
            cin>>x>>y;
           // vx[i]=x;vy[i]=y;
            adj[x].PB(y);
            adj[y].PB(x);
        }
        map<int,int> mp;
 
       for(int i=1;i<=n;i++)
       {
        
        if(visit[i]==0)
            {k++;visit[i]=k;dfs(i,-1,k);}
        if(flag)
            return;
 
       }
       cout<<"IMPOSSIBLE";
                 
    }
            int main() {
                #ifndef ONLINE_JUDGE
                freopen("input.txt","r",stdin); 
                freopen("output.txt","w",stdout);
                //freopen("error.txt","w",stderr);
                #endif
                zoom;
                //modFact(5001,1000000007);
                //SieveOfEratosthenes(100000);
                
                
                ll t=1,t1;
                
                //cin>>t;
                t1=t;
                while(t--){
                   //cout<<"Case "<<t1-t<<": ";
                    solve();
                    //cout<<ln;
                    //cerr<<t<<" ";
                 }
             }
