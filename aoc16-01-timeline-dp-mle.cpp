#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

const int N = 26 * 26;

int G[N][N];
int value[N];

inline int id(const char* valve) {
    return (*valve - 'A') * 26 + *(valve + 1) - 'A';
}

void floyd() {
    for (int k = 0; k < N; k ++)
        for (int i = 0 ; i < N; i ++)
            for (int j = 0; j < N; j ++)
                if (G[i][k] + G[k][j] < G[i][j])
                    G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
}

int d[N][N];
int V[N];
vector<int> next_nodes[18];
int n = 0;

void compress_nodes() {
    for (int i = 0; i < N; i ++)
        for (int j = 0; j < N; j ++)
            d[i][j] = 10000;

    map<int, int> hash;
    n = 0;
    for (int i = 0; i < N; i ++)
        if (value[i] != 0 || i == 0) {
            hash[i] = n ++;
            V[hash[i]] = value[i];
        }
    
    for (int i = 0; i < N; i ++)
        for (int j = 0; j < N; j ++)
            if ((i == 0 || value[i] != 0) && (j == 0 || value[j] != 0) && i != j && G[i][j] <= 26) {
                next_nodes[hash[j]].push_back(hash[i]);
                d[hash[i]][hash[j]] = G[i][j];
            }
    for (int i = 0; i < n; i ++)
        for (int j = 0; j < n; j ++)
            for (int k = 0; k < n; k ++)
                if (d[i][k] + d[k][j] == d[i][j]) {
                    for (int pos = 0; pos < next_nodes[j].size(); pos ++)
                        if (next_nodes[j][pos] == i) {
                            swap(next_nodes[j][pos], next_nodes[j][next_nodes[j].size() - 1]);
                            next_nodes[j].pop_back();
                            break;
                        }
                    break;
                }
}

short f[27][16][27][16][1 << 16];
int ans = 0;

inline bool update(vector<int> &state, int val) {
    ans = max(ans, val);
    if (f[state[0]][state[1]][state[2]][state[3]][state[4]] < val) {
        f[state[0]][state[1]][state[2]][state[3]][state[4]] = val;
        return true;
    }
    return false;
}

void tryMove(int turn, int t, int j, int k, queue<vector<int>> &q, vector<int> oldState, int oldVal) {
    if ((1 << j) & k == 0 && t > 0) {
        auto newState = oldState;
        newState[turn] = t - 1;
        newState[4] = k | (1 << j);
        if (update(newState, oldVal + (t - 1) * V[j])) q.push(newState);
    }
    for (int nxt : next_nodes[j]) {
        int dist = d[nxt][j];
        if (dist + t > 26) continue;
        auto newState = oldState;
        newState[turn] = t - dist;
        newState[turn + 1] = nxt;
        if (update(newState, oldVal)) q.push(newState);
    }
}

void dp() {
    for (int t1 = 0; t1 <= 26; t1 ++)
    for (int t2 = 0; t2 <= 26; t2 ++)
        for (int i = 0; i < n; i ++)
        for (int j = 0; j < n; j ++)
            for (int k = 0; k < 1 << n; k ++)
                f[t1][i][t2][j][k] = -1e4;
    f[26][26][0][0][0] = 0;

    queue<vector<int>> q;
    q.push({26, 26, 0, 0, 0});
    while (!q.empty()) {
        auto state = q.front();
        q.pop();

        int t1 = state[0], i = state[1], t2 = state[2], j = state[3], k = state[4];
        int currVal = f[t1][i][t2][j][k];
        tryMove(0, t1, i, k, q, state, currVal);
        tryMove(1, t2, j, k, q, state, currVal);
    }
}

void input() {
    char fmt[] = "Valve %s has flow rate=%d;";
    char valve[4], _[100];
    int rate;
    for (int i = 0; i < N; i ++)
        for (int j = 0; j < N; j ++)
            G[i][j] = 10000;
    while (~scanf(fmt, valve, &rate)) {
        scanf("%s%s%s%s", _, _, _, _);
        int u = id(valve);
        value[u] = rate;
        while (true) {
            scanf("%s", valve);
            G[u][id(valve)] = 1;
            if (valve[2] != ',') break;
        }
        scanf("\n");
    }
}

int main() {
    freopen("16.in", "r", stdin);
    freopen("16.out", "w", stdout);

    input();

    floyd();

    compress_nodes();

    dp();

    cout<<ans<<endl;

    return 0;
}