#include <bits/stdc++.h>
#define int long long
using namespace std;

struct node
{
    int a,b;
}a[1005];
int num[5005],tmp[5005],best[5005];
int len=1,blen=1;
bool cmp(node x,node y)
{
    return x.a*x.b<y.a*y.b;
}
void mul(int x)
{
    int carry=0;
    for(int i=1;i<=len;i++)
    {
        int v=num[i]*x+carry;
        num[i]=v%10;
        carry=v/10;
    }
    while(carry)
    {
        num[++len]=carry%10;
        carry/=10;
    }
}
void check(int x)
{
    int rem=0;
    for(int i=len;i>=1;i--)
    {
        rem=rem*10+num[i];
        tmp[i]=rem/x;
        rem%=x;
    }
    int tlen=len;
    while(tlen>1&&tmp[tlen]==0) tlen--;
    bool larger=tlen>blen;
    if(tlen==blen)
    {
        for(int i=tlen;i>=1;i--)
        {
            if(tmp[i]!=best[i])
            {
                larger=tmp[i]>best[i];
                break;
            }
        }
    }
    if(larger)
    {
        blen=tlen;
        for(int i=1;i<=blen;i++) best[i]=tmp[i];
    }
}
signed main()
{
    int n,king,right;
    cin>>n>>king>>right;
    for(int i=1;i<=n;i++) cin>>a[i].a>>a[i].b;
    sort(a+1,a+n+1,cmp);
    num[1]=1;
    mul(king);
    for(int i=1;i<=n;i++)
    {
        check(a[i].b);
        mul(a[i].a);
    }
    for(int i=blen;i>=1;i--) cout<<best[i];
    cout<<'\n';
    return 0;
}
