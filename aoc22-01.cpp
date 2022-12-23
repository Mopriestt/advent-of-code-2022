#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int n, m, cur_x, cur_y, dir;
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

inline bool try_move(int x, int y, int direction) {
    if (a[x][y] == ' ') throw;
    if (a[x][y] != '.') return false;
    cur_x = x;
    cur_y = y;
    dir = direction;
    return true;
}

// Sadly all movements are based on manual simulation.

bool jump_face_1() {
    if (dir == 0) {
        if (cur_y != 149) throw;
        return try_move(150 - cur_x - 1, 99, 2);
    }

    if (dir == 1) {
        if (cur_x != 49) throw;
        return try_move(100 - (cur_y - 100) - 1, 99, 2);
    }
    
    if (dir == 3) {
        if (cur_x != 0) throw;
        return try_move(199, cur_y - 100, 3);
    }
    
    throw;
}

bool jump_face_2() {
    if (dir == 2) {
        if (cur_y != 50) throw;
        return try_move(100 + (49 - cur_x), 0, 0);
    }

    if (dir == 3) {
        if (cur_x != 0) throw;

        return try_move(150 + cur_y - 50, 0, 0);
    }

    throw;
}

bool jump_face_3() {
    if (dir == 0) {
        if (cur_y != 99) throw;

        return try_move(49, 100 + (cur_x - 50), 3);
    }

    if (dir == 2) {
        if (cur_y != 50) throw;

        return try_move(100, 50 - (cur_x - 50) - 1, 1);
    }

    throw;
}

bool jump_face_4() {
    if (dir == 0) {
        if (cur_y != 99) throw;

        return try_move(50 - (cur_x - 100) - 1, 149, 2);
    }

    if (dir == 1) {
        if (cur_x != 149) throw;

        return try_move(150 + cur_y - 50, 49, 2);
    }

    throw;
}

bool jump_face_5() {
    if (dir == 2) {
        if (cur_y != 0) throw;

        return try_move(149 - cur_x, 50, 0);
    }

    if (dir == 3) {
        if (cur_x != 100) throw;

        return try_move(50 + cur_y, 50, 0);
    }

    throw;
}

bool jump_face_6() {
    if (dir == 0) {
        if (cur_y != 49) throw;

        return try_move(149, 50 + cur_x - 150, 3);
    }

    if (dir == 1) {
        if (cur_x != 199) throw;
        
        return try_move(0, 100 + cur_y, 1);
    }

    if (dir == 2) {
        if (cur_y != 0) throw;

        return try_move(0, 50 + cur_x - 150, 1);
    }
    throw;
}

bool manual_teleport() {
    int x = cur_x + dx[dir];
    int y = cur_y + dy[dir];
    if (x <= d[y] && x >= u[y] && y <= r[x] && y >= l[x]) {
        if (a[x][y] != '.') return false;
        cur_x = x;
        cur_y = y;
        return true;
    }

    if (cur_x < 50) {
        if (cur_y < 100) return jump_face_2();
        return jump_face_1();
    }
    if (cur_x < 100) {
        return jump_face_3();
    }
    if (cur_x < 150) {
        if (cur_y < 50) return jump_face_5();
        return jump_face_4();
    }
    return jump_face_6();
}

void process() {
    int step = 0;
    cur_x = 0, cur_y = l[0], dir = 0;
    mov += '$';
    
    for (int i = 0; i < mov.size(); i ++) {
        if (mov[i] >= '0' && mov[i] <= '9') {
            step = step * 10 + mov[i] - 48;
            continue;
        }
        
        while (step --) if (!manual_teleport()) break;
        step = 0;
        
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
