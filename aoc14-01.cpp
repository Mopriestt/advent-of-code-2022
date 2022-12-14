#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

bool a[1500][201];
const int abyss = 200;

bool pour() {
    if (a[500][0]) return false;
    int x = 500, y = 0;
    while (y < abyss) {
        // o
        //ooo
        if (a[x - 1][y + 1] && a[x][y + 1] && a[x + 1][y + 1]) return a[x][y] = true;

        // o
        // ⎕
        if (!a[x][y + 1]) {
            ++ y;
            continue;
        }

        // o    o
        // oo   o
        if (!a[x - 1][y + 1] && a[x][y + 1]) {
            -- x; ++ y;
            continue;
        }

        // o   o
        //oo  #o
        ++ x; ++ y;
    }
    return false;
}

void draw(int &prev_x, int &prev_y, int &x, int &y) {
    a[x][y] = true;
    if (prev_x == -1) {
        prev_x = x, prev_y = y;
        return;
    }
    if (prev_x != x) {
        int dx = x - prev_x;
        int d = dx / abs(dx);
        for (int i = 0; i < abs(dx); i ++) {
            a[prev_x][prev_y] = true;
            prev_x += d;
        }
    }
    if (prev_y != y) {
        int dy = y - prev_y;
        int d = dy / abs(dy);
        for (int i = 0; i < abs(dy); i ++) {
            a[prev_x][prev_y] = true;
            prev_y += d;
        }
    }
    prev_x = x;
    prev_y = y;
}

vector<string> split(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

void debugPrint(int l, int r, int u, int d) {
    for (int i = u; i <= d; i ++) {
        for (int j = l; j <= r; j ++) cout<<(a[j][i] ? 'o' : '.');
        cout<<endl;
    }
    cout<<endl;
}

int main() {
    freopen("14.in", "r", stdin);
    freopen("14.out", "w", stdout);
    memset(a, 0, sizeof(a));
    string line;
    int maxY = 0;
    while (getline(cin, line)) {
        auto points = split(line, "->");
        int x, y, prev_x = -1, prev_y = -1;
        for (string s : points) {
            sscanf(s.c_str(), "%d,%d", &x, &y);
            maxY = max(maxY, y);
            draw(prev_x, prev_y, x, y);
        }
    }

    for (int i = 0; i < 1500; i ++) a[i][maxY + 2] = true;

    int ans = 0;
    while (pour()) ++ ans;
    cout<<ans<<endl;
    return 0;
}