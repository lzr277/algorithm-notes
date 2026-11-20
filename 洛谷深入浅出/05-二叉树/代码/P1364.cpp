#include <bits/stdc++.h>
#define int long long
using namespace std;

vector<int> g[105];
int w[105],d[105],q[105];
signed main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int l,r;
        cin>>w[i]>>l>>r;
        if(l)
        {
            g[i].push_back(l);
            g[l].push_back(i);
        }
        if(r)
        {
            g[i].push_back(r);
            g[r].push_back(i);
        }
    }
    int ans=LLONG_MAX;
    for(int start=1;start<=n;start++)
    {
        memset(d,-1,sizeof d);
        int hh=0,tt=0,cost=0;
        q[0]=start;
        d[start]=0;
        while(hh<=tt)
        {
            int u=q[hh++];
            cost+=w[u]*d[u];
            for(int v:g[u])
            {
                if(d[v]!=-1) continue;
                d[v]=d[u]+1;
                q[++tt]=v;
            }
        }
        ans=min(ans,cost);
    }
    cout<<ans<<'\n';
    return 0;
}
