#include <bits/stdc++.h>
#define int long long
using namespace std;

string in,pre;
void solve(int il,int ir,int pl,int pr)
{
    if(il>ir) return;
    char root=pre[pl];
    int k=il;
    while(in[k]!=root) k++;
    int left=k-il;
    solve(il,k-1,pl+1,pl+left);
    solve(k+1,ir,pl+left+1,pr);
    cout<<root;
}
signed main()
{
    cin>>in>>pre;
    solve(0,(int)in.size()-1,0,(int)pre.size()-1);
    cout<<'\n';
    return 0;
}
