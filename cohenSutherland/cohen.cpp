#include <iostream>
#include <graphics.h>
#define LEFT 1
#define BOTTOM 2
#define RIGHT 4
#define TOP 8

using namespace std;

struct point
{
    float x,y;
};

float xmin,ymin,xmax,ymax,m;
point a,b;
int code(point c)
{
    int reg=0;

    if(c.x<xmin)
        reg=reg|LEFT;
    if(c.x>xmax)
        reg=reg|RIGHT;
    if(c.y<ymin)
        reg=reg|BOTTOM;
    if(c.y>ymax)
        reg=reg|TOP;
    return reg;
}

void clipTest(point &c,int &r)
{
    if(r&LEFT) {
        float ynew=m*(xmin-c.x)+c.y;
        c.y=ynew;
        c.x=xmin;
        r=code(c);
    }
    if(r&RIGHT) {
        float ynew=m*(xmax-c.x)+c.y;
        c.y=ynew;
        c.x=xmax;
        r=code(c);
    }
    if(r&BOTTOM) {
        float xnew=(1/m)*(ymin-c.y)+c.x;
        c.y=ymin;
        c.x=xnew;
        r=code(c);
    }
    if(r&TOP) {
        float xnew=(1/m)*(ymax-c.y)+c.x;
        c.y=ymax;
        c.x=xnew;
        r=code(c);
    }
}

int main()
{
    cout << "Enter dimensions of rectangular window: ";
    cin >> xmin >> ymin >> xmax >> ymax;
    cout << "Enter the end points: ";
    cin >> a.x >> a.y >> b.x >> b.y;
    m=(b.y-a.y)/(b.x-a.x);
    int gd=DETECT,gm;
    initgraph(&gd,&gm,NULL);
    setcolor(RED);
    line(xmin,ymin,xmax,ymin);
    line(xmax,ymin,xmax,ymax);
    line(xmax,ymax,xmin,ymax);
    line(xmin,ymax,xmin,ymin);
    line(a.x,a.y,b.x,b.y);
    setcolor(WHITE);
    while (1) {
        int r1=code(a);
        int r2=code(b);
        if ((r1&r2)!=0) {
            break;
        }
        if((r1|r2)==0) {    //visible
            line(a.x,a.y,b.x,b.y);
            break;
        }
        clipTest(a,r1);
        clipTest(b,r2);
    }
    delay(5);
    getch();
    closegraph();
    return 0;
}
