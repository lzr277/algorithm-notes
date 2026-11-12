#include <bits/stdc++.h>
#define int long long
using namespace std;

// 模板来源：yxc/AcWing，本地原始资料/第三章.txt；数组队列和距离记录适配。
const int N=100005,M=100005;
int h[N],e[M],ne[M],idx,d[N],q[N];
void add(int a,int b)
{
    e[idx]=b;
    ne[idx]=h[a];
    h[a]=idx++;
}
signed main()
{
    int n,m;
    cin>>n>>m;
    memset(h,-1,sizeof h);
    memset(d,-1,sizeof d);
    for(int i=1;i<=m;i++)
    {
        int a,b;
        cin>>a>>b;
        add(a,b);
    }
    int hh=0,tt=0;
    q[0]=1;
    d[1]=0;
    while(hh<=tt)
    {
        int t=q[hh++];
        for(int i=h[t];i!=-1;i=ne[i])
        {
            int j=e[i];
            if(d[j]!=-1) continue;
            d[j]=d[t]+1;
            q[++tt]=j;
        }
    }
    cout<<d[n]<<'\n';
    return 0;
}
