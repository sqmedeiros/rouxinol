#include<bits/stdc++.h>
using namespace std;
#define ll long long int
ll mod=1000000007;
 
 
 
main()
{
 
   ll t,n,y,i,j,k,m,a,b;
   map<ll,ll>mp;
   vector<pair<ll,ll>>vect;
   cin>>n;y=0;
   ll z[n],zz[n];
   for(i=0;i<n;i++)
   {
 
      cin>>z[i]>>zz[i];
     // vect.push_back({b,a});
 
   }
   sort(z,z+n);sort(zz,zz+n);
   y=0;j=0;ll ans=1;
   for(i=0;i<n;i++)
   {
         if( z[i] <= zz[j])y++;
         else {  ans=max(ans,y);y--;j++;i--;}
 
 
 
 
 
   }
   ans=max(ans,y);
 
   cout<<ans<<endl;
 
 
 
    return 0;
}
