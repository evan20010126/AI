#include <bits/stdc++.h>
using namespace std;

const vector<pair<int, int>> directions = {{-1, 0}, {-1, 1}, {0, 1},  {1, 1},
                                           {1, 0},  {1, -1}, {0, -1}, {-1, -1}};
const int N = 6;
char board[N][N];

void init(string s) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) board[i][j] = s[i * N + j];
}

bool is_inner(pair<int, int> now) {
    if (now.first < 0 || now.first > 5 || now.second < 0 || now.second > 5) return false;
    else return true;
}

int countFlipPieces(int next_player, string key, int direction_num) {
    int flip_num = 0;
    int key_row = key[0] - 'A', key_col = key[1] - 'a';
    // X is dark (player1)
    // O is light (player2)

    char same_color = (next_player == 1) ? 'X' : 'O';
    char diff_color = (next_player == 1) ? 'O' : 'X';

    pair<int, int> now{key_row, key_col};
    while (true) {
        now.first += directions[direction_num].first;
        now.second += directions[direction_num].second;

        if (!is_inner(now)) {
            return 0;
        } else if (board[now.first][now.second] == same_color) {
            return flip_num;
        } else if (board[now.first][now.second] == diff_color) {
            ++flip_num;
        } else {
            return 0;
        }
    }
}

void flipPieces(int next_player, string key) {
    const int key_row = key[0] - 'A', key_col = key[1] - 'a';
    char same_color = (next_player == 1) ? 'X' : 'O';

    board[key_row][key_col] = same_color;

    for (int direction_num = 0; direction_num < 8; ++direction_num) {
        int num = countFlipPieces(next_player, key, direction_num);
        int check_row = key_row + directions[direction_num].first;
        int check_col = key_col + directions[direction_num].second;

        for (int j = 0; j < num; ++j) {
            board[check_row][check_col] = same_color;
            check_row = check_row + directions[direction_num].first;
            check_col = check_col + directions[direction_num].second;
        }
    }
}

string board_to_string() {
    string out = "";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) { out += board[i][j]; }
    }
    return out;
}

int main() {
    int cas;
    string s;
    int next_player;
    string key;

    cin >> cas;
    for (int i = 0; i < cas; ++i) {
        cin >> s >> next_player >> key;
        init(s);
        flipPieces(next_player, key);
        cout << board_to_string() << "\n"[i == cas - 1];
    }

    return 0;
}