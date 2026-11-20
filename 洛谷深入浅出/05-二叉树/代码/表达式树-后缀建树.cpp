#include <bits/stdc++.h>
#define int long long
using namespace std;

int lc[1005],rc[1005],st[1005],tot,top;
char value[1005];
void pre(int u)
{
    if(!u) return;
    cout<<value[u];
    pre(lc[u]);
    pre(rc[u]);
}
void in(int u)
{
    if(!u) return;
    if(lc[u]) cout<<'(';
    in(lc[u]);
    cout<<value[u];
    in(rc[u]);
    if(lc[u]) cout<<')';
}
void post(int u)
{
    if(!u) return;
    post(lc[u]);
    post(rc[u]);
    cout<<value[u];
}
signed main()
{
    // 教学接口：合法后缀表达式；单字符字母/数字，二元运算+-*/，无空格。
    string s;
    cin>>s;
    for(char ch:s)
    {
        int u=++tot;
        value[u]=ch;
        if(ch=='+'||ch=='-'||ch=='*'||ch=='/')
        {
            rc[u]=st[top--];
            lc[u]=st[top--];
        }
        st[++top]=u;
    }
    int root=st[top];
    pre(root);
    cout<<'\n';
    in(root);
    cout<<'\n';
    post(root);
    cout<<'\n';
    return 0;
}
