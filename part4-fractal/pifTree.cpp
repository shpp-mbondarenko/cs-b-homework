#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "strlib.h"
#include "gwindow.h"
#include "math.h"
#define M_PI 3.1415926535897932384626433832795
using namespace std;
void drawTree(GWindow w, GPoint p1, GPoint p2, double len, int angle,int n);

int main() {

    GWindow gw;
    gw.setSize(700.0,550.0);
    GPoint p1 = gw.drawPolarLine(300, 500, 100, 90);
    GPoint p2 = gw.drawPolarLine(400, 500, 100, 90);
    gw.drawLine(p2, p1);
    gw.drawLine(300,500,400,500);
    drawTree(gw,p1,p2,100.0,45,13);
    return 0;
}

void drawTree(GWindow gw, GPoint p1, GPoint p2, double len, int angle,int n){

    double trueLen = len*0.7071;
    GPoint rightLong = gw.drawPolarLine(p1, trueLen*2, angle); //long line
    GPoint rightShort = gw.drawPolarLine(p2, trueLen, angle);
    gw.drawLine(rightLong, rightShort);
    GPoint leftLong = gw.drawPolarLine(p2, trueLen*2, angle+90); //long line
    GPoint leftShort = gw.drawPolarLine(p1, trueLen, angle+90);
    gw.drawLine(leftLong, leftShort);
    n--;
    if(n==0){
              return;
    }
    angle = angle - 45;
    drawTree(gw, rightLong, rightShort, trueLen, angle, n);
    angle = angle + 90;
    drawTree(gw,leftShort,leftLong, trueLen, angle, n);


}
