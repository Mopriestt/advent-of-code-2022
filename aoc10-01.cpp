#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    freopen("10.in", "r", stdin);
    freopen("10.out", "w", stdout);
    string s;
    vector<int> a;
    
    while (cin>>s) {
        a.push_back(0);
        if (s[0] == 'a') {
            int x = 0;
            cin>>x;
            a.push_back(x);
        }
    }

    char draw[240];

    int cpu = 1;
    for (int i = 0; i < a.size(); i ++) {
        draw[i] = abs(i % 40 - cpu) > 1 ? '.' : '#';
        cpu += a[i];
    }
    for (int i = 0; i < 6; i ++) {
        for (int j = 0; j < 40; j ++)
            cout<<draw[i * 40 + j];
        cout<<endl;
    }
    return 0;
}