
#include<iostream>
#include<string>
#include<cstring>
#include<fstream>

using namespace std;

const int N=20;
const int K=26;

int n,k;
int r[N]; //N位二进制存储目前行占位情况 
int a[K][3]; //存储每个小组组长的位置和人数
int way[K][100][3]; //预处理出的每一个小组可能的占位方式，第一维小组，第二维方式编号，第三维三个数分别表示:起始行，结束行，单行占位情况(N位二进制数)
int way_num[K]; //每个小组的拜访方式总数 
int ans[K]; 
bool vis[K];
int w[K];

void init(){
  memset(vis,false,sizeof(vis));
  memset(r,0,sizeof(r));
  memset(way_num,0,sizeof(way_num));
}

bool dfs(int d){
    if (d==k) return true;
    else {
      for (int i=0;i<way_num[w[d]];++i){
        int ok=true;
        for (int j=way[w[d]][i][0];j<=way[w[d]][i][1];++j)
          if (r[j] & way[w[d]][i][2]) {
            ok=false;
            break;
          }
        if (ok){
          for (int j=way[w[d]][i][0];j<=way[w[d]][i][1];++j)
            r[j]=r[j] | way[w[d]][i][2];
          ans[w[d]]=i;
          if (dfs(d+1)) return true;
          for (int j=way[w[d]][i][0];j<=way[w[d]][i][1];++j)
            r[j]=r[j] ^ way[w[d]][i][2];
        }
      }
      return false;
    }
}

void pre(){ //预处理每一个小组的可能的占位方式
  for (int i=0;i<k;++i){
    int x=a[i][0],y=a[i][1],num=a[i][2];
    for (int j=1;j<=num;++j)
      if (num % j==0 && j<=n && num/j<=n){
        int l=num / j;
        for (int p=max(y-l+1,0);p<=min(y,n-l);++p){
          int seat=0;
          for (int q=p;q<p+l;++q){//得出单行占位情况
            seat+=(1 << q);
          }
          for (int q=max(x-j+1,0);q<=min(x,n-j);++q){
            bool ok=true;
            for (int kk=0;kk<k;++kk)
              if (kk!=i && a[kk][0]>=q && a[kk][0]<q+j && a[kk][1]>=p && a[kk][1]<p+l){//如果方案覆盖了一个组长，则一定不可行 
                ok=false;
                break;
              }
            if (ok){
              way[i][way_num[i]][0]=q;
              way[i][way_num[i]][1]=q+j-1;
              way[i][way_num[i]][2]=seat;
              way_num[i]++;
            }
          }
        }
      }
  }
}

void printAns(){
  char map[n][n];
  for (int i=0;i<k;++i){
    char c='A'+i;
    for (int j=way[i][ans[i]][0];j<=way[i][ans[i]][1];++j){
      for (int l=0;l<n;++l)
        if (way[i][ans[i]][2] & (1 << l)) map[j][l]=c; 
    }
  }
  for (int i=0;i<n;++i){
    for (int j=0;j<n;++j) cout << map[i][j];
    cout << endl;
  }
    
      
}

int main(){
  
  while (cin >> n >> k){
    if (n==0) break;
    init();
    int t=0;
    for (int i=0;i<n;++i){
      string s;
      cin >> s;
      for (int j=0;j<n;++j)
        if (s[j]!='.'){
          a[t][0]=i;
          a[t][1]=j;
          a[t++][2]=s[j]-'0';
        }
    }
    pre();
    for (int i=0;i<k;++i){
      int min=100,now;
      for (int j=0;j<k;++j)
        if (!vis[j] & way_num[j]<min) {
          min=way_num[j];
          now=j;
        }
      w[i]=now;
      vis[now]=true;
    }
    dfs(0); //题意表明一定有解，默认返回true
    printAns(); 
  }  
  return 0;
} 
