#include<bits/stdc++.h>
#include<stdio.h> 
#include<stdlib.h> 
#include<graphics.h> 
#include<math.h>
using namespace std;
#define pb push_back 
#define mp make_pair 

vector<pair<int,int> > centres1,centres2;
void push(int cx, int cy,int x, int y)
{
    centres1.pb(mp(cx+x,cy-y));
    centres2.pb(mp(cx+x,cy+y));
    centres1.pb(mp(cx-x,cy-y));
    centres2.pb(mp(cx-x,cy+y));
}

void rangolipoints(int cx, int cy, int a, int b)
{
    int x = 0, y = b;
    int d = 4 * b * b + a * a - 4 * a * a * b;
    int deltaa=12*b*b,deltab=12*b*b+8*a*a*(1-b);
    push(cx, cy, x, y);

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
        push(cx, cy, x, y);

    }
    // cout<<x<<" "<<y;
    d = b*b+4*a*a-4*b*b*a;
    deltaa=12*a*a;
    deltab=12*a*a+8*b*b*(1-a);
    x=a,y=0;
    push(cx, cy, x, y);
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
        push(cx, cy, x, y);
    }
}


int main()
{
    int gd = DETECT, gm; 
    initgraph(&gd, &gm, NULL);
    int cx=300,cy=300,sa=0,ea=360,a=150,b=100,r=30;
    rangolipoints(cx,cy,a+r,b+r);
    sort(centres1.begin(), centres1.end());
    sort(centres2.begin(), centres2.end(),greater<pair<int,int> >());
    ellipse(cx,cy,sa,ea,a,b);
    
    for(int k=0;k<10;++k)
    {
    	for(int i=0;i<centres1.size();++i)
    	{
    		cleardevice();
    		setcolor(WHITE);
    		ellipse(cx,cy,sa,ea,a,b);
    		setcolor(RED);
    		circle(centres1[i].first,centres1[i].second,r);
    		int t;
    		// cin>>t;
    		delay(5);
    	}
    	for(int i=0;i<centres1.size();++i)
    	{
    		cleardevice();
    		setcolor(WHITE);
    		ellipse(cx,cy,sa,ea,a,b);
    		setcolor(RED);
    		circle(centres2[i].first,centres2[i].second,r);
    		int t;
    		// cin>>t;
    		delay(5);
    	}	
    }
    
    delay(30);
    // getch();
    closegraph();
    return 0;
}