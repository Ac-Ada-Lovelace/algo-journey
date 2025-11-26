// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=838&page=show_problem&problem=447
// UVa506 System Dependencies
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    map<string, vector<string>> dep_map;
    map<string, vector<string>> rev_dep_map;
    map<string, int> installed_map; // -1 removed, 0 installed as dep, 1 installed by user
    map<string, int> dep_by_count;
    map<string, vector<string>> dep_by_map;
    vector<string> install_order;

    string line;
    while (getline(cin, line)) {
        cout << line << endl;
        if (line == "END") {
            break;
        }
        stringstream ss(line);
        string cmd;
        ss >> cmd;
        if (cmd == "DEPEND") {
            string software;
            ss >> software;
            vector<string> deps;
            string dep;
            while (ss >> dep) {
                deps.push_back(dep);
            }

            dep_map[software] = deps;
            for (auto d : deps) {
                rev_dep_map[d].push_back(software);
            }
        }
        if (cmd == "INSTALL") {
            string software;
            ss >> software;
            if (installed_map.find(software) != installed_map.end() &&
                installed_map[software] >= 0) {
                cout << software << " is already installed.\n";
                continue;
            } else {
                vector<string> deps = dep_map[software];
                for (auto dep : deps) {
                    if (installed_map.find(dep) == installed_map.end() ||
                        installed_map[dep] == -1) {
                        cout << "Installing " << dep << "\n";
                        installed_map[dep] = 0;
                        install_order.push_back(dep);
                        dep_by_count[dep] += 1;
                        dep_by_map[dep].push_back(software);
                    }
                }
                cout << "Installing " << software << "\n";
            }
        }
        if (cmd == "REMOVE") {
            string software;
            ss >> software;
            if (installed_map.find(software) == installed_map.end() ||
                installed_map[software] == -1) {
                cout << software << " is not installed.\n";
                continue;
            } else if (dep_by_count[software] > 0) {
                cout << software << " is still needed.\n";
                continue;
            } else {
                cout << "Removing " << software << "\n";
                installed_map[software] = -1;
                // check dependencies
                vector<string> deps = dep_map[software];
                for (auto dep : deps) {
                    dep_by_count[dep] -= 1;
                    auto& dep_by_list = dep_by_map[dep];
                    dep_by_list.erase(remove(dep_by_list.begin(), dep_by_list.end(), software),
                                      dep_by_list.end());
                    if (dep_by_count[dep] == 0 && installed_map[dep] == 0) {
                        cout << "Removing " << dep << "\n";
                        installed_map[dep] = -1;
                    }
                }
            }
        }
        map<string, int> visited;
        if (cmd == "LIST") {
            for (auto s : install_order) {
                if (installed_map[s] >= 0 && visited.find(s) == visited.end()) {
                    cout << s << "\n";
                    visited[s] = 1;
                }
            }
        }
    }
}
