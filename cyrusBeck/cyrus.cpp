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
#define INF 10000 
// #include"check.h"

struct point{
    float x,y;
};

bool onSegment(point p, point q, point r) 
{ 
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && 
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) 
        return true; 
    return false; 
} 

// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(point p, point q, point r) 
{ 
    int val = (q.y - p.y) * (r.x - q.x) - 
            (q.x - p.x) * (r.y - q.y); 

    if (val == 0) return 0; // colinear 
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 

// The function that returns true if line segment 'p1q1' 
// and 'p2q2' intersect. 
bool doIntersect(point p1, point q1, point p2, point q2) 
{ 
    // Find the four orientations needed for general and 
    // special cases 
    int o1 = orientation(p1, q1, p2); 
    int o2 = orientation(p1, q1, q2); 
    int o3 = orientation(p2, q2, p1); 
    int o4 = orientation(p2, q2, q1); 

    // General case 
    if (o1 != o2 && o3 != o4) 
        return true; 

    // Special Cases 
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1 
    if (o1 == 0 && onSegment(p1, p2, q1)) return true; 

    // p1, q1 and p2 are colinear and q2 lies on segment p1q1 
    if (o2 == 0 && onSegment(p1, q2, q1)) return true; 

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2 
    if (o3 == 0 && onSegment(p2, p1, q2)) return true; 

    // p2, q2 and q1 are colinear and q1 lies on segment p2q2 
    if (o4 == 0 && onSegment(p2, q1, q2)) return true; 

    return false; // Doesn't fall in any of the above cases 
} 

// Returns true if the point p lies inside the polygon[] with n vertices 
bool isInside(point polygon[], int n, point p) 
{ 
    // There must be at least 3 vertices in polygon[] 
    if (n < 3) return false; 

    // Create a point for line segment from p to infinite 
    point extreme = {INF, p.y}; 

    // Count intersections of the above line with sides of polygon 
    int count = 0, i = 0; 
    do
    { 
        int next = (i+1)%n; 

        // Check if the line segment from 'p' to 'extreme' intersects 
        // with the line segment from 'polygon[i]' to 'polygon[next]' 
        if (doIntersect(polygon[i], polygon[next], p, extreme)) 
        { 
            // If the point 'p' is colinear with line segment 'i-next', 
            // then check if it lies on segment. If it lies, return true, 
            // otherwise false 
            if (orientation(polygon[i], p, polygon[next]) == 0) 
            return onSegment(polygon[i], p, polygon[next]); 

            count++; 
        } 
        i = next; 
    } while (i != 0); 

    // Return true if count is odd, false otherwise 
    return count&1; // Same as (count%2 == 1) 
} 



point diff(point a,point b){
    point temp;
    temp.x=b.x-a.x;
    temp.y=b.y-a.y;
    return temp;
}

point normal(point ab){
    point temp=ab;
    float c=temp.x;
    temp.x=temp.y;
    temp.y=c;
    if(ab.x>=0&&ab.y>=0)
        temp.x*=-1;
    else if(ab.x>=0&&ab.y<=0)
        temp.x*=-1;
    else if(ab.x<=0&&ab.y<=0)
        temp.x*=-1;
    else if(ab.x<=0&&ab.y>=0)
        temp.x*=-1;
    return temp;
}

float dotproduct(point ab,point cd){
    float res;
    res=ab.x*cd.x+ab.y*cd.y;
    return res;
}

point sum (point a, point b){
    point temp;
    temp.x = a.x + b.x;
    temp.y = a.y +b.y;

    return temp;
}

point mulScalar(float t, point ab) {
    ab.x*=t;
    ab.y*=t;
    return ab;
}



void cyrusbeck(point p1,point p2,point* cw, int len){

    vector <point> res;
    vector <pair<float, float> > tees;
    tees.push_back(make_pair(0,0));
    tees.push_back(make_pair(1,1));
    for (int i =0; i<len; i++){

        point a=cw[i];
        point b=cw[(i+1)%len];
        point ab = diff(a,b);
        point Nab = normal(ab);
        point ap1 = diff(a,p1);
        point p1p2=diff(p1,p2);
        float dot1 = -1*dotproduct(Nab, ap1);
        float dot2 = dotproduct(Nab, p1p2);
        // cout<<dot1<<" "<<dot2<<endl;
        // cout<<ab.x<<" "<<ab.y<<"\t"<<Nab.x<<" "<<Nab.y<<endl;
        float t = float((float)dot1/(float)dot2);
        if (t >0 && t<1){

            tees.push_back(make_pair(t, dot2>0?1:0));
        }

    }
    sort(tees.begin(), tees.end());
    int flag=0;
    // cout<<tees.size()<<endl;
    // for(int i=0;i<tees.size();++i)
    // {
    //     cout<<tees[i].first<<" "<<tees[i].second<<endl;
    // }
    // cout<<endl;
    for(int i=0;i<tees.size();++i)
    {
        if(flag==0)
        {
            while(i<tees.size()&&tees[i].second==0)
                i++;
            i--;
        point temp = sum(p1,mulScalar(tees[i].first, diff(p1,p2)));
        if(isInside(cw,len,temp))
            res.push_back(temp);
        flag=1;
        }
        else
        {
            point temp = sum(p1,mulScalar(tees[i].first, diff(p1,p2)));
            if(isInside(cw,len,temp))
                res.push_back(temp);
            while(i<tees.size()&&tees[i].second==1)
                i++;
            i--;
            flag=0;
        }
    }
    
    for(int i=0;i<res.size();i+=2)
    {
        line(res[i].x,res[i].y,res[i+1].x,res[i+1].y);
    }
}

int main()
{
    int n;
    point p1,p2;
    cout<<"Enter the vertices of the Line\n";
    cin>>p1.x>>p1.y>>p2.x>>p2.y;
    cout<<"Enter the size of the clipping window\n";
    cin>>n;
    cout<<"Enter the vertices of the clipping window\n";
    point cw[n];
    for(int i=0;i<n;i++)
        cin>>cw[i].x>>cw[i].y;
    int gd=DETECT,gm;
    initgraph(&gd,&gm,NULL);
    setcolor(RED);
    line(p1.x,p1.y,p2.x,p2.y);
    setcolor(WHITE);
    for(int i=0;i<n;i++)
        line(cw[i].x,cw[i].y,cw[(i+1)%n].x,cw[(i+1)%n].y);
    delay(20);
    cyrusbeck(p1,p2,cw,n);
    getch();
    closegraph();
    return 0;
}
