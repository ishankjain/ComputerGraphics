#include<graphics.h>
#include<bits/stdc++.h>
// #include<conio.h>
#include<stdio.h>
using namespace std;

int main(){
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    // hermite curve equation   p(t)=2t3+4t2+10t+100
    // float Px,Py;
    // float t=-60;
    // while(t<=60 ){
    //     Py=(t*t*t-3600*t)/3000;
    //     Px=t+100;
    //     t+=0.1;
    //     putpixel((int)Px, 200- (int)Py, WHITE);
    //     putpixel((int)Px,300-(int)Py,WHITE);
    // }

    //circle drawing

        float t2=-60;

        while(t2<=60){
            int Py1=(t2*t2*t2-3600*t2)/3000;
            int Px1=t2+100;
            t2+=0.1;
            putpixel((int)Px1, 200- (int)Py1, WHITE);
            putpixel((int)Px1,300-(int)Py1,WHITE);
            putpixel((int)Px1,250-(int)Py1,RED);
        }    
        // t=-60;

    // float theta=0;

    // while(t<=60){

    //     Py=(int)(250-(t*t*t-3600*t)/3000);
    //     Px=(int)(t+100);
    //     t+=0.1;
    //     setcolor(WHITE);

    //     circle((int)Px,(int)Py,20);

    //     int rcos=20*cos(theta);
    //     int rsin=20*sin(theta);

    //     theta+=0.005;

    //     line(Px-rcos,Py-rsin,Px+rcos,Py+rsin);
    //     line(Px+rsin,Py-rcos,Px-rsin,Py+rcos);
    //     delay(10);
    //     //cleardevice();
    //     setcolor(BLACK);

    //     line(Px-rcos,Py-rsin,Px+rcos,Py+rsin);

    //     line(Px+rsin,Py-rcos,Px-rsin,Py+rcos);

    //     circle((int)Px,Py,20);
    // }





    delay(1000);
    getch();
    closegraph();

}