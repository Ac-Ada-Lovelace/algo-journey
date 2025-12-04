#include<cstdio>
#include<string>
#include<iostream>
#include<set>
using namespace std;
using lint = long long ;
set<lint> buffer;
const int point[] = {0,2,4,9,11,13,18,20,22}, one[] = {1,3,9,13,18,22,19,21},zero[] = {10,11,12,20};
bool vis[9];string temp;int maxd;
void bitcont(lint & tar,int offset) //将输入数据转换为long long，offset标识行号
{
    lint bit = 1;
    for(int i = 0; i < 9; ++i,bit = 1) if(temp[i] != ' ') tar = tar | (bit <<(i + offset));
}

void draw(int now,lint & tar)//画正方形
{
    int cur = point[now];
    lint bit = 1;// 位比较多，要用这个移位，匿名变量1 默认是int
    for(int i = 0; i < 8; ++i,bit = 1) tar = tar | (bit << (one[i] + cur));//或运算添边
    for(int i = 0; i < 4; ++i,bit = 1) tar = tar & (~(bit << (zero[i] + cur)));//将正方形内部边全部清空
}

void dfs(int d,lint cur)
{
    if(d == maxd) {  buffer.insert(cur); return;  }
    for(int i = 0; i < 9; ++i)
    {
        if(vis[i]) continue;
        lint old = cur;
        draw(i,cur);
        vis[i] = true;
        dfs(d + 1, cur);
        cur = old, vis[i] = false;
    }
}
int main()
{
    for(maxd = 1; maxd <= 6; ++maxd) dfs(0,0);//枚举所有的状态
    int cont = 0;
    while(getline(cin,temp))
    {
        lint target  =  0;
        if(temp[0] == '0') break;
        bitcont(target,0);
        for(int i  = 1; i <= 4; ++i)
        {
            getline(cin,temp);
            bitcont(target,i * 9);
        }
        printf("Case %d: ",++cont);
        if(buffer.count(target) == 1) printf("Yes\n");//set 判重，可以手写hash，更快一点
        else printf("No\n");
    }
    return 0;
}
