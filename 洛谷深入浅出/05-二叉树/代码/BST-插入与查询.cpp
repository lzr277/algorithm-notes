#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=100005;
int lc[N],rc[N],value[N],cnt[N],tot,root;
void insert(int &u,int x)
{
    if(u==0)
    {
        u=++tot;
        value[u]=x;
        cnt[u]=1;
        return;
    }
    if(x==value[u]) cnt[u]++;
    else if(x<value[u]) insert(lc[u],x);
    else insert(rc[u],x);
}
bool find(int u,int x)
{
    while(u)
    {
        if(x==value[u]) return true;
        if(x<value[u]) u=lc[u];
        else u=rc[u];
    }
    return false;
}
void inorder(int u)
{
    if(!u) return;
    inorder(lc[u]);
    for(int i=1;i<=cnt[u];i++) cout<<value[u]<<' ';
    inorder(rc[u]);
}
signed main()
{
    // 教学接口：q次操作，1 x插入，2 x查询，3输出中序。
    int q;
    cin>>q;
    while(q--)
    {
        int op,x;
        cin>>op;
        if(op==1)
        {
            cin>>x;
            insert(root,x);
        }
        else if(op==2)
        {
            cin>>x;
            cout<<find(root,x)<<'\n';
        }
        else
        {
            inorder(root);
            cout<<'\n';
        }
    }
    return 0;
}
