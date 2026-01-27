// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=847&page=show_problem&problem=3466
//
// UVa1025 A Spy in the Metro
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 55;
const int MAX_T = 205;
const int INF = 1e9;

// travel_time[i]: time between station i and i+1 (1-based)
int travel_time[MAX_N];
// has_train[time][station][dir], dir 0: forward (1->N), 1: backward (N->1)
int has_train[MAX_T][MAX_N][2];
// dp[time][station]: minimal waiting time from (time, station) to reach N at
// exactly T
int dp[MAX_T][MAX_N];

int N, T;

void preprocess(const vector<int>& d, const vector<int>& e) {
    memset(has_train, 0, sizeof(has_train));

    // Trains starting from station 1 towards N
    for (int dep : d) {
        int tcur = dep;
        int station = 1;
        if (tcur <= T) {
            has_train[tcur][station][0] = 1;
        }
        for (int s = 1; s < N && tcur <= T; s++) {
            tcur += travel_time[s];
            if (tcur > T)
                break;
            ++station;
            has_train[tcur][station][0] = 1;
        }
    }

    // Trains starting from station N towards 1
    for (int dep : e) {
        int tcur = dep;
        int station = N;
        if (tcur <= T) {
            has_train[tcur][station][1] = 1;
        }
        for (int s = N - 1; s >= 1 && tcur <= T; s--) {
            tcur += travel_time[s];
            if (tcur > T)
                break;
            --station;
            has_train[tcur][station][1] = 1;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int case_no = 1;
    while (cin >> N) {
        if (N == 0)
            break;
        cin >> T;

        for (int i = 1; i < N; i++) {
            cin >> travel_time[i];
        }

        int M1;
        cin >> M1;
        vector<int> d(M1);
        for (int i = 0; i < M1; i++) {
            cin >> d[i];
        }

        int M2;
        cin >> M2;
        vector<int> e(M2);
        for (int i = 0; i < M2; i++) {
            cin >> e[i];
        }

        preprocess(d, e);

        for (int t = 0; t <= T; t++) {
            for (int s = 1; s <= N; s++) {
                dp[t][s] = INF;
            }
        }
        dp[T][N] = 0;

        for (int t = T - 1; t >= 0; t--) {
            for (int s = 1; s <= N; s++) {
                int best = dp[t + 1][s] + 1;
                if (s < N && has_train[t][s][0] && t + travel_time[s] <= T) {
                    best = min(best, dp[t + travel_time[s]][s + 1]);
                }
                if (s > 1 && has_train[t][s][1] &&
                    t + travel_time[s - 1] <= T) {
                    best = min(best, dp[t + travel_time[s - 1]][s - 1]);
                }

                // TODO: 在这里补全状态转移，比较三种选择：
                // 1) 等待一分钟：dp[t + 1][s] + 1
                // 2) 如果有正向车且不超时：dp[t + travel_time[s]][s + 1]
                // 3) 如果有反向车且不超时：dp[t + travel_time[s - 1]][s - 1]
                // 将最小值写回 dp[t][s]。
                dp[t][s] = INF; // 占位，待填写
            }
        }

        cout << "Case Number " << case_no << ": ";
        if (dp[0][1] >= INF / 2) {
            cout << "impossible\n";
        } else {
            cout << dp[0][1] << '\n';
        }
        case_no++;
    }

    return 0;
}
