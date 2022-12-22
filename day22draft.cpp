#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int n, m;
vector<string> a;
vector<int> u, d, l, r;
string mov;

void init_boundary() {
    u.resize(m, 100000);
    d.resize(m, -100000);
    l.resize(n, 100000);
    r.resize(n, -100000);
    for (int i = 0; i < n; i ++)
        for (int j = 0; j < m; j ++)
            if (a[i][j] != ' ') {
                u[j] = min(u[j], i);
                d[j] = max(d[j], i);
                l[i] = min(l[i], j);
                r[i] = max(r[i], j);
            }
}

void process() {
    int dir = 0, step = 0;
    int cur_x = 0, cur_y = l[0];
    mov += '$';
    
    for (int i = 0; i < mov.size(); i ++) {
        cout<<i<<endl;
        if (mov[i] >= '0' && mov[i] <= '9') {
            step = step * 10 + mov[i] - 48;
            continue;
        }
        
        while (step --) {
            int x = cur_x + dx[dir];
            int y = cur_y + dy[dir];
            if (x > d[y]) x = u[y];
            if (x < u[y]) x = d[y];
            if (y > r[x]) y = l[x];
            if (y < l[x]) y = r[x];
            if (a[x][y] == '.') {
                cur_x = x;
                cur_y = y;
            }
        }
        
        if (mov[i] == 'L') dir = (dir + 3) % 4;
        if (mov[i] == 'R') dir = (dir + 1) % 4;
    }
    
    cout << (cur_x + 1) * 1000 + (cur_y + 1) * 4 + dir << endl;
}

int main() {
    freopen("22.in", "r", stdin);
    freopen("22.out", "w", stdout);
    
    string line;
    while (getline(cin, line)) {
        if (line.size() == 0) break;
        a.push_back(line);
        m = max(m, (int) line.size());
    }
    n = a.size();
    for (int i = 0; i < n; i ++)
        for (int j = a[i].size(); j < m; j ++)
            a[i] += ' ';
    
    cin >> mov;
    
    init_boundary();
    
    process();
    return 0;
}
