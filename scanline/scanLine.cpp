#include<stdio.h> 
#include<stdlib.h> 
#include<graphics.h> 
#include<math.h>	
// #include"circle.c"
// #include"line.c"
// #include"wait.c"
#include<bits/stdc++.h>
using namespace std;
#define f first
#define s second	
#define pb push_back
struct edge{
	float y,x,slope;
	bool operator < (edge it)
	{
		return x<it.x;
	}
};
vector<vector<edge> > global;
vector<edge> active; 
bool f(edge e1,edge e2)
{
	return e1.x<e2.x;
}
int  main()
{
	int gd=DETECT,gm;
    initgraph(&gd,&gm,NULL);
    int n;

    cout << "Enter the no. of edges of polygon : ";
    cin >> n;
    cout << "Enter the co-ordinates of polygon :\n";
    vector<pair<float,float> >vertices(n+1);
    float maxy=0;
    for (int i = 0; i < n; i++) {
       	cout<<i<<":";
       	cin>>vertices[i].f>>vertices[i].s;
       	if(vertices[i].s>maxy)
       		maxy=vertices[i].s;
    }
    vertices[n].f=vertices[0].f;
   	vertices[n].s=vertices[0].s;
   	global.resize(maxy+1);
    /* draw polygon */
    for (int i = 0; i < n; i++) {
        line(vertices[i].f,vertices[i].s,vertices[i+1].f,vertices[i+1].s);
        edge t;
        float dx=vertices[i].f-vertices[i+1].f;
        float dy=vertices[i].s-vertices[i+1].s;
        if(dx==0)
        	t.slope=0;
        else if(dy==0)
        	t.slope=INT_MAX;
        else
        	t.slope=(float)(dx/dy);
        if(vertices[i].s<=vertices[i+1].s)
        {
        	t.y=vertices[i+1].s;
        	t.x=vertices[i].f;
        	global[vertices[i].s].pb(t);
        }
        else
        {
        	t.y=vertices[i].s;
        	t.x=vertices[i+1].f;
        	global[vertices[i+1].s].pb(t);	
        }
    }
    delay(2000);
    // cout<<global.size()<<endl;
	for(int i=0;i<=maxy;++i)
	{
		// cout<<global[i].size();
		for(int j=0;j<active.size();++j)
		{
			if(active[j].y==i)
			{
				active.erase(active.begin()+j);
				j--;
			}
		}
		for(int j=0;j<global[i].size();++j)
		{
			active.push_back(global[i][j]);
			// cout<<active.size();
		}
		sort(active.begin(), active.end(),f);
		for(int j=0;j<active.size()&&(j+1)<active.size();j+=2)
		{
			setcolor(RED);
			line(round(active[j].x),i,round(active[j+1].x),i);
		}
		for(int j=0;j<active.size();j++)
		{
			active[j].x+=active[j].slope;
		}
	}
	for (int i = 0; i < n; i++) {
        line(vertices[i].f,vertices[i].s,vertices[i+1].f,vertices[i+1].s);
    }
	delay(20000);
	closegraph();
	return 0; 
}