#include <bits/stdc++.h>
using namespace std;

struct node {
    string state;
    int g;
    int h;
    unsigned number;
    node(string state, int g, int h, unsigned number) : state(state), g(g), h(h), number(number){};
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

priority_queue<node, std::vector<node>, compare> heap;

int main() {
    int cas;
    string op;
    int number = 0;
    cin >> cas;
    for (int i = 0; i < cas; ++i) {
        cin >> op;
        if (i != 0) cout << "\n";

        if (op == "enqueue") {
            string state;
            int h, g;
            cin >> state >> g >> h;
            heap.push(node(state, g, h, number++));
            cout << "Insert OK!";
        } else if (op == "dequeue") {
            if (heap.empty()) {
                cout << "Queue is empty!!";
            } else {
                string state = heap.top().state;
                cout << "Got " << state;
                heap.pop();
            }
        }
    }
    return 0;
}