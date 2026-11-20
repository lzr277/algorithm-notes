#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=200005;
int lc[N],rc[N],parent[N],n;
string value[N];
int build_tree()
{
    for(int u=1;u<=n;u++)
    {
        cin>>value[u]>>lc[u]>>rc[u];
        if(lc[u]) parent[lc[u]]=u;
        if(rc[u]) parent[rc[u]]=u;
    }
    for(int u=1;u<=n;u++)
        if(parent[u]==0) return u;
    return 0;
}
void preorder(int root)
{
    if(!root) return;
    static int st[N];
    int top=0;
    st[++top]=root;
    while(top)
    {
        int u=st[top--];
        cout<<value[u]<<' ';
        if(rc[u]) st[++top]=rc[u];
        if(lc[u]) st[++top]=lc[u];
    }
}
void inorder(int root)
{
    static int st[N];
    int top=0,u=root;
    while(u||top)
    {
        while(u)
        {
            st[++top]=u;
            u=lc[u];
        }
        u=st[top--];
        cout<<value[u]<<' ';
        u=rc[u];
    }
}
void postorder(int root)
{
    static int st[N];
    int top=0,u=root,last=0;
    while(u||top)
    {
        if(u)
        {
            st[++top]=u;
            u=lc[u];
        }
        else
        {
            int v=st[top];
            if(rc[v]&&last!=rc[v]) u=rc[v];
            else
            {
                cout<<value[v]<<' ';
                last=v;
                top--;
            }
        }
    }
}
void levelorder(int root)
{
    if(!root) return;
    static int q[N];
    int hh=0,tt=0;
    q[0]=root;
    while(hh<=tt)
    {
        int u=q[hh++];
        cout<<value[u]<<' ';
        if(lc[u]) q[++tt]=lc[u];
        if(rc[u]) q[++tt]=rc[u];
    }
}
signed main()
{
    cin>>n;
    int root=build_tree();
    preorder(root);
    cout<<'\n';
    inorder(root);
    cout<<'\n';
    postorder(root);
    cout<<'\n';
    levelorder(root);
    cout<<'\n';
    return 0;
}
