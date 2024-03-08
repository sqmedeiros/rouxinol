#include<bits/stdc++.h>
using namespace std;
 
int ans = 0, nx[] = {1, 0, -1, 0}, ny[] = {0, -1, 0, 1};
 
bool isVal(int x, int y, int m, int n)
{
    // cout<<"7";
    if(x < 1) return false;
    if(y < 1) return false;
    if(x > n) return false;
    if(y > m) return false;
    return true;
}
 
void DFS(int x, int y, string s[], vector<bool> vis[], int m, int n)
{
    vis[x][y] = true;
    // cout<<"5";
    for (int i = 0; i < 4; i++)
    {
        int newx = x + nx[i];
        int newy = y + ny[i];
        // cout<<"6";
        if(s[newx][newy]=='.' && !vis[newx][newy] && isVal(newx, newy, m, n)) DFS(newx, newy, s, vis, m, n);
        // cout<<"8";
    }
    
}
 
int main()
{
    int n, m;
    cin>>n>>m;
    string grid[n+1];
    // cout<<"1";
    for (int i = 1; i < n+1; i++)
    {
        cin>>grid[i];
        grid[i] = '0'+grid[i];
    }
    // cout<<"2";
    vector<bool> visited[n+1];
    for (int i = 0; i < n+1; i++)
    {
        for (int j = 0; j < m+1; j++)
        {
            visited[i].push_back(false);
        }    
    }
    // cout<<"3";
    for (int i = 1; i < n+1; i++)
    {
        for (int j = 1; j < m+1; j++)
        {
            if(grid[i][j]=='.' && !visited[i][j])
            {
                // cout<<"4";
                DFS(i, j, grid, visited, m, n);
                ans++;
            } 
        }    
    }
    cout<<ans<<'\n';
    
    return 0;
}
