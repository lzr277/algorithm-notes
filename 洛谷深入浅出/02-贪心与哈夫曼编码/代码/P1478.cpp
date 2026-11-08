#include <bits/stdc++.h>
#define int long long
using namespace std;

int cost[5005];
signed main()
{
    int n,s,a,b,cnt=0;
    cin>>n>>s>>a>>b;
    for(int i=1;i<=n;i++)
    {
        int x,y;
        cin>>x>>y;
        if(x<=a+b) cost[++cnt]=y;
    }
    sort(cost+1,cost+cnt+1);
    int ans=0;
    for(int i=1;i<=cnt;i++)
    {
        if(cost[i]>s) break;
        s-=cost[i];
        ans++;
    }
    cout<<ans<<'\n';
    return 0;
}
