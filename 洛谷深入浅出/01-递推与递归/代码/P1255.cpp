#include <bits/stdc++.h>
#define int long long
using namespace std;

// f[i][j] 是第 i 级走法数从低到高的第 j 位。
// f[i][0] 存十进制位数，5000 阶的答案不超过 1100 位。
int f[5005][1105];

signed main()
{
    int n;
    cin>>n;
    f[0][0]=f[1][0]=1;
    f[0][1]=f[1][1]=1;

    for(int i=2;i<=n;i++)
    {
        int len=max(f[i-1][0],f[i-2][0]);
        int carry=0;

        for(int j=1;j<=len;j++)
        {
            int x=f[i-1][j]+f[i-2][j]+carry;
            f[i][j]=x%10;
            carry=x/10;
        }

        if(carry) f[i][++len]=carry;
        f[i][0]=len;
    }

    for(int j=f[n][0];j>=1;j--)
        cout<<f[n][j];
    cout<<'\n';

    return 0;
}
