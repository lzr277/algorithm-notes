#include <bits/stdc++.h>
#define int long long
using namespace std;

int a[305];
signed main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    int l=1,r=n,now=0,ans=0;
    bool high=true;
    while(l<=r)
    {
        int x;
        if(high) x=a[r--];
        else x=a[l++];
        ans+=(x-now)*(x-now);
        now=x;
        high=!high;
    }
    cout<<ans<<'\n';
    return 0;
}
