#include <bits/stdc++.h>
#define int long long
using namespace std;
string s;
int pos=0;
string decode()
{
    string result;
    while(pos<(int)s.size())
    {
        char ch=s[pos++];
        if(ch==']') return result;
        if(ch=='[')
        {
            int count=0;
            while(pos<(int)s.size()&&s[pos]>='0'&&s[pos]<='9')
                count=count*10+(s[pos++]-'0');
            string inner=decode();
            for(int i=0;i<count;++i)
                result+=inner;
        }
        else result+=ch;
    }
    return result;
}
signed main()
{
    cin>>s;
    cout<<decode()<<'\n';
    return 0;
}
