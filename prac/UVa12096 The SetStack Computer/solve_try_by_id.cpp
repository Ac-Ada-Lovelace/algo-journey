#include <bits/stdc++.h>
#include <cinttypes>
using namespace std;

vector<string> get_elements(string set_string) {
    if (set_string == "{}")
        return vector<string>();
    else {
        vector<string> elements;
        auto elements_string = set_string.substr(1, set_string.size() - 2);
        int depth = 0;
        string element;
        for (auto c : elements_string) {
            if (c == '{') {
                element.push_back(c);
                depth++;
            } else if (c == '}') {
                element.push_back(c);
                depth--;
                if (depth == 0) {
                    elements.push_back(element);
                    element.clear();
                }
            }
        }
        return elements;
    }
}

int copy_stack(map<int, set<int>>& set_id_map, map<int, string>& set_string_map, int id) {
    auto elements_id = set_id_map[id];
    auto new_id = set_string_map.size();
    set_id_map[new_id] = set_id_map[id];
    set_string_map[new_id] = set_string_map[id];
    return new_id;
}
int calc_union(map<int, set<int>>& set_id_map, map<int, string>& set_string_map, int first,
               int second) {
    auto first_elements = set_id_map[first];
    auto second_elements = set_id_map[second];
    auto new_id = set_string_map.size();
    set<int> res;
    set_union(first_elements.begin(), first_elements.end(), second_elements.begin(),
              second_elements.end(), inserter(res, res.begin()));

    set_id_map[new_id] = res;
    string res_string = "{";

    for (auto i : res) {
        res_string += set_string_map[i];
    }
    res_string += "}";

    set_string_map[new_id] = res_string;
    return new_id;
}

int clac_intersection(map<int, set<int>>& set_id_map, map<int, string>& set_string_map, int first,
                      int second) {
    auto first_elements = set_id_map[first];
    auto second_elements = set_id_map[second];
    auto new_id = set_string_map.size();
    set<int> res;
    set_intersection(first_elements.begin(), first_elements.end(), second_elements.begin(),
                     second_elements.end(), inserter(res, res.begin()));

    set_id_map[new_id] = res;
    string res_string = "{";

    for (auto i : res) {
        res_string += set_string_map[i];
    }
    res_string += "}";

    set_string_map[new_id] = res_string;
    return new_id;
}

int clac_add(map<int, set<int>>& set_id_map, map<int, string>& set_string_map, int first,
             int second) {
    auto first_elements = set_id_map[first];
    auto second_elements = set_id_map[second];
    set<int> res(second_elements.begin(), second_elements.end());
    auto new_id = set_string_map.size();
    res.insert(first);
    set_id_map[new_id] = res;

    string res_string = "{";
    for (auto i : res) {
        res_string += set_string_map[i];
    }
    res_string += "}";
    set_string_map[new_id] = res_string;
    return new_id;
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int n;
    cin >> n;
    while (n--) {
        map<int, set<int>> set_id_map;
        map<int, string> set_string_map;
        stack<int> set_stack;
        int step;
        cin >> step;
        while (step--) {
            string cmd;
            cin >> cmd;
            if (cmd == "PUSH") {
                int id = set_string_map.size();
                set_id_map[id] = set<int>();
                set_string_map[id] = "{}";
                set_stack.push(id);
            }
            if (cmd == "DUP") {
                int id = set_string_map.size();
                copy_stack(set_id_map, set_string_map, id);

                set_stack.push(id);
            }
            if (cmd == "UNION") {
                auto first = set_stack.top();
                set_stack.pop();
                auto second = set_stack.top();
                set_stack.pop();
                auto new_set = calc_union(set_id_map, set_string_map, first, second);
                set_stack.push(new_set);
            }
            if (cmd == "INTERSECT") {
                auto first = set_stack.top();
                set_stack.pop();
                auto second = set_stack.top();
                set_stack.pop();
                auto new_set = clac_intersection(set_id_map, set_string_map, first, second);

                set_stack.push(new_set);
            }
            if (cmd == "ADD") {
                auto first = set_stack.top();
                set_stack.pop();
                auto second = set_stack.top();
                set_stack.pop();
                auto new_set = clac_add(set_id_map, set_string_map, first, second);

                set_stack.push(new_set);
            }
        }
    }
    helllo
}
