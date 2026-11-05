#include <bits/stdc++.h>
#define int long long
using namespace std;

int prefixSum(int n)
{ // 0 <= n <= 1000000
    int answer=0;
    for(int i=1;i<=n;++i)
        answer+=i;
    return answer;
}

int stairsSmall(int n)
{ // 0 <= n <= 90
    vector<int>f(n+2,0);
    f[0]=f[1]=1;
    for(int i=2;i<=n;++i)
        f[i]=f[i-1]+f[i-2];
    return f[n];
}

int stairsWithBoundary(int n)
{                       // -1 <= n <= 90
    if(n<0) return 0;// 不可能到达负级数
    if(n<=1) return 1;
    int a=1,b=1;
    for(int i=2;i<=n;++i)
    {
        int next=a+b;
        a=b;
        b=next;
    }
    return b;
}

int fibonacci(int n)
{ // 0 <= n <= 92
    if(n<=1) return n;
    int a=0,b=1;
    for(int i=2;i<=n;++i)
    {
        int next=a+b;// 此时 a=F(i-2), b=F(i-1)
        a=b;
        b=next;
    }
    return b;
}

int gridWays(int n,int m,const vector<vector<bool>>&blocked)
{
    // 0 <= n,m <= 20；blocked 的大小必须是 (n+1) × (m+1)
    vector<vector<int>>dp(n+1,vector<int>(m+1,0));
    for(int x=0;x<=n;++x)
    {
        for(int y=0;y<=m;++y)
        {
            if(blocked[x][y]) continue;
            if(x==0&&y==0)
            {
                dp[x][y]=1;
                continue;
            }
            if(x>0) dp[x][y]+=dp[x-1][y];
            if(y>0) dp[x][y]+=dp[x][y-1];
        }
    }
    return dp[n][m];
}

bool validPopOrder(const vector<int>&out)
{ // 输入顺序固定为 1..n
    int n=(int)out.size(),next=1;
    stack<int>st;
    for(int wanted : out)
    {
        if(wanted<1||wanted>n) return false;
        while((st.empty()||st.top()!=wanted)&&next<=n)
            st.push(next++);
        if(st.empty()||st.top()!=wanted) return false;
        st.pop();
    }
    return true;
}

vector<int>catalanTable(int n)
{ // 0 <= n <= 35，完整整数
    vector<int>c(n+1,0);
    c[0]=1;
    for(int total=1;total<=n;++total)
    {
        for(int left=0;left<total;++left)
        {
            int right=total-1-left;
            c[total]+=c[left]*c[right];
        }
    }
    return c;
}

int factorial(int n)
{ // 0 <= n <= 20
    if(n==0) return 1;
    int smaller=factorial(n-1);
    return n*smaller;
}

int countSequencesSlow(int n)
{                  // 教学示例：1 <= n <= 20
    int answer=1;// 仅有 n 的单项数列
    for(int k=1;k<=n/2;++k)
        answer+=countSequencesSlow(k);
    return answer;
}

int sequenceMemoDfs(int n,vector<int>&memo)
{
    if(memo[n]!=-1) return memo[n];// 本题答案 >= 1，-1 可作标记
    int answer=1;
    for(int k=1;k<=n/2;++k)
        answer+=sequenceMemoDfs(k,memo);
    return memo[n]=answer;
}
int sequenceMemo(int n)
{ // 1 <= n <= 1000
    vector<int>memo(n+1,-1);
    return sequenceMemoDfs(n,memo);
}
int sequenceLoop(int n)
{ // 与上面计算相同的关系式
    vector<int>f(n+1,0);
    for(int i=1;i<=n;++i)
    {
        f[i]=1;
        for(int k=1;k<=i/2;++k)
            f[i]+=f[k];
    }
    return f[n];
}

int fibMemoDfs(int n,vector<int>&memo,vector<bool>&seen)
{
    if(n<=1) return n;
    if(seen[n]) return memo[n];
    int answer=fibMemoDfs(n-1,memo,seen)+fibMemoDfs(n-2,memo,seen);
    memo[n]=answer;
    seen[n]=true;
    return answer;
}
int fibonacciMemo(int n)
{ // 0 <= n <= 92
    vector<int>memo(n+1,0);
    vector<bool>seen(n+1,false);
    return fibMemoDfs(n,memo,seen);
}

string parseLevel(const string&s,int&pos)
{ // 约定输入语法合法
    string result;
    while(pos<(int)s.size())
    {
        char ch=s[pos++];
        if(ch==']') return result;// 消费本层右括号后返回
        if(ch!='[')
        {
            result+=ch;
            continue;
        }
        int times=0;
        while(pos<(int)s.size()&&s[pos]>='0'&&s[pos]<='9')
            times=times*10+(s[pos++]-'0');
        string inner=parseLevel(s,pos);
        for(int i=0;i<times;++i)
            result+=inner;
    }
    return result;// 最外层读到输入结束
}
string decodeText(const string&s)
{
    int pos=0;
    return parseLevel(s,pos);
}

signed main()
{
    assert(prefixSum(0)==0&&prefixSum(100)==5050);
    for(int n=0;n<=30;++n)
    {
        assert(stairsSmall(n)==stairsWithBoundary(n));
        assert(stairsSmall(n)==fibonacci(n+1));
        assert(fibonacciMemo(n)==fibonacci(n));
    }
    assert(stairsWithBoundary(-1)==0);
    assert(fibonacci(92)==7540113804746346429LL);
    assert(fibonacciMemo(92)==fibonacci(92));
    vector<vector<bool>>blocked(3,vector<bool>(3,false));
    assert(gridWays(2,2,blocked)==6);
    blocked[1][1]=true;
    assert(gridWays(2,2,blocked)==2);
    blocked[0][0]=true;
    assert(gridWays(2,2,blocked)==0);
    assert(validPopOrder({2,3,1}));
    assert(!validPopOrder({3,1,2}));
    assert(!validPopOrder({1,1,3}));
    auto c=catalanTable(35);
    assert(c[0]==1&&c[3]==5&&c[4]==14);
    assert(c[18]==477638700&&c[35]==3116285494907301262LL);
    assert(factorial(0)==1&&factorial(20)==2432902008176640000LL);
    for(int n=1;n<=20;++n)
        assert(countSequencesSlow(n)==sequenceLoop(n));
    for(int n=1;n<=1000;++n)
        assert(sequenceMemo(n)==sequenceLoop(n));
    assert(decodeText("A[2B[3C]]D")=="ABCCCBCCCD");
    assert(decodeText("[12A]")==string(12,'A'));
    assert(decodeText("[2[2[2CB]]]")=="CBCBCBCBCBCBCBCB");
    cout<<"knowledge checks passed\n";
    return 0;
}
