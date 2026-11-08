#include <bits/stdc++.h>
#define int long long
using namespace std;

// 教学输入：n，然后 n 个正整数频次，1<=n<=1000。
// 输出：最小 WPL，然后按原编号输出编码；不是未确认原题的提交格式。
int w[2005],ls[2005],rs[2005];
string code[1005];
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;

void dfs(int u,string s)
{
    if(ls[u]==0&&rs[u]==0)
    {
        code[u]=s;
        return;
    }
    dfs(ls[u],s+'0');
    dfs(rs[u],s+'1');
}

signed main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>w[i];
        q.push({w[i],i});
    }

    int tot=n,ans=0;
    while(q.size()>1)
    {
        int a=q.top().second;
        q.pop();
        int b=q.top().second;
        q.pop();

        tot++;
        ls[tot]=a;
        rs[tot]=b;
        w[tot]=w[a]+w[b];
        ans+=w[tot];
        q.push({w[tot],tot});
    }

    dfs(q.top().second,"");
    cout<<ans<<'\n';
    for(int i=1;i<=n;i++)
    {
        if(n==1) cout<<"(empty)\n";
        else cout<<code[i]<<'\n';
    }
    return 0;
}
