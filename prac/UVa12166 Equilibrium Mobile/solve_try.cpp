// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=839&page=show_problem&problem=3318
// UVa12166 Equilibrium Mobile
#include <bits/stdc++.h>
using namespace std;
pair<long long, long long> mostFrequent(const vector<long long>& nums) {
    unordered_map<long long, long long> freq;
    for (long long x : nums)
        ++freq[x];

    long long mode = 0, best = -1;
    for (auto [val, cnt] : freq) {
        if (cnt > best || (cnt == best && val < mode)) { // 并列时取更小的值
            best = cnt;
            mode = val;
        }
    }
    return {mode, best}; // {众数, 次数}
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    cin.ignore();
    while (T--) {
        string line;
        getline(cin, line);
        vector<long long> weights;
        int depth = 0;
        for (int i = 0; i < line.size(); ++i) {
            if (line[i] == '[') {
                depth++;
            } else if (line[i] == ']') {
                depth--;
            } else if (isdigit(line[i]) || line[i] == '-') {
                int j = i;
                while (j < line.size() && (isdigit(line[j]) || line[j] == '-'))
                    j++;
                long long weight = stoll(line.substr(i, j - i));
                weights.push_back(weight * (1LL << depth));
                i = j - 1;
            }
        }

        auto [mode, count] = mostFrequent(weights);
        cout << weights.size() - count << '\n';
    }
}
