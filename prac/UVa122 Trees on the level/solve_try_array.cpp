#include <bits/stdc++.h>
using namespace std;

void parse_token(const string& token, int& value, int& path) {
    auto pos1 = token.find('(');
    auto pos2 = token.find(',');
    auto pos3 = token.find(')');

    value = stoi(token.substr(pos1 + 1, pos2 - pos1 - 1));
    string path_str = token.substr(pos2 + 1, pos3 - pos2 - 1);

    path = 1;
    if (path_str == "") {
        return;
    }
    for (char c : path_str) {
        if (c == 'L') {
            path = path * 2;
        } else if (c == 'R') {
            path = path * 2 + 1;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unordered_map<int, int> tree;
    vector<int> nodes;
    bool invalid = false;

    string token;
    while (cin >> token) {
        if (token == "()") {
            if (!invalid) {
                if (!tree.count(1)) {
                    invalid = true;
                } else {
                    for (int n : nodes) {
                        if (n == 1)
                            continue;
                        if (!tree.count(n / 2)) {
                            invalid = true;
                            break;
                        }
                    }
                }
            }

            if (invalid) {
                cout << "not complete" << "\n";
            } else {
                vector<pair<int, int>> ordered(tree.begin(), tree.end());
                sort(ordered.begin(), ordered.end(),
                     [](const pair<int, int>& lhs, const pair<int, int>& rhs) {
                         return lhs.first < rhs.first;
                     });
                for (size_t i = 0; i < ordered.size(); ++i) {
                    if (i)
                        cout << ' ';
                    cout << ordered[i].second;
                }
                cout << "\n";
            }

            tree.clear();
            nodes.clear();
            invalid = false;
            continue;
        }

        int value = 0;
        int path = 0;
        parse_token(token, value, path);
        if (tree.count(path)) {
            invalid = true;
            continue;
        }
        tree[path] = value;
        nodes.push_back(path);
    }
}
