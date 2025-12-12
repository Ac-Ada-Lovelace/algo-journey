// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=845&page=show_problem&problem=2531
// UVa11536 Smallest Sub-Array
#include <bits/stdc++.h>
using namespace std;

int _min = INT_MAX;
map<int, int> count_map = {};
int N, M, K;
vector<int> arr;

int dfs(int l, int r) {
    _min = min(_min, r - l + 1);
    if (r - l + 1 == K) {
        return 0;
    }

    if (arr[r] > K) {
        dfs(l, r - 1);
    } else {
        if (count_map[arr[l]] > 1) {
            count_map[arr[l]]--;
            dfs(l + 1, r);
            count_map[arr[l]]++;
        }
    }
    if (arr[l] > K) {
        dfs(l + 1, r);
    } else {
        if (count_map[arr[r]] > 1) {
            count_map[arr[r]]--;
            dfs(l, r - 1);
            count_map[arr[r]]++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> N >> M >> K;
        arr.resize(N);
        _min = INT_MAX;
        count_map.clear();
        arr[0] = 0;
        arr[1] = 1;
        arr[2] = 3;
        for (int i = 3; i < N; i++) {
            arr[i] = (arr[i - 1] + arr[i - 2] + arr[i - 3]) % M + 1;
        }

        for (int i = 0; i <= N; i++) {
            if (arr[i] <= K) {
                count_map[arr[i]]++;
            }
        }
        if (count_map.size() < K) {
            cout << "Case " << t << ": " << "sequence nai" << '\n';
            continue;
        }

        dfs(0, N - 1);

        cout << "Case " << t << ": " << _min << '\n';
    }
}
