#include<bits/stdc++.h>
#include<stdio.h> 
#include<stdlib.h> 
#include<graphics.h> 
#include<math.h>
using namespace std;
void drawParabola(int cx, int cy,int x, int y,int color)
{
    putpixel(cx - x, cy - y, color);
    putpixel(cx + x, cy - y, color);
}

void myparabola(int cx,int cy, int a,int color)
{
	int d=1-2*a;
	int da=3,db=3-4*a;
	int x=0,y=0;
	drawParabola(cx,cy,x,y,color);
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
		drawParabola(cx,cy,x,y,color);
	}
	d=4*x+1-16*a;
	da=8*x+8-16*a;
	db=-16*a;
	drawParabola(cx,cy,x,y,color);
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
		drawParabola(cx,cy,x,y,color);
	}
}

int main()
{
    int gd = DETECT, gm; 
    initgraph(&gd, &gm, NULL);

    int a, cx, cy;
    cout << "Enter the center of parabola: ";
    cin >> cx >> cy;
    cout << "Enter the value of a for parabola: ";
    cin >> a;

    myparabola(cx, cy, a,WHITE);
    delay(30);
    getch();
    closegraph();
    return 0;
}