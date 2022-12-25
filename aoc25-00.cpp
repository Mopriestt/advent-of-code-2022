#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

string toSNAFU(long long n) {
    vector<int> five;
    while (n) {
        five.push_back(n % 5);
        n /= 5;
    }
    for (int i = 0; i < five.size(); i ++) {
        if (five[i] > 2) {
            if (i < five.size() - 1) five[i + 1] ++;
            else five.push_back(1);
            five[i] -= 5;
        }
    }
    string ret;
    for (int i = five.size() - 1; i >= 0; i --) {
        if (five[i] == 0) ret += '0';
        if (five[i] == 1) ret += '1';
        if (five[i] == 2) ret += '2';
        if (five[i] == -1) ret += '-';
        if (five[i] == -2) ret += '=';
    }
    return ret;
}

int main() {
    freopen("25.in", "r", stdin);
    freopen("25.out", "w", stdout);

    long long ans = 0;
    string s;
    while (cin >> s) {
        long long k = 0;

        for (auto c : s) {
            k *= 5;
            if (c == '1') k += 1;
            if (c == '2') k += 2;
            if (c == '-') k -= 1;
            if (c == '=') k -= 2;
        }
        ans += k;
    }
    
    cout << toSNAFU(ans) << endl;

    return 0;
}
