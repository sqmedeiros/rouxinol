#include <bits/stdc++.h>
using namespace std;
typedef long long ULL;
const ULL maxx = 1000000007;
 
int main()
{
    static ULL a[1000001];
    ULL b[100];
    ULL n, i, x, j, ans;
    cin >> n >> x;
    for(i = 0; i <= x; i++)
        a[i] = -1;
    for(i = 0; i < n; i++)
        cin >> b[i];
    sort(b, b + n);
    a[0] = 1;
    for(i = b[0]; i <= x; i++)
    {
        j = 0;
        ans = 0;
        while(b[j] <= i && j < x)
        {
            if(a[i - b[j]] > -1)
                ans += a[i - b[j]];
            ans %= maxx;
            j++;
        }
        if(ans > 0)
            a[i] = ans;
    }
    if(a[x] == -1)
        cout << 0;
    else
        cout << a[x];
    return 0;
}
