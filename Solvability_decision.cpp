#include <iostream>
using namespace std;

const int N = 4;
int puzzle[N][N];

bool is_solvability(string s) {
    int disorder_num = 0;
    int blank_position;
    for (int i = 0; i < N * N; ++i) {
        for (int j = i + 1; j < N * N; ++j) {
            if (s[i] == '0') {
                blank_position = i;
            } else if (s[j] == '0') {
                blank_position = j;
            } else if (s[i] > s[j]) {
                ++disorder_num;
            }
        }
    }
    if ((disorder_num + (blank_position / 4)) % 2 == 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    int cas;
    cin >> cas;

    for (int i = 0; i < cas; ++i) {
        string s;
        cin >> s;
        if (is_solvability(s)) {
            cout << "YES"
                 << "\n"[i == cas - 1];
        } else {
            cout << "NO"
                 << "\n"[i == cas - 1];
        }
    }
    return 0;
}