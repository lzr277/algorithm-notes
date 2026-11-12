#include <bits/stdc++.h>
#define int long long
using namespace std;

int n,path[15],ans;
bool col[30],dg[30],udg[30];
void dfs(int u)
{
    if(u==n+1)
    {
        ans++;
        if(ans<=3)
            for(int i=1;i<=n;i++) cout<<path[i]<<(i==n?'\n':' ');
        return;
    }
    for(int i=1;i<=n;i++)
    {
        if(col[i]||dg[u+i]||udg[n-u+i]) continue;
        path[u]=i;
        col[i]=dg[u+i]=udg[n-u+i]=true;
        dfs(u+1);
        col[i]=dg[u+i]=udg[n-u+i]=false;
    }
}
signed main()
{
    cin>>n;
    dfs(1);
    cout<<ans<<'\n';
    return 0;
}
