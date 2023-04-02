#include <bits/stdc++.h>
using namespace std;

const int N = 4;

vector<pair<int, int>> direction{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
vector<string> direction_name{"up", "down", "left", "right"};

void successor_function(string s) {
    char puzzle[N][N];
    int blank_row, blank_col;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; j++) {
            if (s[i * 4 + j] == '0') {
                blank_row = i;
                blank_col = j;
            }
            puzzle[i][j] = s[i * 4 + j];
        }
    }

    int count = 0;
    int d_count = 0;

    string buffer[4] = {"", "", "", ""};
    for (auto d : direction) {
        if ((blank_row + d.first >= 0 && blank_row + d.first < N) &&
            (blank_col + d.second >= 0 && blank_col + d.second < N)) {
            count++;

            string tmp = "";
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (i == blank_row + d.first && j == blank_col + d.second) {
                        tmp += puzzle[blank_row][blank_col];
                    } else if (i == blank_row && j == blank_col) {
                        tmp += puzzle[blank_row + d.first][blank_col + d.second];
                    } else {
                        tmp += puzzle[i][j];
                    }
                }
            }
            buffer[d_count] = tmp;
        }
        d_count++;
    }

    cout << count << endl;
    for (int i = 0; i < 4; ++i) {
        if (buffer[i] != "") {
            cout << "move 0 to " << direction_name[i] << "\n" << buffer[i] << "\n"[i == 3];
        }
    }
}

int main() {
    int cas;
    cin >> cas;

    for (int i = 0; i < cas; ++i) {
        /* code */
        string s;
        cin >> s;
        successor_function(s);
        if (i != cas - 1) { cout << "\n"; }
    }

    return 0;
}