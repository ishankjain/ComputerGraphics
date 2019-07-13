#include<graphics.h>
#include<bits/stdc++.h>

using namespace std;

int main()
{
    int gd=DETECT,gm;
    initgraph(&gd,&gm,NULL);
    // initwindow(700, 480);

    int p[4][8] = {     {-40,40,40,-40,-20,20,20,-20},
                        {40,40,-40,-40,20,20,-20,-20},
                        {0,0,0,0,60,60,60,60},
                        {1,1,1,1,1,1,1,1}   };

    float pr[4][8];
    int i, j, k, page = 0;
    float q = 0.0, sum = 0, d = 0;
    // settextstyle(8, HORIZ_DIR, 1);

    for(i=0;i<10;++i)
    {
        // setactivepage(page);    setvisualpage(1 - page);    
        cleardevice();
        q=((d*(22/7.0))/180.0);
        float rotatez[4][4]={   {cos(q), -sin(q), 0, 0},
                                {sin(q), cos(q), 0, 0},
                                {0, 0, 1, 0},
                                {0, 0, 0, 1}   };

        for (i = 0; i <= 3; i++) {
            for (j = 0; j <= 8; j++) {
                sum = 0;
                for (k = 0; k <= 3; k++) {
                    sum += rotatez[i][k] * p[k][j];
                }
                pr[i][j] = sum;
            }
        }

        //top view
        outtextxy(68, 100, "Top View");
        for(i=0;i<4;i++) {
            line(115+pr[0][i],240-pr[1][i],115+pr[0][(i+1)%4],240-pr[1][(i+1)%4]);
            line(115+pr[0][i+4],240-pr[1][i+4],115+pr[0][(i+1)%4+4],240-pr[1][(i+1)%4+4]);
            line(115+pr[0][i],240-pr[1][i],115+pr[0][i+4],240-pr[1][i+4]);
        }
        line(230, 0, 230, getmaxy());

        //front view
        outtextxy(290, 100, "Front View");
        for(i=0;i<4;i++) {
            line(350+pr[0][i],265-pr[2][i],350+pr[0][(i+1)%4],265-pr[2][(i+1)%4]);
            line(350+pr[0][i+4],265-pr[2][i+4],350+pr[0][(i+1)%4+4],265-pr[2][(i+1)%4+4]);
            line(350+pr[0][i],265-pr[2][i],350+pr[0][i+4],265-pr[2][i+4]);
        }
        line(460, 0, 460, getmaxy());

        //side view
        outtextxy(535, 100, "Side View");
        for(i=0;i<4;i++) {
            line(550+pr[2][i],240-pr[1][i],550+pr[2][(i+1)%4],240-pr[1][(i+1)%4]);
            line(550+pr[2][i+4],240-pr[1][i+4],550+pr[2][(i+1)%4+4],240-pr[1][(i+1)%4+4]);
            line(550+pr[2][i],240-pr[1][i],550+pr[2][i+4],240-pr[1][i+4]);
        }

        page = 1 - page,    d++;
        delay(20);
    }

   getch();
   closegraph();
   return 0;
}

