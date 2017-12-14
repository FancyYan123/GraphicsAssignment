#include "circle.h"
#include <math.h>

void Circle::Draw(){
    intPoint2D pos;
    pos.x=0;
    pos.y=r;
    double p=5.0/4+r;

    glBegin(GL_POINTS);
    drawSymPoints(pos);
    while(pos.x<pos.y){
        if(p<0){
            p = p+2*pos.x+3;
            pos.x += 1;
        }
        else{
            p = p+2*(pos.x+1)+3-2*pos.y-2;
            pos.y -= 1;
            pos.x += 1;
        }
        drawSymPoints(pos);
    }
    glEnd();
}

void Circle::setStart(int x, int y){
    start.x=x;
    start.y=y;
}

void Circle::setEnd(int x, int y){
    end.x=x;
    end.y=y;
    center.x = (start.x+end.x)/2;
    center.y = (start.y+end.y)/2;
    r = sqrt((start.x-end.x)*(start.x-end.x)+(start.y-end.y)*(start.y-end.y))/2.0;
}

void Circle::drawSymPoints(intPoint2D first){
    intPoint2D second;
    second.x=first.y;
    second.y=first.x;
    glVertex2i(first.x+center.x, first.y+center.y);
    glVertex2i(-first.x+center.x, first.y+center.y);
    glVertex2i(first.x+center.x, -first.y+center.y);
    glVertex2i(-first.x+center.x, -first.y+center.y);

    glVertex2i(second.x+center.x, second.y+center.y);
    glVertex2i(-second.x+center.x, second.y+center.y);
    glVertex2i(second.x+center.x, -second.y+center.y);
    glVertex2i(-second.x+center.x, -second.y+center.y);
}

void Circle::move(intPoint2D start, intPoint2D end){
    int shiftX = end.x - start.x;
    int shiftY = end.y - start.y;

    center.x += shiftX;
    center.y += shiftY;
}

bool Circle::pointInGraph(intPoint2D click){
    int distX = (click.x-center.x)*(click.x-center.x);
    int distY = (click.y-center.y)*(click.y-center.y);
    if(sqrt(distX+distY)<=r)
        return true;
    else
        return false;
}

Graph2D* Circle::mouseSelect(intPoint2D click){
    if(pointInGraph(click))
        return this;
    else
        return NULL;
}

void Circle::zoom(intPoint2D origin, intPoint2D scale){
    double standard = sqrt((origin.x-center.x)*(origin.x-center.x)+(origin.y-center.y)*(origin.y-center.y));
    double scaled = sqrt((scale.x-center.x)*(scale.x-center.x)+(scale.y-center.y)*(scale.y-center.y));

    r = r*scaled/standard;
}

void Circle::rotate(intPoint2D start, intPoint2D end){
    //现阶段只有绕重心旋转，圆旋转后还是圆
    return;
}

void Circle::fill(){

}
