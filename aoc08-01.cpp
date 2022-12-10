#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int main() {
    freopen("08.in", "r", stdin);
    freopen("08.out", "w", stdout);

    string s;
    vector<string> a;
    while (cin>>s) a.push_back(s);
    int n = a.size(), m = a[0].size();
    int ans = 0;
    for (int i = 1; i < n - 1; i ++)
        for (int j = 1; j < m - 1; j ++) {
            int val = 1;
            for (int k = 0; k < 4; k ++) {
                int x = i, y = j;
                while (1) {
                    x += dx[k], y += dy[k];
                    if (x == 0 || x == n - 1 || y == 0 || y == m - 1) break;
                    if (a[x][y] >= a[i][j]) break;
                }
                int see = abs(i - x) + abs(j - y);
                val *= see;
            }
            ans = max(ans, val);
        }
    cout<<ans<<endl;
    return 0;
}
