#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm> 

using namespace std;

int main() {
    freopen("05.in", "r", stdin);
    freopen("05.out", "w", stdout);
    vector<string> s;
    s.push_back("TPZCSLQN");
    s.push_back("LPTVHCG");
    s.push_back("DCZF");
    s.push_back("GWTDLMVC");
    s.push_back("PWC");
    s.push_back("PFJDCTSZ");
    s.push_back("VWGBD");
    s.push_back("NJSQHW");
    s.push_back("RCQFSLV");

    string tmp;
    int a, b, c;
    while (cin>>tmp>>c>>tmp>>a>>tmp>>b) {
        --a, --b;
        string ts = s[a].substr(s[a].size() - c);
        s[a].resize(s[a].size() - c);
        s[b] += ts;
    }
    string ans;
    for (int i = 0; i < s.size(); i ++) ans += *s[i].rbegin();
    cout<<ans<<endl;
    return 0;
}