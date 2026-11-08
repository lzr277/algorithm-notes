#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    int n,last=0,ans=0;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int x;
        cin>>x;
        if(x>last) ans+=x-last;
        last=x;
    }
    cout<<ans<<'\n';
    return 0;
}
