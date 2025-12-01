// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=108&page=show_problem&problem=76
// UVa140 Bandwidth
#include <bits/stdc++.h>
using namespace std;

vector<string> siplit_by(string str, char delim) {
    vector<string> res;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delim)) {
        res.push_back(token);
    }
    return res;
}

pair<string, vector<string>> parse_token(string token) {
    auto pos = token.find(':');
    string node = token.substr(0, pos);
    vector<string> neighbors;
    if (pos != string::npos) {
        string neigh_str = token.substr(pos + 1);
        for (char c : neigh_str) {
            if (isupper(c)) {
                neighbors.push_back(string(1, c));
            }
        }
    }
    return {node, neighbors};
}

int calc_bandwidth(const map<string, vector<string>>& graph,
                   const vector<string>& order) {
    map<string, int> pos;
    for (int i = 0; i < order.size(); i++) {
        pos[order[i]] = i;
    }

    int bandwidth = 0;
    for (const auto& [node, neighbors] : graph) {
        for (const auto& neighbor : neighbors) {
            bandwidth = max(bandwidth, abs(pos[node] - pos[neighbor]));
        }
    }
    return bandwidth;
}

void disp(const vector<string>& order, int bandwidth) {
    for (const auto& node : order) {
        cout << node << ' ';
    }
    cout << "-> ";
    cout << bandwidth << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line)) {
        if (line == "#") {
            break;
        }
        vector<string> nodes;
        for (auto ch : line) {
            if (isupper(ch)) {
                nodes.push_back(string(1, ch));
            }
        }
        sort(nodes.begin(), nodes.end());
        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

        auto ts = siplit_by(line, ';');

        map<string, vector<string>> graph;

        for (auto t : ts) {
            auto [node, neighbors] = parse_token(t);
            graph[node] = neighbors;
        }

        sort(nodes.begin(), nodes.end());
        int min_bandwidth = INT_MAX;
        vector<string> best_order = nodes;
        do {
            auto cur_band = calc_bandwidth(graph, nodes);
            if (cur_band < min_bandwidth) {
                min_bandwidth = cur_band;
                best_order = nodes;
            }
            if (cur_band == min_bandwidth &&
                lexicographical_compare(nodes.begin(), nodes.end(),
                                        best_order.begin(), best_order.end())) {
                best_order = nodes;
            }

        } while (next_permutation(nodes.begin(), nodes.end()));

        disp(best_order, min_bandwidth);
    }
}
