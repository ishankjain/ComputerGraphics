#include <iostream>
#include <graphics.h>
#define PQ 1
#define QR 2
#define RP 4

using namespace std;

struct point
{
    float x,y;
};
float m;
point a,b,p,q,r;

bool outside(point l,point m,point n,point o)
{
    int t1=(l.y-n.y)*(n.x-m.x)-(l.x-n.x)*(n.y-m.y);
    int t2=(o.y-n.y)*(n.x-m.x)-(o.x-n.x)*(n.y-m.y);
    // cout<<t1<<" "<<t2<<endl;
    if((t1*t2)<0)
        return true;
    else return false;
}
int code(point c)
{
    int reg=0;

    if(outside(c,p,q,r))
    {
        // cout<<"pq";
        reg=reg|PQ;
    }
    if(outside(c,q,r,p))
    {
        // cout<<"qr";
        reg=reg|QR;
    }
    if(outside(c,r,p,q))
    {
        // cout<<"rp";
        reg=reg|RP;
    }
    return reg;
}

point Intersection(point A, point B, point C, point D) 
{ 
    // Line AB represented as a1x + b1y = c1 
    double a1 = B.y - A.y; 
    double b1 = A.x - B.x; 
    double c1 = a1*(A.x) + b1*(A.y); 
  
    // Line CD represented as a2x + b2y = c2 
    double a2 = D.y - C.y; 
    double b2 = C.x - D.x; 
    double c2 = a2*(C.x)+ b2*(C.y); 
  
    double determinant = a1*b2 - a2*b1; 
    point ans;
    ans.x = (b2*c1 - b1*c2)/determinant; 
    ans.y = (a1*c2 - a2*c1)/determinant; 
    return ans; 
} 

void clipTest(point &c,int &r1)
{
    if(r1&PQ) {
        c=Intersection(a,b,p,q);
    }
    if(r1&QR) {
        c=Intersection(a,b,q,r);
    }
    if(r1& RP) {
        c=Intersection(a,b,r,p);
    }
}

int main()
{
    cout << "Enter coordinates of triagular window: ";
    cin>>p.x>>p.y>>q.x>>q.y>>r.x>>r.y;
    cout << "Enter the end points of line: ";
    cin >> a.x >> a.y >> b.x >> b.y;
    m=(b.y-a.y)/(b.x-a.x);
    int gd=DETECT,gm;
    initgraph(&gd,&gm,NULL);
    setcolor(RED);
    line(p.x,p.y,q.x,q.y);
    line(q.x,q.y,r.x,r.y);
    line(r.x,r.y,p.x,p.y);
    line(a.x,a.y,b.x,b.y);
    setcolor(WHITE);
    while (1) 
    {
        int r1=code(a);
        int r2=code(b);
        // cout<<r1;
        if ((r1&r2)!=0) {
            break;
        }
        if((r1|r2)==0) {    //visible
            line(a.x,a.y,b.x,b.y);
            break;
        }
        // break;
        clipTest(a,r1);
        clipTest(b,r2);
    }
    delay(5);
    getch();
    closegraph();
    return 0;
}
