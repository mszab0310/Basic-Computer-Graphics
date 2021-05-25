#include <graphics.h>
#include <ctime>
#include <iostream>
struct punct{int x,y;};
void BresGeneral(int, int, int, int);
punct waitForLeftMouseClick();
int culoareCreion = GREEN;
int culoareHartie = WHITE;
int latp = 10;
void patr(int i,int j){
// determin pozitia in grila
    int xp,yp;
    xp = 50 + i*latp;
    yp = 50 + j*latp;
// determin culoarea celulei
    if(getpixel(xp+1,yp+1)==BLACK) setcolor(YELLOW);
    else setcolor(BLACK);
    for(int k=1;k<latp;k++)
        line(xp+k,yp+1,xp+k,yp+latp);
    setcolor(GREEN);
}
int main(){
    punct A,B;
    int maxcolor = getmaxcolor() + 1;
    srand(time(0));
    initwindow(620,620);
    for(int i=0;i<=50;i++) line(50,50+i*latp,550,50+i*latp);
    for(int j=0;j<=50;j++) line(50+j*latp,50,50+j*latp,550);
    while(1){
        A = waitForLeftMouseClick();
        B = waitForLeftMouseClick();
        if(A.x >= 550 || A.y >= 550 || B.x >= 550 || B.y >= 550){
            ;
        }else{
            int xb,xa,yb,ya;
            xa = (A.x-50)/latp;
            xb = (B.x-50)/latp;
            ya = (A.y-50)/latp;
            yb = (B.y-50)/latp;
            // alege o culoare
            culoareCreion = rand()%maxcolor+1;
            // traseaza segmentul AB
            BresGeneral(xa, ya, xb, yb);
            setcolor(culoareCreion);
            int xap,yap,xbp,ybp;
            xap = 55 + xa*latp;
            yap = 55 + ya*latp;
            xbp = 55 + xb*latp;
            ybp = 55 + yb*latp;
            setcolor(BLUE);
            line(xap,yap,xbp,ybp);
        }
    }
    //system("PAUSE");
}
punct waitForLeftMouseClick()
{
    clearmouseclick(WM_LBUTTONDOWN);
    const int DELAY = 50; // Milliseconds of delay between checks
    punct p;
    while (!ismouseclick(WM_LBUTTONDOWN))
        delay(DELAY);
    getmouseclick(WM_LBUTTONDOWN, p.x, p.y);
    return p;
}
// Bresenham generalizat
void BresGeneral(int x1, int y1, int x2, int y2){
    int oct, dx,dy, absdx, absdy,c1,c2,t;
    int culoare = culoareCreion;
    int x,y,i;
    dx=x2-x1;
    dy=y2-y1;
    absdx=abs(dx); absdy=abs(dy);
    if(dx>0) // oct=1,2,7,8
    { if(dy>0) // oct 1,2
            if(dx>=dy) oct=1; else oct=2;
        else
        if(dx>=absdy) oct=8; else oct=7;
    }
    else // 3,4,5,6
    { if(dy>0) // oct 3,4
            if(absdx>=dy) oct=4; else oct=3;
        else
        if(absdx>=absdy) oct=5; else oct=6;
    }
    if(absdy>absdx)
    { x=absdx; absdx=absdy; absdy=x; }
    c1=absdy<<1;
    c2=c1-(absdx<<1);
    t=c1-absdx;
    patr(x1,y1);
//putpixel(x1,y1,culoare);
    for(i=1, x=x1, y=y1; i<absdx; i++)
    { if(t<0) // deplasament O
        { t+=c1;
            switch(oct){
                case 1:
                case 8:x++;break;
                case 4:
                case 5:x--;break;
                case 2:
                case 3:y++;break;
                case 6:
                case 7:y--;break;
            }
        }
        else
        { t+=c2; // deplasament D
            switch(oct){
                case 1:
                case 2:x++;y++;break;
                case 3:
                case 4:x--;y++;break;
                case 5:
                case 6:x--;y--;break;
                case 7:
                case 8:x++;y--;break;
            }
        }
        patr(x,y);
//putpixel(x,y,culoare);
    }
    patr(x2,y2);
//putpixel(x2,y2,culoare);
}
