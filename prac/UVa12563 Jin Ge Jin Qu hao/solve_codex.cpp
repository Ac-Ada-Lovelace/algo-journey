// UVa12563 Jin Ge Jin Qu hao
// 0/1 背包：先在 t-1 秒内尽量放歌曲，优先歌数，其次用时，再加上固定 678
// 秒的劲歌金曲
#include <bits/stdc++.h>
using namespace std;

struct State {
    int cnt;  // 已放的歌曲数量
    int time; // 已用时间
};

bool better(const State& a, const State& b) {
    if (a.cnt != b.cnt)
        return a.cnt > b.cnt;
    return a.time > b.time;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);

    int T;
    if (!(cin >> T))
        return 0;
    const int SONG_LEN = 678; // 劲歌金曲固定时长
    for (int tc = 1; tc <= T; ++tc) {
        int n;
        int t;
        cin >> n >> t;
        vector<int> a(n);
        for (int& x : a)
            cin >> x;

        int maxTime = min(t - 1, 180 * n); // 只需考虑能装下的最大总时长
        vector<State> dp(maxTime + 1, State{-1000, 0});
        dp[0] = {0, 0};
        for (int len : a) {
            for (int tm = maxTime - len; tm >= 0; --tm) {
                if (dp[tm].cnt < 0)
                    continue; // 不可达
                State cand{dp[tm].cnt + 1, dp[tm].time + len};
                if (better(cand, dp[tm + len]))
                    dp[tm + len] = cand;
            }
        }

        State best{-1, 0};
        for (const State& s : dp) {
            if (better(s, best))
                best = s;
        }

        // 总是尽量把劲歌金曲安排在最后
        int ansCnt = best.cnt + 1;
        int ansTime = best.time + SONG_LEN;
        cout << "Case " << tc << ": " << ansCnt << " " << ansTime << "\n";
    }
    return 0;
}
