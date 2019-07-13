#include<bits/stdc++.h>
#include<stdio.h> 
#include<stdlib.h> 
#include<graphics.h> 
#include<math.h>
#include"circle.c"
#include"line.c"
#include"wait.c"
#include<X11/Xlib.h>

using namespace std;

int main(){
	XInitThreads();
	int gd = DETECT, gm; 
	initgraph(&gd, &gm, NULL); 
	int cx=200,cy=200,r=100,dg,x,y;
	circleM(200,200,100,WHITE);
	double tx,ty;
	dg=360;
	int k=60;

	while(k--){
		tx=r*sin((3.14159265/ 180.0)*dg);
		ty=r*cos((3.14159265/ 180.0)*dg);
		x=tx+cx;
		y=ty+cy;
		lineM(cx,cy,x,y,GREEN);
		delay(20);
		lineM(cx,cy,x,y,BLACK);
		// delay(30);
		dg-=6;
		if(dg==0)
			dg=360; 
	}
	// wait_for_char();
	closegraph();
	return 0; 
}