#include <bits/stdc++.h>
#define int long long
using namespace std;

int k[205],d[205],q[205];
signed main()
{
    int n,a,b;
    cin>>n>>a>>b;
    for(int i=1;i<=n;i++) cin>>k[i];
    memset(d,-1,sizeof d);
    int hh=0,tt=0;
    q[0]=a;
    d[a]=0;
    while(hh<=tt)
    {
        int t=q[hh++];
        int next[2]={t+k[t],t-k[t]};
        for(int i=0;i<2;i++)
        {
            int j=next[i];
            if(j<1||j>n||d[j]!=-1) continue;
            d[j]=d[t]+1;
            q[++tt]=j;
        }
    }
    cout<<d[b]<<'\n';
    return 0;
}
