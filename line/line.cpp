#include<bits/stdc++.h>
#include<stdio.h> 
#include<stdlib.h> 
#include<graphics.h> 
#include<math.h>
using namespace std;

void swap(int *x1,int *y1,int *x2,int *y2)
{
	int t1=*x1,t2=*y1;
    *x1=*x2,*y1=*y2;
   	*x2=t1,*y2=t2;
}

void lineM(int x1,int y1,int x2,int y2,int color)
{
	if(x2==x1)
	{
		if(y2<y1)
			swap(&x1,&y1,&x2,&y2);
		while(y1<=y2)
		{
			putpixel(x1, y1, color);
			y1++;
		}
		return;
	}
	double m=((y2-y1)*1.0)/((x2-x1)*1.0);
	if(abs(m)<1.0)
	{
		if(x2<x1)
		{
			swap(&x1,&y1,&x2,&y2);
		}
		int dx = abs(x2-x1);
		int dy = abs(y2-y1);
		int x = x1, y = y1;
		int d;
		putpixel(x, y, color);
		d = 2*dy - dx;
		while (x <= x2)
		{
			if (d <= 0)
				d += dy;
			else{
				d += dy - dx;
				if(y<y2)
				{
					y++;
				}
				else
				{
					y--;
				}
			}
			x++;
			putpixel(x, y, color);
		}
	}
	else
	{
		if(y2<y1)
		{
			swap(&x1,&y1,&x2,&y2);
		}
		int dx = abs(x2-x1);
		int dy = abs(y2-y1);
		int x = x1, y = y1;
		int d;
		putpixel(x, y, color);
		d = 2*dx - dy;
		while (y <= y2)
		{
			if (d <= 0)
			{
				d += dx;
			}
			else
			{
				d += dx - dy;
				if(x<x2)
				{
					x++;
				}
				else
				{
					x--;
				}
			}
			y++;
			putpixel(x, y, color);
		}
	}
}

int main()
{
	// XInitThreads();
	int gd = DETECT, gm;
	initgraph(&gd, &gm, NULL);

	int x1,y1,x2,y2;
	cout<<"Enter 1st coordinate:";
	cin>>x1>>y1;
	cout<<"Enter 2nd coordinate:";
	cin>>x2>>y2;
	lineM(x1,y1,x2,y2,WHITE);
	getchar();
	closegraph();
	return 0;
}