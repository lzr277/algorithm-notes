#include <bits/stdc++.h>
#define int long long
using namespace std;

string s;
int pos=0;

string dfs()
{
    string ans;

    while(pos<(int)s.size()&&s[pos]!=']')
    {
        if(s[pos]>='A'&&s[pos]<='Z')
        {
            ans+=s[pos];
            pos++;
        }
        else
        {
            int num=0;

            // 跳过左括号
            pos++;

            // 读取完整的重复次数
            while(pos<(int)s.size()&&s[pos]>='0'&&s[pos]<='9')
            {
                num=num*10+s[pos]-'0';
                pos++;
            }

            // 子层遇到右括号就停下，将内部结果返回
            string t=dfs();

            // 父层跳过子层停留的右括号
            pos++;

            for(int i=0;i<num;i++)
                ans+=t;
        }
    }

    return ans;
}

signed main()
{
    cin>>s;
    cout<<dfs()<<'\n';

    return 0;
}
