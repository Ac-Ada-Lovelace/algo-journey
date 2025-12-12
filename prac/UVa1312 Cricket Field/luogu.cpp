
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;
#define N 105
struct node
{
	int x,y;
	bool operator < (const node &b) const
	{
		if(y!=b.y)
			return y<b.y;
		else
			return x<b.x;
	}	
}inp[N];
int wzx[N];
int main()
{	
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
	int q;
	scanf("%d",&q);
	int x,y,n,x0,y0;
	int oo=0;
	while(q--)
	{
		scanf("%d%d%d",&n,&x,&y);
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&inp[i].x,&inp[i].y);
			wzx[i]=inp[i].x;
		}
		wzx[0]=0,wzx[n+1]=x;
		sort(inp+1,inp+n+1);
		sort(wzx,wzx+n+2);
		int da=0,ansx,ansy;
		for(int i=0;i<=n+1;i++)
		{
			for(int j=i+1;j<=n+1;j++)
			{
				int disx=wzx[j]-wzx[i];
				int disy,maxx;
				int yy=0;
				for(int k=1;k<=n;k++)
				{
					if(inp[k].x>wzx[i]&&inp[k].x<wzx[j])
					{
						disy=inp[k].y-yy;
						maxx=min(disx,disy);
						if(da<maxx)
						{
							da=maxx;
							ansx=wzx[i];
							ansy=yy;
						}
						yy=inp[k].y;
					}
				}
				disy=y-yy;
				maxx=min(disx,disy);
				if(da<maxx)
				{
					da=maxx;
					ansx=wzx[i];
					ansy=yy;
				}
			}
		}
		
		printf("%d %d %d\n",ansx,ansy,da);
		if(q)
			printf("\n");
	}
	return 0;
}
