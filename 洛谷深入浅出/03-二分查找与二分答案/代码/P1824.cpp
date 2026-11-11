#include <bits/stdc++.h>
#define int long long
using namespace std;

int a[100005],n,m;
bool check(int d)
{
    int last=a[1],cnt=1;
    for(int i=2;i<=n;i++)
    {
        if(a[i]-last>=d)
        {
            last=a[i];
            cnt++;
        }
    }
    return cnt>=m;
}
signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    int l=0,r=a[n]-a[1],ans=0;
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
