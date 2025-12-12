#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

const double EPS = 1e-9;

int n, L;
int a[100005];
double prefix[100005];

// 检查是否存在长度>=L的子序列，其平均值>=mid
// 同时记录符合条件的最优区间
bool check(double mid, int& best_start, int& best_end) {
    // 构造新数组: b[i] = a[i] - mid
    // 计算前缀和
    prefix[0] = 0;
    for (int i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] + (a[i] - mid);
    }

    double max_sum = -1e18;
    int result_start = -1, result_end = -1;

    // 对于每个结束位置j，找最小的prefix[i] (i <= j-L)
    double min_prefix = 0;
    int min_pos = 0;

    for (int j = L; j <= n; j++) {
        // 更新最小前缀和
        if (prefix[j - L] < min_prefix) {
            min_prefix = prefix[j - L];
            min_pos = j - L;
        }

        double sum = prefix[j] - min_prefix;
        int length = j - min_pos;

        // 如果找到更大的和，或者和相同但长度更短，或者长度相同但起始位置更小
        if (sum > max_sum + EPS ||
            (fabs(sum - max_sum) < EPS &&
             length < result_end - result_start + 1) ||
            (fabs(sum - max_sum) < EPS &&
             length == result_end - result_start + 1 &&
             min_pos + 1 < result_start)) {
            max_sum = sum;
            result_start = min_pos + 1;
            result_end = j;
        }
    }

    if (max_sum > -EPS) {
        best_start = result_start;
        best_end = result_end;
        return true;
    }
    return false;
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

        for (int i = 1; i <= n; i++) {
            a[i] = s[i - 1] - '0';
        }

        // 二分答案
        double low = 0, high = 1;
        int ans_start = 1, ans_end = L;

        // 进行足够多次二分以达到精度要求
        for (int iter = 0; iter < 100; iter++) {
            double mid = (low + high) / 2;
            int start, end;

            if (check(mid, start, end)) {
                low = mid;
                ans_start = start;
                ans_end = end;
            } else {
                high = mid;
            }
        }

        cout << ans_start << " " << ans_end << endl;
    }

    return 0;
}
