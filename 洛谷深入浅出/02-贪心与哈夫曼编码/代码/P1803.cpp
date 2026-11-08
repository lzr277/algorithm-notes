#include <bits/stdc++.h>
#define int long long
using namespace std;

struct node
{
    int l,r;
}a[1000005];

bool cmp(node x,node y)
{
    if(x.r!=y.r) return x.r<y.r;
    return x.l<y.l;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i].l>>a[i].r;
    sort(a+1,a+n+1,cmp);

    int last=-1,ans=0;
    for(int i=1;i<=n;i++)
    {
        if(a[i].l>=last)
        {
            ans++;
            last=a[i].r;
        }
    }

    cout<<ans<<'\n';
    return 0;
}
