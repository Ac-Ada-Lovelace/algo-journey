#include <bits/stdc++.h>
using namespace std;

void parse_token(string token, int& value, string path) {
    auto pos1 = token.find('(');
    auto pos2 = token.find(',');
    auto pos3 = token.find(')');

    value = stoi(token.substr(pos1 + 1, pos2 - pos1 - 1));
    path = token.substr(pos2 + 1, pos3 - pos2 - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    map<string, int> nodes;
    string token;
    int max_depth = 0;
    while (cin >> token) {
        if (token == "()") {
    

            max_depth = 0;
            nodes.clear();
        }

        int value = 0;
        string path;

        parse_token(token, value, path);
        nodes[path] = value;
        max_depth = max(max_depth, (int)path.length());
    }
}
