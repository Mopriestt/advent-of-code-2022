#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

inline bool connect(vector<int> &a, vector<int> &b) {
    int zero = 0, one = 0;
    for (int i = 0; i < 3; i ++) {
        if (abs(a[i] - b[i]) == 0) ++ zero;
        if (abs(a[i] - b[i]) == 1) ++ one;
    }
    return zero == 2 && one == 1;
}

vector< vector<int> > a, inner_air;
int n;
int max_x, max_y, max_z;
bool is_cube[25][25][25];

// Align cube minimum x, y, z to 1.
void move_cubes() {
    int min_x = 100, min_y = 100, min_z = 100;
    max_x = max_y = max_z = 0;
    memset(is_cube, 0, sizeof(is_cube));
    for (auto cube : a) {
        min_x = min(min_x, cube[0]);
        min_y = min(min_y, cube[1]);
        min_z = min(min_z, cube[2]);
    }

    for (int i = 0; i < a.size(); i ++) {
        max_x = max(max_x, a[i][0] -= min_x - 1);
        max_y = max(max_y, a[i][1] -= min_y - 1);
        max_z = max(max_z, a[i][2] -= min_z - 1);
        is_cube[a[i][0]][a[i][1]][a[i][2]] = true;
    }
}

const int dx[] = {1, -1, 0, 0, 0, 0};
const int dy[] = {0, 0, 1, -1, 0, 0};
const int dz[] = {0, 0, 0, 0, 1, -1};

inline bool outside(int x, int y, int z) {
    return x < 0 || y < 0 || z < 0 || x > max_x || y > max_y || z > max_z;
}

vector<vector<vector<int>>> groups;
bool vis[25][25][25];
void dfs(int x, int y, int z, vector<vector<int>> &group) {
    if (outside(x, y, z)) return;
    if (vis[x][y][z] || is_cube[x][y][z]) return;
    vis[x][y][z] = true;
    group.push_back({x, y, z});
    for (int k = 0; k < 6; k ++) {
        int X = dx[k] + x, Y = dy[k] + y, Z = dz[k] + z;
        dfs(X, Y, Z, group);
    }
}

void calc_trapped_sides() {
    memset(vis, 0, sizeof(vis));
    for (int x = 0; x < max_x; x ++)
        for (int y = 0; y < max_y; y ++)
            for (int z = 0; z < max_z; z ++) {
                if (is_cube[x][y][z] || vis[x][y][z]) continue;
                vector<vector<int>> group;
                dfs(x, y, z, group);
                groups.push_back(group);
            }
    for (auto group : groups) {
        bool is_trapped_group = true;
        for (auto air : group) {
            for (int k = 0; k < 6 && is_trapped_group; k ++)
                if (outside(air[0] + dx[k], air[1] + dy[k], air[2] + dz[k]))
                    is_trapped_group = false;
        }
        if (is_trapped_group) {
            inner_air.insert(inner_air.end(), group.begin(), group.end());
        }
    }
}

int main() {
    freopen("18.in", "r", stdin);
    freopen("18.out", "w", stdout);
    int x, y, z;
    while (~scanf("%d,%d,%d", &x, &y, &z))
        a.push_back({x, y, z});
    n = a.size();

    move_cubes();

    calc_trapped_sides();

    int ans = n * 6;
    for (int i = 0; i < n; i ++) {
        for (int j = i + 1; j < n; j ++)
            if (connect(a[i], a[j])) ans -= 2;
        for (int j = 0; j < inner_air.size(); j ++)
            if (connect(a[i], inner_air[j])) ans --;
    }
    cout << ans << endl;
    return 0;
}
