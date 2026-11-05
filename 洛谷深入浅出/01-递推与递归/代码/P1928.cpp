#include <iostream>
#include <string>
#include <cctype>
using namespace std;
string s;
size_t pos=0;
string decode() {
    string result;
    while(pos<s.size()) {
        char ch=s[pos++];
        if(ch==']') return result;
        if(ch=='[') {
            int count=0;
            while(pos<s.size() && isdigit(static_cast<unsigned char>(s[pos])))
                count=count*10+(s[pos++]-'0');
            string inner=decode();
            for(int i=0;i<count;++i) result+=inner;
        } else result+=ch;
    }
    return result;
}
int main() {
    cin>>s;
    cout<<decode()<<'\n';
}
