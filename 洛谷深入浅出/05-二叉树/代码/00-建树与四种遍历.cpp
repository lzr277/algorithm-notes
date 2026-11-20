#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=1005;
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
void preorder(int u)
{
    if(u==0) return;
    cout<<value[u]<<' ';
    preorder(lc[u]);
    preorder(rc[u]);
}
void inorder(int u)
{
    if(u==0) return;
    inorder(lc[u]);
    cout<<value[u]<<' ';
    inorder(rc[u]);
}
void postorder(int u)
{
    if(u==0) return;
    postorder(lc[u]);
    postorder(rc[u]);
    cout<<value[u]<<' ';
}
void levelorder(int root)
{
    if(root==0) return;
    int q[N],hh=0,tt=0;
    q[0]=root;
    while(hh<=tt)
    {
        int u=q[hh++];
        cout<<value[u]<<' ';
        if(lc[u]) q[++tt]=lc[u];
        if(rc[u]) q[++tt]=rc[u];
    }
}
int depth(int u)
{
    if(u==0) return 0;
    return max(depth(lc[u]),depth(rc[u]))+1;
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
    cout<<'\n'<<depth(root)<<'\n';
    return 0;
}
