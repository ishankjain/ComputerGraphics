#include<iostream>
#include<graphics.h>
using namespace std;
#define ROUND(a) ((int)(a+0.5))

#define LEFT_EDGE 0x1
#define RIGHT_EDGE 0x2
#define BOTTOM_EDGE 0x4
#define TOP_EDGE 0x8

#define INSIDE(a) (!a)
#define REJECT(a,b) (a&b)
#define ACCEPT(a,b) (!(a|b))

struct window
{
float x;
float y;
};

struct point
{
float x;
float y;
};

unsigned char encode(point pt, window winMin,window winMax){
    unsigned char code=0x00;
    if(pt.x < winMin.x)
    code = code | LEFT_EDGE;
    if(pt.x > winMax.x)
    code = code | RIGHT_EDGE;
    if(pt.y < winMin.y)
    code = code | BOTTOM_EDGE;
    if(pt.y > winMax.y)
    code = code | TOP_EDGE;
    return(code);
}

void clipLineMid(window winMin, window winMax,point p1,point p2){
    struct point mid;
    int v;
    unsigned char code1,code2;
    code1=encode(p1,winMin,winMax);
    code2=encode(p2,winMin,winMax);
    if(ACCEPT(code1,code2))
    v=0;
    else if(REJECT(code1,code2))
    v=1;
    else
    v=2;
    switch(v){
        case 0:
            p1.x=(int)p1.x;
            p1.y=(int)p1.y;
            p2.x=(int)p2.x;
            p2.y=(int)p2.y;
            /* Line conpletely visible */
            setcolor(WHITE);
            line(p1.x, p1.y, p2.x, p2.y);
            break;
        case 1: /* Line completely invisible */
            break;
        case 2: /* line partly visible */
            mid.x = p1.x + (p2.x-p1.x)/2;
            mid.y = p1.y + (p2.y-p1.y)/2;
            clipLineMid(winMin,winMax,p1,mid);
            mid.x = mid.x+1;
            mid.y = mid.y+1;
            clipLineMid(winMin,winMax,mid,p2);
            break;
    }
}

int main()
{
    struct point p1, p2;struct window winMin, winMax;
    cout << "Enter dimensions of rectangular window: ";
    cin >> winMin.x >> winMin.y >> winMax.x >> winMax.y;
    cout << "Enter the end points: ";
    cin >> p1.x >> p1.y >> p2.x >> p2.y;
    // m=(b.y-a.y)/(b.x-a.x);
    int gd=DETECT,gm;
    initgraph(&gd,&gm,NULL);
    setcolor(RED);
    line(p1.x, p1.y, p2.x, p2.y);
    // setcolor(BLUE);
    line(winMin.x, winMin.y, winMin.x, winMax.y);
    line(winMin.x, winMin.y, winMax.x, winMin.y);
    line(winMax.x, winMax.y, winMin.x, winMax.y);
    line(winMax.x, winMax.y, winMax.x, winMin.y);
    setcolor(WHITE);
    clipLineMid(winMin,winMax,p1,p2);
    delay(5);
    getch();
    closegraph();
    return 0;
}
