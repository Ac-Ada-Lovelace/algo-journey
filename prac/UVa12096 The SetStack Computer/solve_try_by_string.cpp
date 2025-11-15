#include <bits/stdc++.h>
using namespace std;

void calc_union(stack<int>& id_stack, map<int, set<int>>& id_set_map,
                map<set<int>, int>& set_id_map) {
    auto first = id_stack.top();
    id_stack.pop();
    auto second = id_stack.top();
    id_stack.pop();

    auto first_set = id_set_map.at(first);
    auto second_set = id_set_map.at(second);
    auto union_set = set<int>();
    set_union(first_set.begin(), first_set.end(), second_set.begin(), second_set.end(),
              inserter(union_set, union_set.begin()));

    int new_id = 0;
    if (set_id_map.find(union_set) == set_id_map.end()) {
        new_id = id_set_map.size();
        set_id_map[union_set] = new_id;
        id_set_map[new_id] = union_set;

    } else {
        new_id = set_id_map[union_set];
    }
    id_stack.push(new_id);
}

void calc_intersect(stack<int>& id_stack, map<int, set<int>>& id_set_map,
                    map<set<int>, int>& set_id_map) {
    auto first = id_stack.top();
    id_stack.pop();
    auto second = id_stack.top();
    id_stack.pop();

    auto first_set = id_set_map.at(first);
    auto second_set = id_set_map.at(second);
    auto intersect_set = set<int>();
    set_intersection(first_set.begin(), first_set.end(), second_set.begin(), second_set.end(),
                     inserter(intersect_set, intersect_set.begin()));

    int new_id = 0;
    if (set_id_map.find(intersect_set) == set_id_map.end()) {
        new_id = id_set_map.size();
        set_id_map[intersect_set] = new_id;
        id_set_map[new_id] = intersect_set;

    } else {
        new_id = set_id_map[intersect_set];
    }
    id_stack.push(new_id);
}
void calc_add(stack<int>& id_stack, map<int, set<int>>& id_set_map,
              map<set<int>, int>& set_id_map) {
    auto first = id_stack.top();
    id_stack.pop();
    auto second = id_stack.top();
    id_stack.pop();

    auto first_set = id_set_map.at(first);
    auto second_set = id_set_map.at(second);
    auto add_set(second_set);

    add_set.insert(first);

    int new_id = 0;
    if (set_id_map.find(add_set) == set_id_map.end()) {
        new_id = id_set_map.size();
        set_id_map[add_set] = new_id;
        id_set_map[new_id] = add_set;

    } else {
        new_id = set_id_map[add_set];
    }
    id_stack.push(new_id);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int cases;
    cin >> cases;
    while (cases--) {
        int step;
        stack<int> id_stack;
        map<int, set<int>> id_set_map;
        map<set<int>, int> set_id_map;
        cin >> step;
        while (step--) {
            string cmd;
            cin >> cmd;
            if (cmd == "PUSH") {
                id_stack.push(0);

                if (id_set_map.find(0) == id_set_map.end()) {
                    id_set_map[0] = set<int>();
                    set_id_map[set<int>()] = 0;
                }
            } else if (cmd == "DUP") {
                id_stack.push(id_stack.top());
            } else if (cmd == "UNION") {
                calc_union(id_stack, id_set_map, set_id_map);
            } else if (cmd == "INTERSECT") {
                calc_intersect(id_stack, id_set_map, set_id_map);
            } else if (cmd == "ADD") {
                calc_add(id_stack, id_set_map, set_id_map);
            }
            auto top_id = id_stack.top();
            cout << id_set_map[top_id].size() << endl;
        }
        cout << "***" << endl;
    }
}
