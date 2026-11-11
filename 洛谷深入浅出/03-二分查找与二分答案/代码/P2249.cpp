#include <bits/stdc++.h>
#define int long long
using namespace std;

int a[1000005];
int find_first(int n,int x)
{
    int l=1,r=n+1;
    while(l<r)
    {
        int mid=l+(r-l)/2;
        if(a[mid]>=x) r=mid;
        else l=mid+1;
    }
    if(l<=n&&a[l]==x) return l;
    return -1;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++)
    {
        int x;
        cin>>x;
        cout<<find_first(n,x)<<(i==m?'\n':' ');
    }
    return 0;
}
