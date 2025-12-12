// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=844&page=show_problem&problem=4483
// UVa1608 Non-boring sequences - Optimized
#include <bits/stdc++.h>
using namespace std;

vector<int> seq;
vector<int> prevOccur;  // prevOccur[i] = 上一次出现 seq[i] 的位置
vector<int> nextOccur;  // nextOccur[i] = 下一次出现 seq[i] 的位置

void preprocess(int n) {
    prevOccur.assign(n, -1);
    nextOccur.assign(n, n);

    unordered_map<int, int> lastPos;

    // 计算 prevOccur
    for (int i = 0; i < n; i++) {
        if (lastPos.count(seq[i])) {
            prevOccur[i] = lastPos[seq[i]];
        }
        lastPos[seq[i]] = i;
    }

    // 计算 nextOccur
    lastPos.clear();
    for (int i = n - 1; i >= 0; i--) {
        if (lastPos.count(seq[i])) {
            nextOccur[i] = lastPos[seq[i]];
        }
        lastPos[seq[i]] = i;
    }
}

// 检查 seq[pos] 在 [L, R] 中是否唯一
bool isUnique(int pos, int L, int R) {
    return prevOccur[pos] < L && nextOccur[pos] > R;
}

// 在 [L, R] 中找一个唯一元素的位置
// 优化：从两端向中间搜索
int findUnique(int L, int R) {
    for (int i = 0; i <= R - L; i++) {
        // 先检查左边
        if (L + i <= R && isUnique(L + i, L, R)) {
            return L + i;
        }
        // 再检查右边
        if (R - i >= L && isUnique(R - i, L, R)) {
            return R - i;
        }
    }
    return -1;
}

bool check(int L, int R) {
    if (L >= R) return true;

    int mid = findUnique(L, R);
    if (mid == -1) return false;

    return check(L, mid - 1) && check(mid + 1, R);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        seq.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> seq[i];
        }

        preprocess(n);

        if (check(0, n - 1)) {
            cout << "non-boring\n";
        } else {
            cout << "boring\n";
        }
    }

    return 0;
}
