#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=1000005;
int lc[N],rc[N],q[N],d[N];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>lc[i]>>rc[i];
    int hh=0,tt=0,ans=0;
    q[0]=1;
    d[1]=1;
    while(hh<=tt)
    {
        int u=q[hh++];
        ans=max(ans,d[u]);
        if(lc[u])
        {
            d[lc[u]]=d[u]+1;
            q[++tt]=lc[u];
        }
        if(rc[u])
        {
            d[rc[u]]=d[u]+1;
            q[++tt]=rc[u];
        }
    }
    cout<<ans<<'\n';
    return 0;
}
