// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=844&page=show_problem&problem=4481
// UVa1606 Amphiphilic Carbon Molecules
#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-9;

struct Point {
    int x, y, type; // type: 0=亲水, 1=疏水
};

struct Angle {
    double ang;
    int type;
    bool operator<(const Angle& other) const {
        return ang < other.ang;
    }
};

int n;
Point points[1005];

// 计算从 p 到 q 的极角
double getAngle(Point p, Point q) {
    return atan2(q.y - p.y, q.x - p.x);
}

// 核心算法：以点 i 为基准，旋转直线统计最大溶解数
int solve(int i) {
    vector<Angle> angles;

    // 计算所有其他点相对于点 i 的极角
    for (int j = 0; j < n; j++) {
        if (i == j)
            continue;
        double ang = getAngle(points[i], points[j]);
        angles.push_back({ang, points[j].type});
    }

    // 按极角排序
    sort(angles.begin(), angles.end());

    int m = angles.size();
    if (m == 0)
        return 1; // 只有一个点

    // 初始化：统计直线初始方向时的溶解数
    // 假设直线方向为某个角度，计算初始状态
    // 策略：让直线垂直向上（角度=-90度），统计右侧的点

    int maxCount = 0;

    // 尝试每个可能的直线方向
    // 直线经过点 i，方向由某个其他点决定
    for (int start = 0; start < m; start++) {
        // 以 angles[start] 的方向作为直线方向
        double lineAngle = angles[start].ang;

        // 统计当前直线方向下的溶解数
        int count = 1; // 点 i 自己（在直线上）

        for (int j = 0; j < m; j++) {
            // 计算点相对于直线的位置
            double relAngle = angles[j].ang - lineAngle;

            // 归一化到 [0, 2π)
            while (relAngle < 0)
                relAngle += 2 * PI;
            while (relAngle >= 2 * PI)
                relAngle -= 2 * PI;

            // 判断点在直线的哪一侧
            // [0, π): 左侧（水侧）
            // [π, 2π): 右侧（丙酮侧）
            // 接近 0 或 π: 在直线上

            if (relAngle < EPS || fabs(relAngle - PI) < EPS) {
                // 在直线上，都溶解
                count++;
            } else if (relAngle < PI) {
                // 左侧（水侧）
                if (angles[j].type == 0)
                    count++; // 亲水性溶解
            } else {
                // 右侧（丙酮侧）
                if (angles[j].type == 1)
                    count++; // 疏水性溶解
            }
        }

        maxCount = max(maxCount, count);
    }

    // 还要尝试垂直方向（可能没有点在这个方向）
    // 尝试几个特殊角度
    for (double baseAngle : {0.0, PI / 2, PI, 3 * PI / 2}) {
        int count = 1;

        for (int j = 0; j < m; j++) {
            double relAngle = angles[j].ang - baseAngle;
            while (relAngle < 0)
                relAngle += 2 * PI;
            while (relAngle >= 2 * PI)
                relAngle -= 2 * PI;

            if (relAngle < EPS || fabs(relAngle - PI) < EPS) {
                count++;
            } else if (relAngle < PI) {
                if (angles[j].type == 0)
                    count++;
            } else {
                if (angles[j].type == 1)
                    count++;
            }
        }

        maxCount = max(maxCount, count);
    }

    return maxCount;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}
