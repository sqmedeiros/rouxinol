#include <bits/stdc++.h>
using namespace std;
 
int main() {
  int n;
  cin>>n;
  long int x,y;
  while(n--){
    cin>>x>>y;
    if(x<y){
      if(y%2==1){
         long int r=y*y;
         cout<<r-x+1<<endl;
      }
      else{
         long int r=(y - 1) * (y - 1) + 1;
         cout << r + x - 1 << endl;
      }
    }
    else{
      if(x%2==0){
         long int r=x*x;
         cout<<r-y+1<<endl;
      }
      else{
       long int r = (x - 1) * (x - 1) + 1;
       cout << r + y - 1 << endl;
      }
    }
    
  }
  return 0;
}
