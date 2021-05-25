#include <graphics.h>
#include <iostream>
#include <cmath>

typedef struct Point {
    float x, y;
} point;
typedef struct List {
    point k;
    struct List *next;
} list;
point d{300, 100}, c{400, 200}, b{200, 200}, a{300, 300};
point f{400, 200}, g{300, 300}, h{300, 100}, j{200, 200};

void waitForLeftMouseClick() {
    clearmouseclick(WM_LBUTTONDOWN);
    const int DELAY = 50; // Milliseconds of delay between checks
    int x, y;
    while (!ismouseclick(WM_LBUTTONDOWN))
        delay(DELAY);
    getmouseclick(WM_LBUTTONDOWN, x, y);
}

void lerp(point & dest, const point& a, const point& b, const float t){
    dest.x = a.x + (b.x - a.x) * t;
    dest.y = a.y + (b.y - a.y) * t;
}

void bezier(point &dest, const point& a, const point& b,const point& c, const point& d,const float t){
    point ab, bc, cd, abbc, bccd, cdde;
    lerp(ab, a, b, t); // point between a and b
    lerp(bc, b, c, t); // point between b and c
    lerp(cd, c, d, t); // point between c and d
    lerp(abbc, ab, bc, t); // point between ab and bc
    lerp(bccd, bc, cd, t);// point between bc and cd
    lerp(dest, abbc, bccd, t); // point on the bezier-curve
}

void rot(float *a, float *b, int xc, int yc, double alfa) {
    double cosa = cos(alfa), sina = sin(alfa);
    int x = *a, y = *b;
    int xr, yr;
    xr = xc + (x - xc) * cosa - (y - yc) * sina;
    yr = yc + (x - xc) * sina + (y - yc) * cosa;
    *a = xr;
    *b = yr;
}

int main() {
    initwindow(600, 600);
    int xc = (int) a.x;
    int yc = (int) a.y + (d.y - a.y) / 2;
    setcolor(YELLOW);
    setwritemode(XOR_PUT);
    point a1 = a, bt = b, ct = c, dt = d, ft = f, gt = g, ht = h, jt = j;
    double alfa = 0;
    while (1) {
        rot(&a1.x, &a1.y, xc, yc, alfa);
        rot(&bt.x, &bt.y, xc, yc, alfa);
        rot(&ct.x, &ct.y, xc, yc, alfa);
        rot(&dt.x, &dt.y, xc, yc, alfa);
        rot(&ft.x, &ft.y, xc, yc, alfa);
        rot(&gt.x, &gt.y, xc, yc, alfa);
        rot(&ht.x, &ht.y, xc, yc, alfa);
        rot(&jt.x, &jt.y, xc, yc, alfa);
        line(dt.x, dt.y, a1.x, a1.y);
        line(ft.x, ft.y, jt.x, jt.y);
        for (int i = 0; i < 100; ++i) {
            point p;
            float t = static_cast<float>(i) / 99.0;
            bezier(p, a1, bt, ct, dt, t);
            putpixel(p.x, p.y, YELLOW);
            bezier(p, ft, gt, ht, jt, t);
            putpixel(p.x, p.y, YELLOW);
        }
        delay(5);
        for (int i = 0; i < 100; ++i) {
            point p;
            float t = static_cast<float>(i) / 99.0;
            bezier(p, a1, bt, ct, dt, t);
            putpixel(p.x, p.y, YELLOW);
            bezier(p, ft, gt, ht, jt, t);
            putpixel(p.x, p.y, YELLOW);
        }
        line(dt.x, dt.y, a1.x, a1.y);
        line(ft.x, ft.y, jt.x, jt.y);
        a1 = a;
        bt = b;
        ct = c;
        dt = d;
        ft = f;
        gt = g;
        ht = h;
        jt = j;
        alfa -= 0.02;
    }
    while (!kbhit()) {
        delay(1);
    }
    waitForLeftMouseClick();
    return 0;
}
