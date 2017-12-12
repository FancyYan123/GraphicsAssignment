#include "line.h"
#include <math.h>
#include <assert.h>

//斜率绝对值大于1时：
void Line::bresenhamk1(double k){
    assert(k > 1 || k<-1);
    int dx = abs(startPos.x - endPos.x);
    int dy = abs(startPos.y - endPos.y);
    int x, y, endy;
    int delta1 = 2 * dx;
    int delta2 = 2 * (dx - dy);
    int p = 2 * dx - dy;
    int step = k > 0 ? 1 : -1;

    if (startPos.y < endPos.y){
        x = startPos.x;
        y = startPos.y;
        endy = endPos.y;
    }
    else{
        x = endPos.x;
        y = endPos.y;
        endy = startPos.y;
    }

    glBegin(GL_POINTS);
    glVertex2i(x, y);
    while (y < endy){
        y++;
        if (p < 0){
            p += delta1;
        }
        else{
            x += step;
            p += delta2;
        }
        glVertex2i(x, y);
    }
    glEnd();
//	glFlush();
}

//斜率大于等于-1小于等于1时：
void Line::bresenhamk2(double k){

    assert(k >= -1 && k <= 1);
    int dx = abs(startPos.x - endPos.x);
    int dy = abs(startPos.y - endPos.y);
    int x, y, endx;
    int delta1 = 2 * dy;
    int delta2 = 2 * (dy - dx);
    int p = 2 * dy - dx;
    int step = k > 0 ? 1 : -1;

    if (startPos.x < endPos.x){
        x = startPos.x;
        y = startPos.y;
        endx = endPos.x;
    }
    else{
        x = endPos.x;
        y = endPos.y;
        endx = startPos.x;
    }

    glBegin(GL_POINTS);
    glVertex2i(x, y);
    while (x < endx){
        x++;
        if (p < 0){
            p += delta1;
        }
        else{
            y += step;
            p += delta2;
        }
        glVertex2i(x, y);
    }
    glEnd();
//	glFlush();
}



void Line::Draw(){
    if (startPos.x != endPos.x){
        double k = (startPos.y - endPos.y + 0.0) / (startPos.x - endPos.x + 0.0);
        if (fabs(k)>1)
            bresenhamk1(k);
        else
            bresenhamk2(k);
    }

    else if (startPos.x == endPos.x && startPos.y == endPos.y)
        return;

    else{
        int x = startPos.x;
        int y = startPos.y < endPos.y ? startPos.y : endPos.y;
        int endy = startPos.y > endPos.y ? startPos.y : endPos.y;
        glBegin(GL_POINTS);
        while (y < endy){
            glVertex2i(x, y);
            y++;
        }
        glEnd();
    }
}

bool Line::onLeftDown(int x, int y){
    int A = endPos.y-startPos.y;
    int B = startPos.x-endPos.x;
    int C = startPos.y*endPos.x - endPos.y*startPos.x;

    int temp = A*x+B*y+C;
    if(temp<=0&&B>0)
        return true;
    else if(temp>=0&&B<0)
        return true;
    else if(temp<=0&&B==0&&A>0)
        return true;
    else if(temp>=0&&B==0&&A<0)
        return true;
    else
        return false;

}

void Line::move(intPoint2D start, intPoint2D end){
    int shiftX = end.x - start.x;
    int shiftY = end.y - start.y;

    startPos.x += shiftX;
    startPos.y += shiftY;
    endPos.x += shiftX;
    endPos.y += shiftY;
}

Graph2D* Line::mouseSelect(intPoint2D click){
    int x_max = startPos.x>endPos.x?startPos.x:endPos.x;
    int x_min = startPos.x<endPos.x?startPos.x:endPos.x;
    int y_max = startPos.y>endPos.y?startPos.y:endPos.y;
    int y_min = startPos.y<endPos.y?startPos.y:endPos.y;

    if(click.x<x_min || click.x>x_max)
        return NULL;
    if(click.y<y_min || click.y>y_max)
        return NULL;

    int A = endPos.y-startPos.y;
    int B = startPos.x-endPos.x;
    int C = startPos.y*endPos.x - endPos.y*startPos.x;

    double dist = abs(A*click.x+B*click.y+C)/sqrt(A*A+B*B);
    if(dist<5.0)
        return this;

    return NULL;
}

void Line::zoom(intPoint2D origin, intPoint2D scale){
    intPoint2D center((startPos.x+endPos.x)/2, (startPos.y+endPos.y)/2);
    double standard = sqrt((origin.x-center.x)*(origin.x-center.x)+(origin.y-center.y)*(origin.y-center.y));
    double scaled = sqrt((scale.x-center.x)*(scale.x-center.x)+(scale.y-center.y)*(scale.y-center.y));

    double s = scaled/standard;
    //应用缩放公式，假设不动点是（xf, yf）:
    //x = x*s + xf(1-s);    y = y*s + yf(1-s);
    startPos.x = startPos.x*s + center.x*(1-s);
    startPos.y = startPos.y*s + center.y*(1-s);
    endPos.x = endPos.x*s + center.x*(1-s);
    endPos.y = endPos.y*s + center.y*(1-s);
}

void Line::rotate(intPoint2D start, intPoint2D end){
    intPoint2D center((startPos.x+endPos.x)/2, (startPos.y+endPos.y)/2);
    double SIN = getAngleSin(start, end, center);
    double COS = getAngleCos(start, end, center);

    startPos.x = center.x + (startPos.x-center.x)*COS - (startPos.y-center.y)*SIN;
    startPos.y = center.y + (startPos.x-center.x)*SIN + (startPos.y-center.y)*COS;

    endPos.x = center.x + (endPos.x-center.x)*COS - (endPos.y-center.y)*SIN;
    endPos.y = center.y + (endPos.x-center.x)*SIN + (endPos.y-center.y)*COS;
}
