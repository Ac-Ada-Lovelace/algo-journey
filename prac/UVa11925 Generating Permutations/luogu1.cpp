
#include <bits/stdc++.h>
using namespace std;
int main()
{
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
   int n, a[300];
   string s;
   while(scanf("%d", &n), n)
   {
      for(int i = 0; i < n; ++i)
         scanf("%d", a+i);
      s = "";
      for(int i = 0; i < n-1; ++i)
         for(int j = n-1; j >= 0; --j)
         {// 冒泡排序
            s += '2';
            if(j != n-1 && a[j+1] < a[j])
            {
               swap(a[j], a[j+1]);
               s += '1';
            }
         }
      reverse(s.begin(), s.end()); // 反转答案
      cout << s << endl;
   }
   return 0;
}
