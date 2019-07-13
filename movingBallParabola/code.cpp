#include<bits/stdc++.h>
#include<stdio.h> 
#include<stdlib.h> 
#include<graphics.h> 
#include<math.h>
using namespace std;
#define pb push_back 
#define mp make_pair 
#define f first
#define s second

vector<pair<int,int> >centres;
void drawParabola(int cx, int cy,int x, int y,int color,int a,int r)
{
    putpixel(cx - x, cy - y, color);
    putpixel(cx + x, cy - y, color);
    int d=sqrt(1+y/a);
    int xn=x-((x*r)/(2*a*d));
    int yn=y+(r/d);
    centres.pb(mp(cx-xn,cy-yn));
    centres.pb(mp(cx+xn,cy-yn));
}

void myparabola(int cx,int cy, int a,int color,int r)
{
	int d=1-2*a;
	int da=3,db=3-4*a;
	int x=0,y=0;
	drawParabola(cx,cy,x,y,color,a,r);
	while(x<=2*a)
	{
		if(d<=0)
		{
			d+=da;
			da+=2;
			db+=2;
		}
		else
		{
			d+=db;
			da+=2;
			db+=2;
			y++;
		}
		x++;
		drawParabola(cx,cy,x,y,color,a,r);
	}
	d=4*x+1-16*a;
	da=8*x+8-16*a;
	db=-16*a;
	drawParabola(cx,cy,x,y,color,a,r);
	while(y<=200)
	{
		if(d<=0)
		{
			x++;
			d+=da;
			da+=8;
		}
		else
		{
			d+=db;
		}
		y++;
		drawParabola(cx,cy,x,y,color,a,r);
	}
}

int main()
{
	int gd = DETECT, gm; 
    initgraph(&gd, &gm, NULL);
    int r=30;
    myparabola(350,300,50,WHITE,r+5);
	sort(centres.begin(), centres.end());
	for(int j=0;j<1;++j)
	{
		int i;
		for(i=0;i<centres.size();++i)
		{
    		setcolor(RED);
    		circle(centres[i].first,centres[i].second,r);
    		delay(10);
    		setcolor(BLACK);
    		circle(centres[i].first,centres[i].second,r);
		}
		i--;
		for(;i>=0;--i)
		{
    		setcolor(RED);
    		circle(centres[i].first,centres[i].second,r);
    		delay(10);
    		setcolor(BLACK);
    		circle(centres[i].first,centres[i].second,r);
		}
	}    
    delay(100);
    getch();
    closegraph();
    return 0;
}

