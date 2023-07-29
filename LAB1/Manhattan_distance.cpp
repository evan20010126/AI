#include <bits/stdc++.h>
using namespace std;

const int N = 4;

int manhattan_distance(string s) {
    int row, col;
    int target_row, target_col;
    int sum = 0;
    int value;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '0') { continue; }

        row = i / 4;
        col = i % 4;

        value = ('0' <= s[i] && '9' >= s[i]) ? s[i] - 48 : s[i] - 'A' + 10;

        target_row = value / 4;
        target_col = value % 4;

        sum += abs(row - target_row) + abs(col - target_col);
    }
    return sum;
}

int main() {
    int cas;
    cin >> cas;

    for (int i = 0; i < cas; ++i) {
        string s;
        cin >> s;
        cout << manhattan_distance(s) << "\n"[i == cas - 1];
    }
    return 0;
}