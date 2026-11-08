#include <bits/stdc++.h>
#define int long long
using namespace std;

struct node
{
    int p,a;
}a[5005];
bool cmp(node x,node y)
{
    return x.p<y.p;
}
signed main()
{
    int need,m,ans=0;
    cin>>need>>m;
    for(int i=1;i<=m;i++) cin>>a[i].p>>a[i].a;
    sort(a+1,a+m+1,cmp);
    for(int i=1;i<=m&&need>0;i++)
    {
        int buy=min(need,a[i].a);
        ans+=buy*a[i].p;
        need-=buy;
    }
    cout<<ans<<'\n';
    return 0;
}
