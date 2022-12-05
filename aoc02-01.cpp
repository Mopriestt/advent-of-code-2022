#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

int main() {
    freopen("02.in", "r", stdin);
    freopen("02.out", "w", stdout);
    string a, b;
    int ans = 0;
    while (cin>>a>>b) {
        int i = a[0] - 'A';
        int j = b[0] - 'X';

        ans += j + 1 + (j - i + 4) % 3 * 3;
    }

    cout<<ans<<endl;
    return 0;
}