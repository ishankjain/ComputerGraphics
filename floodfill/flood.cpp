#include <graphics.h>
#include <stdio.h>
#include<bits/stdc++.h>
using namespace std;
#define f first
#define s second	
#define pb push_back
void flood(int x, int y, int new_col, int old_col) {
if (getpixel(x, y) == old_col) {
putpixel(x, y, new_col);
 flood(x + 1, y, new_col, old_col);
 flood(x - 1, y, new_col, old_col);
 flood(x, y + 1, new_col, old_col);
 flood(x, y - 1, new_col, old_col);
 }
}
int main() {
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
   	for (int i = 0; i < n; i++) {
        line(vertices[i].f,vertices[i].s,vertices[i+1].f,vertices[i+1].s);
    }
    int x=(vertices[0].f+vertices[2].f)/2;
    int y=(vertices[0].s+vertices[2].s)/2;
	int newcolor = BLUE;
	int oldcolor = 0;
 	flood(x, y, newcolor, oldcolor);
 	getch();
	return 0;
}