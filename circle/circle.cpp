#include<bits/stdc++.h>
#include<stdio.h> 
#include<stdlib.h> 
#include<graphics.h> 
#include<math.h>
using namespace std;

void displayCircle(int x,int y,int cx,int cy,int color)
{
	putpixel(x+cx,y+cy,color);
	putpixel(y+cx,x+cy,color);
	putpixel(x+cx,-1*y+cy,color);
	putpixel(-1*y+cx,x+cy,color);
	putpixel(-1*x+cx,y+cy,color);
	putpixel(y+cx,-1*x+cy,color);
	putpixel(-1*x+cx,-1*y+cy,color);
	putpixel(-1*y+cx,-1*x+cy,color);
}
int roundy(double k)
{
	if(k-(int)k>0.5)
	{
		return ((int)k+1);
	}
	else
	{
		return (int)k;
	}
}
void circleM(int cx,int cy,int r,int color)
{
	int x = 0;
	int y = r;
	int d = 3-2*r;
	int deltae=3,deltase=5-2*r;
	displayCircle(x, y,cx,cy,color);
	while (x <= y)
	{
		if (d <= 0)
		{
			d += deltae;
			deltae+=2;
			deltase+=2;
		}
		else
		{
			d += deltase;
			deltae+=2;
			deltase+=4;
			y--;
		}
		x++;
		displayCircle(x, y,cx, cy,color);
	}
}

int main()
{
	int gd = DETECT, gm; 
	initgraph(&gd, &gm, NULL);
	int r;
	cout<<"enter radius:";
	cin>>r;
	int x,y;
	cout<<"enter centre:";
	cin>>x>>y;
	circleM(x,y,r,WHITE);
	delay(5);
	getchar();
	closegraph();
}
