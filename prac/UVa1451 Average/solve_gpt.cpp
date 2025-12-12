
#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-7;

int n, L;
vector<int> a;

/*
 check(V)：
   判断是否存在 length >= L 的区间满足 avg >= V
   同时恢复最短、最小起点的那个区间

 返回：
   true ：存在可行区间，并在 bestL/bestR 中写入最优区间
   false：不存在
*/
bool check(double V, int &bestL, int &bestR) {
    vector<double> B(n + 1);
    vector<double> prefixMin(n + 1);
    vector<int> prefixIdx(n + 1);

    // 构造 B[i] = sum(a) - i*V
    B[0] = 0.0;
    for (int i = 1; i <= n; i++)
        B[i] = B[i - 1] + (a[i] - V);

    // 前缀最小值（严格前缀定义）
    prefixMin[0] = B[0];
    prefixIdx[0] = 0;
    for (int i = 1; i <= n; i++) {
        if (B[i] < prefixMin[i - 1]) {
            prefixMin[i] = B[i];
            prefixIdx[i] = i;
        } else {
            prefixMin[i] = prefixMin[i - 1];
            prefixIdx[i] = prefixIdx[i - 1];
        }
    }

    bool ok = false;
    int bestLen = INT_MAX;

    // 检查所有 r >= L
    for (int r = L; r <= n; r++) {
        int k = r - L;   // 最远允许的左界是 prefixMin[k]

        // 若 B[r] ≥ prefixMin[k] → 可行区间 ( prefixIdx[k]+1  ... r )
        if (B[r] >= prefixMin[k] - EPS) {
            int l = prefixIdx[k] + 1;
            int len = r - prefixIdx[k];

            if (!ok || len < bestLen || (len == bestLen && l < bestL)) {
                ok = true;
                bestLen = len;
                bestL = l;
                bestR = r;
            }
        }
    }

    return ok;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    int T;
    cin >> T;

    while (T--) {
        cin >> n >> L;
        string s;
        cin >> s;

        a.assign(n + 1, 0);
        for (int i = 1; i <= n; i++)
            a[i] = (s[i - 1] == '1');

        // 二分最大平均值
        double low = 0.0, high = 1.0;
        for (int it = 0; it < 80; it++) { // 双精度二分足够
            double mid = (low + high) / 2.0;
            int tmpL, tmpR;
            if (check(mid, tmpL, tmpR)) low = mid;
            else high = mid;
        }

        // 最终用 low 恢复真实区间
        int Lans, Rans;
        check(low, Lans, Rans);

        cout << Lans << " " << Rans << "\n";
    }

    return 0;
}

