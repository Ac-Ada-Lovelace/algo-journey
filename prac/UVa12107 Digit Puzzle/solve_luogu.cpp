
#include <bits/stdc++.h>
using namespace std;
void fastio() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}
string a[5];
char dict[15] = {'*', '0', '1', '2', '3', '4',
                 '5', '6', '7', '8', '9'}; // 字典序排列
int len[5], dep;
int toint(string s) // 将字符串转为数
{
    int x = 0, len = s.length();
    for (int i = 0; i < len; i++)
        x = (x * 10) + (s[i] - '0');
    return x;
}
bool calc() // 当前等式是否能成立（最后一个数可能有空格）
{
    int x = toint(a[1]), y = toint(a[2]), z = x * y;
    string t = ""; // 将 z 转化为 string 类型
    for (int i = 0; i < len[3]; i++)
        t += (char)(z % 10 + '0'), z /= 10;
    reverse(t.begin(), t.end());
    if (z != 0 || t[0] == '0')
        return false; // 位数不对就挂掉
    for (int i = 0; i < len[3]; i++)
        if (a[3][i] != '*' && a[3][i] != t[i]) // 不是空格，但和目标不同，挂掉
            return false;
    return true;
}
int chk(int c, int pos) // 看看是否唯一解
{
    int cnt = 0; // 记录有多少个解
    if (c == 3)
        return calc(); // 前两个数填完了
    int nxtc = (pos == len[c] - 1 ? c + 1 : c),
        nxtpos = (pos == len[c] - 1 ? 0 : pos + 1); // 求下一位
    if (a[c][pos] == '*')                           // 乱填一下
    {
        for (int i = 1; i <= 10; i++) // 不能填空格
        {
            if (i == 1 && pos == 0)
                continue; // 首位不能为0
            a[c][pos] = dict[i], cnt += chk(nxtc, nxtpos);
            if (cnt > 1)
                break; // 反正都不是唯一解了，直接退出就行。
        }
        a[c][pos] = '*'; // 恢复
    } else
        cnt = chk(nxtc, nxtpos); // 有数字就不用乱填了
    return cnt; // 此时，cnt=0 无解；cnt=1 唯一解；cnt>=2 多解。注意 cnt>=2
                // 时不一定是真正解的数量
}
bool dfs(int modify, int c, int pos) // modify:修改了多少次 c:当前位置
{
    if (modify == dep)
        return chk(1, 0) == 1; // 不能再改了，看看能不能满足
    if (c == 4)
        return false;
    int nxtc = (pos == len[c] - 1 ? c + 1 : c),
        nxtpos = (pos == len[c] - 1 ? 0 : pos + 1); // 求下一位
    for (int i = 0; i <= 10; i++) {
        if (i == 1 && pos == 0)
            continue; // 首位不能为0
        if (a[c][pos] == dict[i]) {
            if (dfs(modify, nxtc, nxtpos))
                return true; // 不用改，modify 不变
        } else {
            char zltAKIOI = a[c][pos]; // 神仙祈福
            a[c][pos] = dict[i];
            if (dfs(modify + 1, nxtc, nxtpos))
                return true;      // 要改，modify 加一
            a[c][pos] = zltAKIOI; // 神仙附身
        }
    }
    return false;
}
int main() {
    fastio();
    for (int i = 1;; i++) {
        cin >> a[1];
        if (a[1] == "0")
            break;
        cin >> a[2] >> a[3];
        len[1] = a[1].length(), len[2] = a[2].length(), len[3] = a[3].length();
        for (dep = 0;; dep++) // 迭代加深搜索
            if (dfs(0, 1, 0)) {
                cout << "Case " << i << ": " << a[1] << ' ' << a[2] << ' '
                     << a[3] << '\n';
                break;
            }
    }
    return 0;
}
