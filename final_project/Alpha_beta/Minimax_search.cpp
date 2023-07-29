#include <bits/stdc++.h>
#include <stdio.h>
#include <unistd.h>
#include <chrono>
#include <iostream>
using namespace std;

const vector<pair<int, int>> directions = {{-1, 0}, {-1, 1}, {0, 1},  {1, 1},
                                           {1, 0},  {1, -1}, {0, -1}, {-1, -1}};
const int N = 6;
int first_player;

struct package {
    string prior_step;
    int score;
    pair<int, int> alpha_beta;

    package() : prior_step(""), score(0), alpha_beta({INT_MIN, INT_MAX}){};

    package(package tmp, pair<int, int> alpha_beta)
        : prior_step(tmp.prior_step), score(tmp.score), alpha_beta(alpha_beta){};

    package(string prior_step, int score, pair<int, int> alpha_beta)
        : prior_step(prior_step), score(score), alpha_beta(alpha_beta){};
};

void init(char board[N][N], string s) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) board[i][j] = s[i * N + j];
}

bool is_inner(pair<int, int> now) {
    if (now.first < 0 || now.first > 5 || now.second < 0 || now.second > 5) return false;
    else return true;
}

int countFlipPieces(char board[N][N], int next_player, string key, int direction_num) {
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

bool is_Valid(char board[N][N], int next_player, string key) {
    int sum = 0;
    for (int direction_num = 0; direction_num < 8; ++direction_num) {
        sum += countFlipPieces(board, next_player, key, direction_num);
    }

    return (sum != 0) ? true : false;
}

void flipPieces(char board[N][N], int next_player, string key) {
    const int key_row = key[0] - 'A', key_col = key[1] - 'a';
    char same_color = (next_player == 1) ? 'X' : 'O';

    board[key_row][key_col] = same_color;

    for (int direction_num = 0; direction_num < 8; ++direction_num) {
        int num = countFlipPieces(board, next_player, key, direction_num);
        int check_row = key_row + directions[direction_num].first;
        int check_col = key_col + directions[direction_num].second;

        for (int j = 0; j < num; ++j) {
            board[check_row][check_col] = same_color;
            check_row = check_row + directions[direction_num].first;
            check_col = check_col + directions[direction_num].second;
        }
    }
}

string board_to_string(char board[N][N]) {
    string out = "";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) { out += board[i][j]; }
    }
    return out;
}

int countColorPieces(char board[N][N], int player_color) {
    char same_color = (player_color == 1) ? 'X' : 'O';

    int count = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[i][j] == same_color) ++count;
        }
    }
    return count;
}

void copy_board(char new_board[N][N], char board[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) { new_board[i][j] = board[i][j]; }
    }
}

package Minimax_search(char board[N][N],
                       int player_color,
                       int depth,
                       bool pick_max,
                       pair<int, int> alpha_beta) {
    player_color = (player_color == 3) ? 1 : player_color;

    if (depth == 0) {
        /* heuristicScore */
        int ans;
        if (first_player == 2) {
            ans = countColorPieces(board, 2) - countColorPieces(board, 1);
        } else {
            ans = countColorPieces(board, 1) - countColorPieces(board, 2);
        };
        return package("", ans, alpha_beta);
    } else {
        // pair<string, int> best;
        package best;
        pair<int, int> tmp_alpha_beta = alpha_beta;

        bool is_first = true;
        bool empty = true;

        for (char i = 'A'; i < 'G'; ++i) {
            for (char j = 'a'; j < 'g'; ++j) {
                char key[3] = {i, j, '\0'};
                if (board[i - 'A'][j - 'a'] != '+' || !is_Valid(board, player_color, key)) continue;

                empty = false;

                char new_board[N][N];
                copy_board(new_board, board);
                flipPieces(new_board, player_color, key);

                if (is_first) {
                    best = Minimax_search(new_board, player_color + 1, depth - 1, !pick_max,
                                          tmp_alpha_beta);
                    best.prior_step = key;
                    is_first = false;

                    if (pick_max) {
                        if (best.score > tmp_alpha_beta.first) tmp_alpha_beta.first = best.score;
                    } else {
                        if (best.score < tmp_alpha_beta.second) tmp_alpha_beta.second = best.score;
                    }
                    // 當有 pruning 則之前算的 tmp_alpha_beta 作廢
                    if (tmp_alpha_beta.first >= tmp_alpha_beta.second) {
                        return package(best, alpha_beta);
                    }

                    // if (depth == 4) { cout << best.first << " " << best.second << endl; }
                } else {
                    package tmp = Minimax_search(new_board, player_color + 1, depth - 1, !pick_max,
                                                 tmp_alpha_beta);
                    tmp.prior_step = key;

                    // if (depth == 4) { cout << tmp.first << " " << tmp.second << endl; }

                    if (pick_max) {
                        // MAX-term

                        if (tmp.score > best.score) best = tmp;  // 沒找到更大的不會換

                        if (tmp.score > tmp_alpha_beta.first) tmp_alpha_beta.first = tmp.score;

                    } else {
                        // MIN-term
                        if (tmp.score < best.score) best = tmp;

                        if (tmp.score < tmp_alpha_beta.second) tmp_alpha_beta.second = tmp.score;
                    }
                    // 當有 pruning 則之前算的 tmp_alpha_beta 作廢
                    if (tmp_alpha_beta.first >= tmp_alpha_beta.second) {
                        return package(best, alpha_beta);
                    }
                }
            }
        }

        if (empty) {
            best = Minimax_search(board, player_color + 1, depth - 1, !pick_max, alpha_beta);
        }

        /* no ever pruning */
        if (pick_max) {
            // MAX-term
            best.alpha_beta.second = tmp_alpha_beta.first;
        } else {
            // MIN-term to upper
            best.alpha_beta.first = tmp_alpha_beta.second;
        }
        /* -- */

        return best;
    }
}

int main() {
    int cas;
    string s;
    // int player_color;
    int depth;

    cin >> cas;
    for (int i = 0; i < cas; ++i) {
        cin >> s >> first_player >> depth;

        auto start = std::chrono::high_resolution_clock::now();

        char board[N][N];
        init(board, s);
        std::cout << Minimax_search(board, first_player, depth, true, {INT_MIN, INT_MAX}).prior_step
                  << "\n"[i == cas - 1];
        auto finish = std::chrono::high_resolution_clock::now();
        printf("Elapsed time in milliseconds: %ld ms\n",
               std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count());
    }

    return 0;
}