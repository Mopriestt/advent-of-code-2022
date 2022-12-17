#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

int a[10005];
int shapes[5][4];
string wind;

inline int get_row(vector<int> pos) {
    int res = 0;
    for (int x : pos) res |= 1 << x;
    return res;
}
void init_shape() {
    memset(shapes, 0, sizeof(shapes));
    shapes[0][0] = get_row({3, 4, 5, 6});

    shapes[1][0] = shapes[1][2] = get_row({4});
    shapes[1][1] = get_row({3, 4, 5});

    shapes[2][0] = get_row({3, 4, 5});
    shapes[2][1] = shapes[2][2] = get_row({5});

    shapes[3][0] = shapes[3][1] = shapes[3][2] = shapes[3][3] = get_row({3});

    shapes[4][0] = shapes[4][1] = get_row({3, 4});
}

void init_tower() {
    memset(a, 0, sizeof(a));
    for (int i = 1; i <= 10000; i ++)
        a[i] |= 1, a[i] |= 1 << 8;
    a[0] = (1 << 9) - 1;
}


int cur_h = 0, cur_w;

inline bool intersect(vector<int> &shape, int h) {
    for (int i = 0; i < 4; i ++)
        if (shape[i] & a[h + i]) return true;
    return false;
}

inline void blow(vector<int> &shape, int w, int h) {
    cur_w ++;
    auto moved = shape;
    for (int i = 0; i < 4; i ++)
        if (w == -1) moved[i] >>= 1;
        else moved[i] <<= 1;
    if (!intersect(moved, h)) shape = moved;
}

void debugPrint() {
    for (int i = 10; i >= 0; i --) {
        for (int j = 0; j <= 8; j ++) {
            if (j == 0 || j == 8) {
                cout<<'|';
                continue;
            }
            if (a[i] & (1 << j)) cout<<'#';
            else cout<<'.';
        }
        cout<<endl;
    }
    cout<<endl;
}

void drop(int k) {
    int h = cur_h + 4;
    vector<int> shape = {shapes[k][0], shapes[k][1], shapes[k][2], shapes[k][3]};

    for (;;) {
        int w = wind[cur_w % wind.size()] == '<' ? -1 : 1;
        blow(shape, w, h);
        if (intersect(shape, h - 1)) {
            for (int j = 0; j < 4; j ++)
                a[h + j] |= shape[j];
            break;
        }
        -- h;
    }
    while (a[cur_h + 1] ^ 1 ^ (1 << 8)) ++ cur_h;
}

int main() {
    freopen("17.in", "r", stdin);
    freopen("17.out", "w", stdout);

    init_shape();
    
    init_tower();

    cin>>wind;

    for (int turn = 0; turn < 2022; turn ++) {
        drop(turn % 5);
    }

    cout<<cur_h<<endl;

    return 0;
}