#include <bits/stdc++.h>
#define int long long
using namespace std;

priority_queue<int,vector<int>,greater<int>> q;

signed main()
{
    int n,x;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        q.push(x);
    }

    int ans=0;
    while(q.size()>1)
    {
        int a=q.top();
        q.pop();
        int b=q.top();
        q.pop();

        int c=a+b;
        ans+=c;
        q.push(c);
    }

    cout<<ans<<'\n';
    return 0;
}
