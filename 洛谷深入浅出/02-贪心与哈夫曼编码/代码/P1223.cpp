#include <bits/stdc++.h>
#define int long long
using namespace std;

struct node
{
    int t,id;
}a[1005];

bool cmp(node x,node y)
{
    if(x.t!=y.t) return x.t<y.t;
    return x.id<y.id;
}

signed main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].t;
        a[i].id=i;
    }
    sort(a+1,a+n+1,cmp);

    int now=0,sum=0;
    for(int i=1;i<=n;i++)
    {
        cout<<a[i].id<<(i==n?'\n':' ');
        sum+=now;
        now+=a[i].t;
    }

    cout<<fixed<<setprecision(2)<<1.0*sum/n<<'\n';
    return 0;
}
