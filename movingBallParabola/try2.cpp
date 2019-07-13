#include<iostream>
#include <graphics.h>
using namespace std;

int xc=sqrt(64*200),yc=200,r=20;
int Y=300,X=300;
int x[3],y[3];

void parabola () {

    int a=0,b=0;

    for(; b<16; a=a+1) {
        b=(a*a)/64;
        putpixel(X-a-20, Y-b+20, WHITE);
        putpixel(X+a+20, Y-b+20, WHITE);
    }

    while(b<200) {
        b=b+1;
        a=sqrt(64*b);
        putpixel(X-a-20, Y-b+20, WHITE);
        putpixel(X+a+20, Y-b+20, WHITE);
    }

    line(X-20,Y+20,X+20,Y+20);
}

int main()
{
	double angle=0,theta;
	int i,a;
	int gd=DETECT,gm;
	initgraph(&gd,&gm,NULL);


    while(yc>0)
    {
        theta=M_PI*angle/180;
        cleardevice();
        setcolor(WHITE);
        parabola();
        setcolor(RED);
        circle(X-xc,Y-yc,r);
        for(i=0;i<4;i++)
        {
            theta=M_PI*angle/180;
            x[i]=xc+r*cos(theta);
            y[i]=yc+r*sin(theta);
            angle+=90;
            line(X-xc,Y-yc,X-x[i],Y-y[i]);

        }
        angle+=10;
        yc=yc-10;
        xc=sqrt(64*yc);

        delay(50);

    }

    while(yc<200)
    {
        theta=M_PI*angle/180;
        cleardevice();
        setcolor(WHITE);
        parabola();
        setcolor(RED);
        circle(X+xc,Y-yc,r);
        for(i=0;i<4;i++)
        {
            theta=M_PI*angle/180;
            x[i]=xc+r*cos(theta);
            y[i]=yc+r*sin(theta);
            angle+=90;
            line(X+xc,Y-yc,X+x[i],Y-y[i]);
        }
        angle-=10;
        yc=yc+10;
        xc=sqrt(64*yc);

        delay(50);

    }

	getch();
	closegraph();
}