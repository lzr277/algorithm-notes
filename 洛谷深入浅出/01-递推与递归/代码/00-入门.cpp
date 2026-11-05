#include <bits/stdc++.h>
#define int long long
using namespace std;
int memo[91]{};
bool seen[91]{};
int fact(int n)
{
    if(n==0) return 1;
    return n*fact(n-1);
}
int fib(int n)
{
    if(n<=1) return n;
    return fib(n-1)+fib(n-2);
}
int fibMemo(int n)
{
    if(n<=1) return n;
    if(seen[n]) return memo[n];
    memo[n]=fibMemo(n-1)+fibMemo(n-2);
    seen[n]=true;
    return memo[n];
}
int fibLoop(int n)
{
    if(n<=1) return n;
    int a=0,b=1;
    for(int i=2;i<=n;++i)
    {
        int next=a+b;
        a=b;
        b=next;
    }
    return b;
}
signed main()
{
    int n;
    cin>>n;// 为同时运行所有演示，本程序限定 0..20
    if(n<0||n>20)
    {
        cerr<<"请输入 0..20\n";
        return 1;
    }
    int sum=0;
    for(int i=1;i<=n;++i)
        sum+=i;
    cout<<sum<<'\n'
         <<fact(n)<<'\n'
         <<fib(n)<<'\n'
         <<fibMemo(n)<<'\n'
         <<fibLoop(n)<<'\n';
    return 0;
}
