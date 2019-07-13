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



vector<pair<point,int> > cyrusbeck(point p1,point p2,point* cw, int len){
    vector <pair<point,int> > res;
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
        float t = float((float)dot1/(float)dot2);
        if (t >0 && t<1){

            tees.push_back(make_pair(t, dot2>0?1:0));
        }

    }
    sort(tees.begin(), tees.end());
    int flag=0;
    res.pb(mp(p1,-1));
    for(int i=0;i<tees.size();++i)
    {
        if(flag==0)
        {
            while(i<tees.size()&&tees[i].second==0)
                i++;
            i--;
            if(tees[i].f!=0)
            {
                point temp = sum(p1,mulScalar(tees[i].first, diff(p1,p2)));
                if(isInside(cw,len,temp))
                    res.push_back(mp(temp,tees[i].second));
            }
            else
            {
                point temp = p1;
                if(isInside(cw,len,temp))
                    res[0].s=0;
            }
            flag=1;
        }
        else
        {
            if(tees[i].f!=1)
            {
                point temp = sum(p1,mulScalar(tees[i].first, diff(p1,p2)));
                if(isInside(cw,len,temp))
                    res.push_back(mp(temp,tees[i].s));
            }
            while(i<tees.size()&&tees[i].second==1)
                i++;
            i--;
            flag=0;
        }
    }
    // res.pb(mp(p2,-1));
    // for(int i=0;i<res.size();i+=2)
    // {
    //     line(res[i].x,res[i].y,res[i+1].x,res[i+1].y);
    // }
    return res;
}
void traversecw(vector<pair<point,int> > nsp,vector<pair<point,int> > ncw,vector<pair<point,int> > &partial,point p,vector<int> &visited);
void traversesp(vector<pair<point,int> > nsp,vector<pair<point,int> > ncw,vector<pair<point,int> > &partial,point p,vector<int> &visited);
void traversecw(vector<pair<point,int> > nsp,vector<pair<point,int> > ncw,vector<pair<point,int> > &partial,point p,vector<int> &visited)
{
    int i;
    for(i=0;i<ncw.size();++i)
    {
        if((int)ncw[i].f.x==(int)p.x&&(int)ncw[i].f.y==(int)p.y)
        {
            break;
        }
    }
    // if(i==10)
    //     i=9;
    int j=(i+1)%ncw.size();
    cout<<"\t"<<j<<endl;
    while(1)
    {
        // cout<<"!";
        if(ncw[j].s==0)
        {
            partial.pb(ncw[j]);
            cout<<ncw[j].f.x<<" "<<ncw[j].f.y<<endl;
            j++;
            j=j%ncw.size();
            
        }
        else if(ncw[j].s==1)
        {
            traversesp(nsp,ncw,partial,ncw[j].f,visited);
            return;
        }
    }
}

void traversesp(vector<pair<point,int> > nsp,vector<pair<point,int> > ncw,vector<pair<point,int> > &partial,point p,vector<int> &visited)
{
    int i;
    for(i=0;i<nsp.size();++i)
    {
        if((int)nsp[i].f.x==(int)p.x&&(int)nsp[i].f.y==(int)p.y)
        {
            break;
        }
    }
    // if(i==10)
    // {
    //     i=2; 

    //     cout<<"\t\t\t"<<nsp[2].f.x-p.x<<" "<<nsp[2].f.y-p.y<<endl;
    // }
    if(visited[i]==1)
    {
        cout<<"\t\t\t"<<i<<endl;
        return;
    }
    partial.pb(nsp[i]);
    cout<<nsp[i].f.x<<" "<<nsp[i].f.y<<endl;
    visited[i]=1;
    int j=(i+1)%nsp.size();
    cout<<"\t\t"<<j<<endl;
    while(1)
    {
        // cout<<"@";
        if(visited[j]==1)
            return;
        if(nsp[j].s==0)
        {
            visited[j]=1;
            partial.pb(nsp[j]);
            cout<<nsp[j].f.x<<" "<<nsp[j].f.y<<endl;
            j++;
            j=j%nsp.size();
            
        }
        else if(nsp[j].s==1)
        {
            visited[j]=1;
            partial.pb(nsp[j]);
            cout<<nsp[j].f.x<<" "<<nsp[j].f.y<<endl;
            traversecw(nsp,ncw,partial,nsp[j].f,visited);
            return;
        }
    }
}
int main()
{
    int gd=DETECT,gm;
    initgraph(&gd,&gm,NULL);
    int m,n;
    // cout<<"Enter the size of the subject polygon\n";
    cin>>m;
    // cout<<"Enter the vertices of the subject polygon\n";
    point* sp=new point[m];
    for(int i=0;i<m;i++)
        cin>>sp[i].x>>sp[i].y;
    setlinestyle(3, 1, 1);
    for (int i=0; i < m; i++) {
        line(sp[i].x,sp[i].y,sp[(i+1)%m].x,sp[(i+1)%m].y);
    }
    // cout<<"Enter the size of the clipping window\n";
    cin>>n;
    // cout<<"Enter the vertices of the clipping window\n";
    point* cw=new point[n];
    for(int i=0;i<n;i++)
        cin>>cw[i].x>>cw[i].y;
    setcolor(14);
    for (int i=0; i < n; i++) {
        line(cw[i].x,cw[i].y,cw[(i+1)%n].x,cw[(i+1)%n].y);
    }
    vector <pair < point , int > > nsp;
    vector <pair < point , int > > ncw;
    for(int i=0;i<m;i++){
        point p1=sp[i];
        point p2=sp[(i+1)%m];
        // nsp.push_back(make_pair(p1,-1));
        vector<pair<point,int> > res=cyrusbeck(p1,p2,cw,n);
        for(float i=0;i<res.size();i++)
            nsp.push_back(res[i]);
    }
    for(int i=0;i<n;i++){
        point p1=cw[i];
        point p2=cw[(i+1)%n];
        // ncw.push_back(make_pair(p1,-1));
        vector<pair<point,int> >res=cyrusbeck(p1,p2,sp,m);
        for(float i=0;i<res.size();i++)
            ncw.push_back(res[i]);
    }
    cout<<'\n';
    for(float i=0;i<nsp.size();i++)
        cout<<nsp[i].first.x<<" "<<nsp[i].first.y<<" "<<nsp[i].second<<'\n';

    cout<<'\n';

    for(float i=0;i<ncw.size();i++)
        cout<<ncw[i].first.x<<" "<<ncw[i].first.y<<" "<<ncw[i].second<<'\n';

    vector<int> visited(nsp.size());
    vector<pair<point,int> > partial;
    cout<<endl;
    // cout<<nsp.size()<<" "<<ncw.size();
    for(int i=0;i<nsp.size();++i)
    {
        if(nsp[i].s==0 && visited[i]==0)
        {
            traversesp(nsp,ncw,partial,nsp[i].f,visited);
            setlinestyle(0, 1, 3);
            setcolor(2);
            for(int j=0;j<partial.size();++j)
            {
                cout<<partial[j].f.x<<" "<<partial[j].f.y<<endl;
                line(partial[j].f.x,partial[j].f.y,partial[(j+1)%partial.size()].f.x,partial[(j+1)%partial.size()].f.y);    
            }
            partial.clear();
        }
        visited[i]=1;
    }
    getch();
    closegraph();
    return 0;
}

/*
4
100 100
100 300
300 300
300 100
4
150 200
200 350
350 200
200 50
*/