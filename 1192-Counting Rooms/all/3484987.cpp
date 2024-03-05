#include<bits/stdc++.h>
#define ll long long
#define str string
using namespace std;
int n,m,fix[1001][1001],ans;
char rum[1001][1001];
void rec(int i,int j){
	fix[i][j]=true;
	if(fix[i-1][j]==false && rum[i-1][j]=='.'){
		rec(i-1,j);
	}
	if(fix[i+1][j]==false && rum[i+1][j]=='.'){
		rec(i+1,j);
	}
	if(fix[i][j-1]==false && rum[i][j-1]=='.'){
		rec(i,j-1);
	}
	if(fix[i][j+1]==false && rum[i][j+1]=='.'){
		rec(i,j+1);
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>rum[i][j];
		}	
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(fix[i][j]==false && rum[i][j]=='.'){
				ans++;
				rec(i,j);
			}
		}	
	}
	cout<<ans;
}
