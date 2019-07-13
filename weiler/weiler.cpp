#include <bits/stdc++.h>
#include <graphics.h>

using namespace std;

float sdx[15],sdy[15];
int i,w=0,h;

void sort(float sdy[],int h)
{
    float temp;
    for(int j=0;j<=h-1;j++)
    {
        for(i=0;i<h-1-j;i++)
        {
            if(sdy[i]>sdy[i+1])
            {
                temp=sdy[i];
                sdy[i]=sdy[i+1];
                sdy[i+1]=temp;
            }
        }
    }
}

struct points
{
    float x;
    float y;
    float io;
    float vis;
};
struct points z[20];

int main()
{
    // initwindow(640, 480);
    int gd=DETECT,gm;
    initgraph(&gd,&gm,NULL);

    int n,m,s;
    float px[15]={0};
    float py[15]={0};
    float pdx[15],pdy[15];
    float outx[15]={0};
    float outy[15]={0};
    float xmin,ymin,xmax,ymax;

    cout<<"\nEnter xmin,ymin,xmax,ymax: ";
    cin>>xmin>>ymin>>xmax>>ymax;

    setcolor(YELLOW);
    rectangle(xmin,ymax,xmax,ymin);

    cout<<"\nEnter the no. of vertices (n): ";
    cin>>n;
    cout<<"\nEnter the x coordinate of all vertices: ";

    for(m=0;m<n;m++)
    {  cin>>px[m];  }
    // cout<<"\nEnter the y coordinate of all vertices: ";
    cout<<"\nEnter the y coordinate of all vertices: ";
    for(m=0;m<n;m++)
    {
        cin>>py[m];
    }

    setcolor(GREEN);
    px[n]=px[0];py[n]=py[0];
    for(s=0;s<n;s++)
    {  line(px[s],py[s],px[s+1],py[s+1]);  }

    // getch();
    // cleardevice();
    // getch();
    int l=0;
    for(m=0;m<n;m++)
    {
        if(px[m]>=xmin && px[m+1]<=xmin)
        {
            pdx[m]=xmin;
            pdy[m]=py[m]+((py[m+1]-py[m])/(px[m+1]-px[m]))*(xmin-px[m]);
            outx[l]=pdx[m];outy[l]=pdy[m];
            z[l].io=1;
            l++;
        }
        if(px[m]>=xmin && px[m+1]>=xmin)
        {
            outx[l]=px[m+1];outy[l]=py[m+1];
            z[l].io=0;
            l++;
        }
        if(px[m]<=xmin && px[m+1]>=xmin)
        {
            pdx[m]=xmin;
            pdy[m]=py[m]+((py[m+1]-py[m])/(px[m+1]-px[m]))*(xmin-px[m]);
            outx[l]=pdx[m];outy[l]=pdy[m];
            z[l].io=0;
            l++;
            outx[l]=px[m+1];outy[l]=py[m+1];
            z[l].io=0;
            l++;
        }
    }

    outx[l]=outx[0];outy[l]=outy[0];
    setcolor(RED);
    rectangle(xmin,ymax,xmax,ymin);
    setcolor(BLUE);

    for(i=0;i<l;i++)
    {
        if(outx[i]==xmin)
        {
            sdx[w]=outx[i];
            sdy[w]=outy[i];
            w++;
        }
    }

    sort(sdy,w);
    outx[l]=outx[0];outy[l]=outy[0];
    for(i=0;i<=l;i++)
    {
        z[i].x=outx[i];
        z[i].y=outy[i];
        z[i].vis=0;
    }
    s=0;
    for(m=0;m<=l-1;m++)
    {
        outx[l]=outx[0];outy[l]=outy[0];
        sdx[w+1]=sdx[0];sdy[w+1]=sdy[0];

        if(z[s].io==0)
        {
            line(outx[s],outy[s],outx[s+1],outy[s+1]);
            z[s].vis=1;
            z[s+l].vis=1;
        }
        else if(z[s].io==1)
        {
            for(i=0;i<=w;i++)
            {
                if(sdy[i]==outy[s])
                {
                    line(sdx[i],sdy[i],sdx[i+1],sdy[i+1]);
                    z[s].vis=1;
                    z[s+l].vis=1;
                    break;
                }
            }
            for(int j=0;j<l;j++)
            {
                if(sdy[i+1]==z[j].y)
                {
                    s=j;
                    line(outx[s],outy[s],outx[s+1],outy[s+1]);
                    z[s].vis=1;
                    z[s+l].vis=1;
                    break;
                }
            }
        }
        if(s<=l-1)
        {
            s++;
        }
        else
        {
            s=0;
        }
        if(s==l)
        {
            s=0;
        }

        int p=s;
        while(z[s].vis == 1)
        {
            s++;
            if(s==p+l)
            {
                break;
            }
        }
    }

    getch();
    closegraph();
    return 0;
}