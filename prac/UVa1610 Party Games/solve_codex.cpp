// UVa1610 Party Games - Codex solution
#include <bits/stdc++.h>
using namespace std;

string buildSeparator(const string& L, const string& R) {
    // If L is a strict prefix of R, L itself is the shortest valid separator.
    if (R.rfind(L, 0) == 0 && L.size() < R.size())
        return L;

    int len = min(L.size(), R.size());
    string ans;

    for (int i = 0; i < len; ++i) {
        if (L[i] == R[i]) {
            ans.push_back(L[i]);
            continue;
        }

        char bumped = static_cast<char>(L[i] + 1);
        if (bumped < R[i]) {
            ans.push_back(bumped);
            return ans;
        }

        // bumped == R[i]
        ans.push_back(L[i]);
        for (int j = i + 1; j < (int)L.size(); ++j) {
            if (L[j] != 'Z') {
                ans.push_back(static_cast<char>(L[j] + 1));
                return ans;
            }
            ans.push_back('Z');
        }
        // Could not bump anything after position i; L itself works.
        return ans;
    }

    // All shared prefix identical; if L is shorter, it is the minimal valid
    // answer.
    return L;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    while (cin >> n && n) {
        vector<string> names(n);
        for (auto& s : names)
            cin >> s;
        sort(names.begin(), names.end());

        const string& L = names[n / 2 - 1];
        const string& R = names[n / 2];

        cout << buildSeparator(L, R) << '\n';
    }
    return 0;
}
