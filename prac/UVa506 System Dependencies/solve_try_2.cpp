#include <bits/stdc++.h>
#include <sstream>
using namespace std;

map<string, vector<string>> dep_map;
map<string, vector<string>> rev_dep_map;

// 0 uninstalled
// 1 insatlled as dep
// 2 installed by user
map<string, int> installed_map;

map<string, int> dep_by_count;

list<string> install_order;

void build_deps(string sw, vector<string> deps) {
    dep_map[sw] = deps;
    installed_map[sw] = 0;
    dep_by_count[sw] = 0;
    for (auto dep : deps) {
        rev_dep_map[dep].push_back(sw);
        installed_map[dep] = 0;
        dep_by_count[dep] = 0;
    }
}
void do_install(string sw, int is_as_dep) {
    installed_map[sw] = 2 - is_as_dep;
    auto deps = dep_map[sw];
    for (auto dep : deps) {
        dep_by_count[dep] += 1;
    }
}

void do_install_as_dep(string sw) {
    do_install(sw, 1);
}
void do_install_by_user(string sw) {
    do_install(sw, 0);
}

bool all_deps_installed(string sw) {
    auto deps = dep_map[sw];
    for (auto dep : deps) {
        if (installed_map[dep] == 0) {
            return false;
        }
    }
    return true;
}
void install(string sw) {
    stack<string> stk;
    stk.push(sw);
    while (!stk.empty()) {
        if (all_deps_installed(stk.top())) {
            string curr_sw = stk.top();
            stk.pop();
            if (installed_map[curr_sw] == 0) {
                cout << "Installing " << curr_sw << "\n";
                if (curr_sw == sw) {
                    do_install_by_user(curr_sw);
                } else {
                    do_install_as_dep(curr_sw);
                }
                install_order.push_back(curr_sw);
            }
        } else {
            auto deps = dep_map[stk.top()];
            for (auto dep : deps) {
                if (installed_map[dep] == 0) {
                    stk.push(dep);
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("output.txt", "w", stdout);

    string line;
    while (getline(cin, line)) {
        // 回显
        cout << ">   " << line << endl;
        if (line == "END") {
            break;
        }

        string cmd;
        stringstream ss(line);
        ss >> cmd;
        if (cmd == "DEPEND") {}
        if (cmd == "INSTALL") {}
        if (cmd == "REMOVE") {}
        if (cmd == "LIST") {}
    }
}
