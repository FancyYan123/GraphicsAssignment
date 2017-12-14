#include "rect.h"
#include "line.h"
#include <math.h>

#include<iostream>
using namespace std;

void Rect::Draw()
{
    Line Up(leftUp, rightUp);
    Line Right(rightUp, rightDown);
    Line Down(rightDown, leftDown);
    Line Left(leftDown, leftUp);

    Up.Draw();
    Right.Draw();
    Down.Draw();
    Left.Draw();

}

void Rect::move(intPoint2D start, intPoint2D end){
    int shiftX=end.x-start.x;
    int shiftY=end.y-start.y;

    leftUp.x += shiftX; rightUp.x+=shiftX;
    leftUp.y += shiftY; rightUp.y+=shiftY;
    rightDown.x += shiftX;  leftDown.x+=shiftX;
    rightDown.y += shiftY;  leftDown.y+=shiftY;
}

void Rect::zoom(intPoint2D origin, intPoint2D scale){
    intPoint2D center((leftUp.x+rightDown.x)/2, (leftUp.y+rightDown.y)/2);
    double standard = sqrt((origin.x-center.x)*(origin.x-center.x)+(origin.y-center.y)*(origin.y-center.y));
    double scaled = sqrt((scale.x-center.x)*(scale.x-center.x)+(scale.y-center.y)*(scale.y-center.y));

    double s = scaled/standard;

    leftUp.x = leftUp.x*s + center.x*(1-s);
    leftUp.y = leftUp.y*s + center.y*(1-s);
    rightDown.x = rightDown.x*s + center.x*(1-s);
    rightDown.y = rightDown.y*s + center.y*(1-s);

    leftDown.x = leftDown.x*s + center.x*(1-s);
    leftDown.y = leftDown.y*s + center.y*(1-s);
    rightUp.x = rightUp.x*s + center.x*(1-s);
    rightUp.y = rightUp.y*s + center.y*(1-s);
}

Graph2D* Rect::mouseSelect(intPoint2D click){
//    int x_max = leftUp.x>rightDown.x?leftUp.x:rightDown.x;
//    int x_min = leftUp.x<rightDown.x?leftUp.x:rightDown.x;
//    int y_max = leftUp.y>rightDown.y?leftUp.y:rightDown.y;
//    int y_min = leftUp.y<rightDown.y?leftUp.y:rightDown.y;

//    if(click.x<x_min || click.x>x_max)
//        return NULL;
//    if(click.y<y_min || click.y>y_max)
//        return NULL;

//    return this;

    Line Up(leftUp, rightUp);
    Line Right(rightUp, rightDown);
    Line Down(rightDown, leftDown);
    Line Left(leftDown, leftUp);

    if(Up.onLeftDown(click.x, click.y)!=Down.onLeftDown(click.x, click.y) &&
            Left.onLeftDown(click.x, click.y)!=Right.onLeftDown(click.x, click.y))
        return this;
    else
        return NULL;

}

void Rect::rotate(intPoint2D start, intPoint2D end){
    intPoint2D center((leftUp.x+rightDown.x)/2, (leftUp.y+rightDown.y)/2);
    double SIN = getAngleSin(start, end, center);
    double COS = getAngleCos(start, end, center);

    leftUp.x = center.x + (leftUp.x-center.x)*COS - (leftUp.y-center.y)*SIN;
    leftUp.y = center.y + (leftUp.x-center.x)*SIN + (leftUp.y-center.y)*COS;

    leftDown.x = center.x + (leftDown.x-center.x)*COS - (leftDown.y-center.y)*SIN;
    leftDown.y = center.y + (leftDown.x-center.x)*SIN + (leftDown.y-center.y)*COS;

    rightUp.x = center.x + (rightUp.x-center.x)*COS - (rightUp.y-center.y)*SIN;
    rightUp.y = center.y + (rightUp.x-center.x)*SIN + (rightUp.y-center.y)*COS;

    rightDown.x = center.x + (rightDown.x-center.x)*COS - (rightDown.y-center.y)*SIN;
    rightDown.y = center.y + (rightDown.x-center.x)*SIN + (rightDown.y-center.y)*COS;
}
