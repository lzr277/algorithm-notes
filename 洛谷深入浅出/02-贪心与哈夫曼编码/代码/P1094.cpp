#include <bits/stdc++.h>
#define int long long
using namespace std;

int a[30005];
signed main()
{
    int w,n;
    cin>>w>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    int l=1,r=n,ans=0;
    while(l<=r)
    {
        if(l<r&&a[l]+a[r]<=w) l++;
        r--;
        ans++;
    }
    cout<<ans<<'\n';
    return 0;
}
