#include <bits/stdc++.h>
#define int long long
using namespace std;

string pre,post;
int pos[256];
signed main()
{
    cin>>pre>>post;
    for(int i=0;i<(int)post.size();i++) pos[(int)post[i]]=i;
    int ans=1;
    for(int i=0;i+1<(int)pre.size();i++)
    {
        if(pos[(int)pre[i]]==pos[(int)pre[i+1]]+1) ans*=2;
    }
    cout<<ans<<'\n';
    return 0;
}
