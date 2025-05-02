#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
int main()
{
    int n;
    long long r=0,c=0,y=0,p=0;
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>n;
    for(int i=0;i<n;i++)
    {
       cin>>r>>c;
       if(r>=c)
       {
        y=(r*r)-r+1;
        if(r%2==0)
        {
          p=y+(r-c);  
        }
        else{
            p=y-(r-c);
        }
       }
       else
       {
        y=(c*c)-c+1;
        if(c%2==0)
        {
            p=y-(c-r);
        }
        else{
            p=y+(c-r);
        }
       }
       cout<<p<<"\n";
 
    }
    return 0;
}
