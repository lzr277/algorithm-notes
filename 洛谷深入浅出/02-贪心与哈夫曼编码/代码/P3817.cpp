#include <bits/stdc++.h>
#define int long long
using namespace std;

int a[100005];
signed main()
{
    int n,x,ans=0;
    cin>>n>>x;
    for(int i=1;i<=n;i++) cin>>a[i];
    if(a[1]>x)
    {
        ans=a[1]-x;
        a[1]=x;
    }
    for(int i=2;i<=n;i++)
    {
        int d=max(0LL,a[i-1]+a[i]-x);
        a[i]-=d;
        ans+=d;
    }
    cout<<ans<<'\n';
    return 0;
}
