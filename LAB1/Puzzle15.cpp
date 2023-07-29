#include <bits/stdc++.h>
using namespace std;

const int N = 4;
vector<pair<int, int>> direction{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
vector<string> direction_name{"up", "down", "left", "right"};

struct node {
    string state;
    string action;
    int g;
    int h;
    unsigned number;
    node* parent;
    node(string state, string action, int g, int h, unsigned number, node* parent)
        : state(state), action(action), g(g), h(h), number(number), parent(parent){};
    node(){};
};

struct compare {
    bool operator()(node a, node b) {
        if (a.g + a.h > b.g + b.h) {
            return true;
        } else if (a.g + a.h < b.g + b.h) {
            return false;
        } else {
            if (a.number > b.number) return true;
            else return false;
        }
    }
};

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

vector<pair<string, string>> successor_function(string s) {
    vector<pair<string, string>> ans_vec;

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
            ans_vec.push_back({direction_name[d_count], tmp});
            // buffer[d_count] = tmp;
        }
        d_count++;
    }

    // cout << count << endl;
    // for (int i = 0; i < 4; ++i) {
    //     if (buffer[i] != "") {
    //         cout << "move 0 to " << direction_name[i] << "\n" << buffer[i] << "\n"[i == 3];
    //     }
    // }
    return ans_vec;
}

/* global variable */
priority_queue<node, std::vector<node>, compare> heap;

int main() {
    string s;
    cin >> s;

    if (!is_solvability(s)) {
        cout << "No solution!!";
    } else if (s == "0123456789ABCDEF") {
        cout << "It is the goal state.";
    } else {
        node finish_node;
        bool is_complete = false;

        int number = 0;
        node mynode(s, "", 0, manhattan_distance(s), number++, NULL);
        heap.push(mynode);
        int n = 0;
        while (!heap.empty()) {
            node mynode1 = heap.top();
            // if (n != 0) { cout << (mynode1.parent)->state << " " << mynode1.state << endl; }
            // n++;
            heap.pop();
            if (mynode1.state == "0123456789ABCDEF") {
                finish_node = mynode1;
                is_complete = true;
                break;
            }

            vector<pair<string, string>> posible_step = successor_function(mynode1.state);

            for (auto step : posible_step) {
                node tmp(step.second, step.first, mynode1.g + 1, manhattan_distance(step.second),
                         number++, &mynode1);
                cout << (tmp.parent)->state << " " << tmp.state << endl;
                heap.push(tmp);
            }
        }

        if (!is_complete) {
            cout << "No solution!!";
        } else {
            vector<string> action_buffer;

            while (finish_node.action != "") {
                action_buffer.push_back(finish_node.action);
                finish_node = *(finish_node.parent);
            }

            for (int i = action_buffer.size() - 1; i >= 0; --i)
                cout << "move 0 to " << action_buffer[i] << endl;
        }
    }
    return 0;
}