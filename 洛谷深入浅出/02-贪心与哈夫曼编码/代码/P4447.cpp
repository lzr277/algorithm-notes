#include <bits/stdc++.h>
#define int long long
using namespace std;

int a[100005];
map<int,priority_queue<int,vector<int>,greater<int>>> q;
signed main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)
    {
        int x=a[i],len=0;
        if(!q[x-1].empty())
        {
            len=q[x-1].top();
            q[x-1].pop();
        }
        q[x].push(len+1);
    }
    int ans=n;
    for(auto &item:q)
    {
        if(!item.second.empty()) ans=min(ans,item.second.top());
    }
    cout<<ans<<'\n';
    return 0;
}
