#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    freopen("08.in", "r", stdin);
    freopen("08.out", "w", stdout);

    string s;
    vector<string> a, l, r, u, d;
    while (cin>>s) a.push_back(s);
    l = r = u = d = a;
    int n = a.size(), m = a[0].size();
    for (int i = 0; i < n; i ++)
        for (int j = 0; j < m; j ++) {
            if (i > 0) u[i][j] = max(u[i - 1][j], u[i][j]);
            if (j > 0) l[i][j] = max(l[i][j - 1], l[i][j]);
            int x = n - i - 1, y = m - j - 1;
            if (x < n - 1) d[x][y] = max(d[x + 1][y], d[x][y]);
            if (y < m - 1) r[x][y] = max(r[x][y + 1], r[x][y]);
        }
    int ans = n * 2 + m * 2 - 4;
    for (int i = 1; i < n - 1; i ++)
        for (int j = 1; j < m - 1; j ++) {
            int x = a[i][j];
            if (u[i - 1][j] < x || d[i + 1][j] < x || l[i][j - 1] < x || r[i][j + 1] < x)
                ++ans;
        }
    cout<<ans<<endl;
    return 0;
}
