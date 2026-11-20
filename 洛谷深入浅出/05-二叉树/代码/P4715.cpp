#include <bits/stdc++.h>
#define int long long
using namespace std;

int strength[130],winner[260];
signed main()
{
    int n;
    cin>>n;
    int m=1LL<<n;
    for(int i=1;i<=m;i++)
    {
        cin>>strength[i];
        winner[m+i-1]=i;
    }
    for(int u=m-1;u>=1;u--)
    {
        int a=winner[u*2],b=winner[u*2+1];
        winner[u]=strength[a]>strength[b]?a:b;
    }
    int a=winner[2],b=winner[3];
    cout<<(strength[a]<strength[b]?a:b)<<'\n';
    return 0;
}
