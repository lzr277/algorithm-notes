#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
    int n;
    cin>>n;
    vector<int>f(n+1,0);
    for(int i=1;i<=n;++i)
    {
        f[i]=1;// 只保留当前数，立即停止
        for(int k=1;k<=i/2;++k)
            f[i]+=f[k];
    }
    cout<<f[n]<<'\n';
    return 0;
}
