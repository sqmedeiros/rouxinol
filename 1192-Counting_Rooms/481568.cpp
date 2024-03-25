#include <iostream>
#include<bits/stdc++.h>
using namespace std;
string str[1001]; 
int n,m;
bool visit[1001][1001];
void dfs(int i,int j)
{
	if(i>=0 && i<n && j>=0 && j<m && str[i][j]=='.')
	{
	visit[i][j]=true;
	if(visit[i+1][j]==false)
	dfs(i+1,j);
	if(visit[i-1][j]==false)
	dfs(i-1,j);
	if(visit[i][j+1]==false)
	dfs(i,j+1);
	if(visit[i][j-1]==false)
	dfs(i,j-1);
	}
}
int main() {
	// your code goes here
	int i,j;
	cin>>n>>m;
	for(i=0;i<n;i++)
	cin>>str[i];
	memset(visit,false,sizeof(visit));
	int ans=0;
	for(i=0;i<n;i++)
	for(j=0;j<m;j++)
	{
		if(str[i][j]=='.' && visit[i][j]==false)
		{
			ans++;
			dfs(i,j);
		}
	}
	cout<<ans<<endl;
	return 0;
}