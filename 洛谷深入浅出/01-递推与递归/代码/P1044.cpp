#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
    int n;
    cin>>n;
    int c[19]{};
    c[0]=1;
    for(int i=1;i<=n;++i)
        for(int k=0;k<i;++k)
            c[i]+=c[k]*c[i-1-k];
    cout<<c[n]<<'\n';
    return 0;
}
