
#include <bits/stdc++.h>
using namespace std;

// 四种可能的布尔函数（关于单变量 x 的函数）
// 以 (f(0), f(1)) 编码：
// 0: 常量 0  -> (0,0)
// 1: 常量 1  -> (1,1)
// 2: x       -> (0,1)
// 3: !x      -> (1,0)
struct FuncPair {
    int f0, f1;
};

const int FUNC_CNT = 4;
const int INF = 1e9;

// 把 (f(0), f(1)) 映射回 0..3 的函数编号
int encode_func(int f0, int f1) {
    if (f0 == 0 && f1 == 0) return 0; // const 0
    if (f0 == 1 && f1 == 1) return 1; // const 1
    if (f0 == 0 && f1 == 1) return 2; // x
    if (f0 == 1 && f1 == 0) return 3; // !x
    // 对于单变量布尔函数不可能出现其它情况
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);

    // 预先构造 4 个函数在 x=0,1 时的值
    FuncPair F[FUNC_CNT];
    // 0: const 0
    F[0] = {0, 0};
    // 1: const 1
    F[1] = {1, 1};
    // 2: x
    F[2] = {0, 1};
    // 3: !x
    F[3] = {1, 0};

    // 预先构造 NAND 组合表：nandRes[a][b] = 编号 g
    int nandRes[FUNC_CNT][FUNC_CNT];
    for (int a = 0; a < FUNC_CNT; ++a) {
        for (int b = 0; b < FUNC_CNT; ++b) {
            int g0 = 1 - (F[a].f0 & F[b].f0); // f(0) 时 NAND
            int g1 = 1 - (F[a].f1 & F[b].f1); // f(1) 时 NAND
            nandRes[a][b] = encode_func(g0, g1);
        }
    }

    int d;
    if (!(cin >> d)) return 0;
    while (d--) {
        int n, m;
        cin >> n >> m;
        int N = n + m;              // 总节点数：1..n 为输入，n+1..n+m 为门
        vector<int> a(m + 1), b(m + 1); // 每个 gate 的两个源（原始编号：正=gate,负=input）

        for (int j = 1; j <= m; ++j) {
            cin >> a[j] >> b[j];
        }

        // 把源映射成统一的节点编号 1..N
        auto mapSrc = [&](int s) -> int {
            if (s > 0) return n + s; // gate s -> node n+s
            else return -s;          // input -s -> node -s
        };

        vector<int> u(m + 1), v(m + 1); // 每个门的两个输入节点
        for (int j = 1; j <= m; ++j) {
            u[j] = mapSrc(a[j]);
            v[j] = mapSrc(b[j]);
        }

        // 先求“原始电路”的函数：把所有输入都接 x，
        // 分别在 x=0 和 x=1 时模拟一次。
        int root = n + m;           // 最后一个门的输出就是电路输出

        auto evalCircuit = [&](int xval) -> int {
            vector<int> val(N + 1, 0);
            // 输入节点：全等于 xval
            for (int i = 1; i <= n; ++i) {
                val[i] = xval;
            }
            // 依次处理门
            for (int j = 1; j <= m; ++j) {
                int node = n + j;
                int A = val[u[j]];
                int B = val[v[j]];
                val[node] = 1 - (A & B); // NAND
            }
            return val[root];
        };

        int out0 = evalCircuit(0);
        int out1 = evalCircuit(1);
        int targetFunc = encode_func(out0, out1); // 电路原本实现的函数类型

        // dp[node][f] = 实现此节点输出为函数 f 所需的最少 x 个数
        vector<array<int, FUNC_CNT>> dp(N + 1);
        for (int i = 0; i <= N; ++i)
            for (int f = 0; f < FUNC_CNT; ++f)
                dp[i][f] = INF;

        // 为了回溯需要记录选择：对每个 gate 节点、每个函数 f，
        // 记录是从 (funcU, funcV) 组合过来。
        struct Choice {
            char fu = -1, fv = -1;
        };
        vector<array<Choice, FUNC_CNT>> choice(N + 1);

        // 输入节点初始化
        for (int i = 1; i <= n; ++i) {
            // 把该输入接 0：函数常 0，代价 0
            dp[i][0] = 0;
            // 接 1：函数常 1，代价 0
            dp[i][1] = 0;
            // 接 x：函数 x，代价 1
            dp[i][2] = 1;
            // 输入端无法直接实现 !x
            dp[i][3] = INF;
        }

        // 门节点 DP，拓扑顺序天然是 1..n+m，门按 j=1..m 递增
        for (int j = 1; j <= m; ++j) {
            int node = n + j;
            int lu = u[j], lv = v[j];
            // 初始化为 INF
            for (int f = 0; f < FUNC_CNT; ++f) {
                dp[node][f] = INF;
                choice[node][f].fu = choice[node][f].fv = -1;
            }

            // 枚举左、右子节点的函数类型
            for (int fu = 0; fu < FUNC_CNT; ++fu) {
                if (dp[lu][fu] >= INF) continue;
                for (int fv = 0; fv < FUNC_CNT; ++fv) {
                    if (dp[lv][fv] >= INF) continue;
                    int g = nandRes[fu][fv];                 // 本节点的函数
                    int cost = dp[lu][fu] + dp[lv][fv];      // 使用 x 的总数
                    if (cost < dp[node][g]) {
                        dp[node][g] = cost;
                        choice[node][g].fu = (char)fu;
                        choice[node][g].fv = (char)fv;
                    }
                }
            }
        }

        // 最终必须实现 targetFunc
        // 理论上一定有解（把所有输入都接 x 就行），这里直接使用 dp[root][targetFunc]
        // 同时我们要回溯具体每个 input 的赋值。
        vector<char> ansChar(n + 1, '?');

        // 递归回溯函数
        function<void(int,int)> build = [&](int node, int f) {
            if (node <= n) {
                // 输入端：根据函数类型确定赋值
                if (f == 0) ansChar[node] = '0';
                else if (f == 1) ansChar[node] = '1';
                else if (f == 2) ansChar[node] = 'x';
                else {
                    // f==3 (!x) 不应该在输入端出现，因为 dp[i][3] = INF
                    // 为安全起见，退化为 'x'（不会被真正用到）
                    ansChar[node] = 'x';
                }
                return;
            }
            int j = node - n;
            int lu = u[j], lv = v[j];
            auto ch = choice[node][f];
            int fu = ch.fu, fv = ch.fv;
            if (fu == -1 || fv == -1) {
                // 理论上不会发生，保险：不回溯
                return;
            }
            build(lu, fu);
            build(lv, fv);
        };

        build(root, targetFunc);

        // 把还没填的（理论上不会有）补成 'x' 防御
        for (int i = 1; i <= n; ++i) {
            if (ansChar[i] != '0' && ansChar[i] != '1' && ansChar[i] != 'x')
                ansChar[i] = 'x';
        }

        // 输出答案
        for (int i = 1; i <= n; ++i) cout << ansChar[i];
        cout << "\n";
    }

    return 0;
}
