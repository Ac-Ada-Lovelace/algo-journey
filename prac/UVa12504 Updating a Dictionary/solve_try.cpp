#include <bits/stdc++.h>
using namespace std;

map<string, string> parse_line(const string& line) {
    map<string, string> result;
    if (line == "{}") {
        return result;
    }
    string k, v;
    int status = 0;
    string nl = line;
    nl[nl.size() - 1] = ',';

    for (auto c : nl.substr(1)) {
        if (c == ':') {
            status = 1;
            continue;

        } else if (c == ',') {
            status = 0;
            result[k] = v;
            k.clear();
            v.clear();
            continue;
        }
        switch (status) {
            case 0:
                k.push_back(c);
                break;
            case 1:
                v.push_back(c);
                break;
        }
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int cases;
    cin >> cases;
    while (cases--) {
        string first_line;
        string second_line;
        cin >> first_line >> second_line;
        map<string, string> dict1 = parse_line(first_line);
        map<string, string> dict2 = parse_line(second_line);

        vector<string> added_keys;
        vector<string> removed_keys;
        vector<string> changed_keys;
        for (const auto& kv : dict2) {
            const auto& k = kv.first;
            const auto& v = kv.second;
            if (dict1.count(k) == 0) {
                added_keys.push_back(k);
            } else if (dict1[k] != v) {
                changed_keys.push_back(k);
            }
            dict1.erase(k);
        }
        for (const auto& kv : dict1) {
            removed_keys.push_back(kv.first);
        }

        if (added_keys.empty() && removed_keys.empty() && changed_keys.empty()) {
            cout << "No changes\n";
        } else {
            if (!added_keys.empty()) {
                cout << "+";
                for (size_t i = 0; i < added_keys.size(); i++) {
                    if (i) {
                        cout << ",";
                    }
                    cout << added_keys[i];
                }
                cout << "\n";
            }
            if (!removed_keys.empty()) {
                cout << "-";
                for (size_t i = 0; i < removed_keys.size(); i++) {
                    if (i) {
                        cout << ",";
                    }
                    cout << removed_keys[i];
                }
                cout << "\n";
            }
            if (!changed_keys.empty()) {
                cout << "*";
                for (size_t i = 0; i < changed_keys.size(); i++) {
                    if (i) {
                        cout << ",";
                    }
                    cout << changed_keys[i];
                }
                cout << "\n";
            }

        }
        cout << endl;
    }
}
