#include <bits/stdc++.h>
#define int long long
using namespace std;

int a[200005];
signed main()
{
    int n,c,ans=0;
    cin>>n>>c;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)
    {
        int x=a[i]+c;
        int l=lower_bound(a+1,a+n+1,x)-a;
        int r=upper_bound(a+1,a+n+1,x)-a;
        ans+=r-l;
    }
    cout<<ans<<'\n';
    return 0;
}
