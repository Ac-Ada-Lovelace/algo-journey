#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<pair<int, int>> faces(6);
    while (true) {
        for (int i = 0; i < 6; ++i) {
            int a, b;
            if (!(cin >> a >> b))
                return 0;
            if (a > b)
                swap(a, b);
            faces[i] = {a, b};
        }

        sort(faces.begin(), faces.end());

        bool ok = true;
        for (int i = 0; i < 6; i += 2) {
            if (faces[i] != faces[i + 1]) {
                ok = false;
                break;
            }
        }

        if (ok) {
            if (!(faces[0].first == faces[2].first && faces[0].second == faces[4].first &&
                  faces[2].second == faces[4].second)) {
                ok = false;
            }
        }

        cout << (ok ? "POSSIBLE\n" : "IMPOSSIBLE\n");
    }
    return 0;
}
