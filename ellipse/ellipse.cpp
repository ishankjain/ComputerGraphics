#include<bits/stdc++.h>
#include<stdio.h> 
#include<stdlib.h> 
#include<graphics.h> 
#include<math.h>
using namespace std;

void drawEllipse(int cx, int cy,int x, int y,int color)
{
    putpixel(cx + x, cy - y, color);
    putpixel(cx + x, cy + y, color);
    putpixel(cx - x, cy - y, color);
    putpixel(cx - x, cy + y, color);
}

void myellipse(int cx, int cy, int a, int b,int color)
{
    int x = 0, y = b;
    int d = 4 * b * b + a * a - 4 * a * a * b;
    int deltaa=12*b*b,deltab=12*b*b+8*a*a*(1-b);
    drawEllipse(cx, cy, x, y,color);

    while (a * a * y >= x * b * b) {
        if (d <= 0) {
            d += deltaa;
            deltaa+=8*b*b;
            deltab+=8*b*b;
        }
        else {
            d += deltab;
            deltaa+=8*b*b;
            deltab+=8*b*b+8*a*a;
            y--;
        }
        x++;
        drawEllipse(cx, cy, x, y,color);

    }
    // cout<<x<<" "<<y;
    d = b*b+4*a*a-4*b*b*a;
    deltaa=12*a*a;
    deltab=12*a*a+8*b*b*(1-a);
    x=a,y=0;
    drawEllipse(cx, cy, x, y,color);
    while (b*b*x>a*a*y) {
        if (d <= 0) {
            d += deltaa;
            deltaa+=8*a*a;
            deltab+=8*a*a;
        }
        else {
            d += deltab;
            deltaa+=8*a*a;
            deltab+=8*b*b+8*a*a;
            x--;
        }
        y++;
        drawEllipse(cx, cy, x, y,color);
    }
}

int main()
{
    int gd = DETECT, gm; 
    initgraph(&gd, &gm, NULL);

    int a, b, cx, cy;
    cout << "Enter the center of ellipse: ";
    cin >> cx >> cy;
    cout << "Enter the values of a and b for ellipse: ";
    cin >> a >> b;

    myellipse(cx, cy, a, b);
    delay(30);
    getch();
    closegraph();
    return 0;
}