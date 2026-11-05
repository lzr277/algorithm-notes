#include <bits/stdc++.h>
#define int long long
using namespace std;

int dp[22][22][22];

int fc(int a,int b,int c)
{
    if(a<1||b<1||c<1) return 1;

    if(a>20||b>20||c>20)
        return fc(20,20,20);

    if(dp[a][b][c]!=-1)
        return dp[a][b][c];

    if(a<b&&b<c)
    {
        dp[a][b][c]=fc(a,b-1,c-1)
                   +fc(a,b,c-1)
                   -fc(a,b-1,c);
    }
    else
    {
        dp[a][b][c]=fc(a-1,b,c)
                   +fc(a-1,b-1,c)
                   +fc(a-1,b,c-1)
                   -fc(a-1,b-1,c-1);
    }

    return dp[a][b][c];
}

signed main()
{
    memset(dp,-1,sizeof dp);

    int a,b,c;

    while(cin>>a>>b>>c)
    {
        if(a==-1&&b==-1&&c==-1)
            break;

        cout<<"w("<<a<<", "<<b<<", "<<c<<") = "<<fc(a,b,c)<<'\n';
    }

    return 0;
}
