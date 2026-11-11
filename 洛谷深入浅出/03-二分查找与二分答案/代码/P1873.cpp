#include <bits/stdc++.h>
#define int long long
using namespace std;

int a[1000005],n,m;
bool check(int h)
{
    int sum=0;
    for(int i=1;i<=n;i++)
    {
        if(a[i]>h) sum+=a[i]-h;
        if(sum>=m) return true;
    }
    return sum>=m;
}
signed main()
{
    cin>>n>>m;
    int high=0;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        high=max(high,a[i]);
    }
    int l=0,r=high,ans=-1;
    while(l<=r)
    {
        int mid=l+(r-l)/2;
        if(check(mid))
        {
            ans=mid;
            l=mid+1;
        }
        else r=mid-1;
    }
    cout<<ans<<'\n';
    return 0;
}
