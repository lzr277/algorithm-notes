#include <bits/stdc++.h>
#define int long long
using namespace std;

int a[25],s[5],n,best;
void dfs(int u,int left,int right)
{
    if(max(left,right)>=best) return;
    if(u==n+1)
    {
        best=max(left,right);
        return;
    }
    dfs(u+1,left+a[u],right);
    dfs(u+1,left,right+a[u]);
}
signed main()
{
    for(int i=1;i<=4;i++) cin>>s[i];
    int ans=0;
    for(int subject=1;subject<=4;subject++)
    {
        n=s[subject];
        best=0;
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
            best+=a[i];
        }
        dfs(1,0,0);
        ans+=best;
    }
    cout<<ans<<'\n';
    return 0;
}
