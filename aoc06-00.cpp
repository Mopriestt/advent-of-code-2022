#include <iostream>
#include <string>
#include <set>

using namespace std;

int main() {
    freopen("06.in", "r", stdin);
    freopen("06.out", "w", stdout);
    string s;
    cin>>s;
    for (int i = 3; i < s.size(); i ++) {
        set<char> st(s.begin() + i - 3, s.begin() + i + 1);
        if (st.size() == 4) {
            cout<<i + 1<<endl;
            break;
        }
    }
    return 0;
}