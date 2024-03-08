#include<bits/stdc++.h>
using namespace std;
#define ll long long
bool bmap[1001][1001];
bool visit[1001][1001];
void dfs(int row,int col,int height,int width)
{
  if(visit[row][col]) return;
  visit[row][col]=true;
  if((row+1<=height) &&bmap[row+1][col]) dfs(row+1,col,height,width);
  if((col+1<=width) &&bmap[row][col+1]) dfs(row,col+1,height,width);
  if((row-1>=0) &&bmap[row-1][col]) dfs(row-1,col,height,width);
  if((col-1>=0) &&bmap[row][col-1]) dfs(row,col-1,height,width);
 
}
int connected_components(int height,int width)
{
  int ans=0;
  for(int row=1;row<=height;row++)
  {
    for(int col=1;col<=width;col++)
    {
      //cout<<bmap[row][col];
      if(bmap[row][col] && !visit[row][col]) 
      {
        //cout<<"row:"<<row<<" col:"<<col<<endl;
        ans++;
        dfs(row,col,height,width);
      }
    }
    //cout<<endl;
  }
  return ans;
}
int main()
{
ios_base::sync_with_stdio(false);
cin.tie(NULL);
int height,width;
cin>>height>>width;
for(int i=0;i<height;i++)
{
  string s;
  cin>>s;
  for(int j=1;j<=width;j++) 
    {
      if(s[j-1]=='#') bmap[i+1][j]=false;
      else bmap[i+1][j]=true;
      visit[i+1][j]=false;
    }
}
cout<<connected_components(height,width)<<endl;
 
}
 
 
 
 
 
 
 
