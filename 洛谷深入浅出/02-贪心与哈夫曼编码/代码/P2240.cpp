#include <bits/stdc++.h>
#define int long long
using namespace std;

struct node
{
    int m,v;
}a[105];

bool cmp(node x,node y)
{
    return x.v*y.m>y.v*x.m;
}

signed main()
{
    int n,t;
    cin>>n>>t;
    for(int i=1;i<=n;i++) cin>>a[i].m>>a[i].v;
    sort(a+1,a+n+1,cmp);

    double ans=0;
    for(int i=1;i<=n&&t>0;i++)
    {
        int take=min(t,a[i].m);
        ans+=1.0*take*a[i].v/a[i].m;
        t-=take;
    }

    cout<<fixed<<setprecision(2)<<ans<<'\n';
    return 0;
}
