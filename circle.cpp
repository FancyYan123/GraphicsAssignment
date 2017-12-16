#include "circle.h"
#include <math.h>

void Circle::Draw(drawBoardBuffer* drawBoard){
    intPoint2D pos;
    pos.x=0;
    pos.y=r;
    double p=5.0/4+r;

    //glBegin(GL_POINTS);
    drawSymPoints(pos, drawBoard);
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
        drawSymPoints(pos, drawBoard);
    }
    //glEnd();
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

void Circle::drawSymPoints(intPoint2D first, drawBoardBuffer* drawBoard){
    intPoint2D second;
    second.x=first.y;
    second.y=first.x;
    drawBoard->drawPoint(first.x+center.x, first.y+center.y);
    drawBoard->drawPoint(-first.x+center.x, first.y+center.y);
    drawBoard->drawPoint(first.x+center.x, -first.y+center.y);
    drawBoard->drawPoint(-first.x+center.x, -first.y+center.y);

    drawBoard->drawPoint(second.x+center.x, second.y+center.y);
    drawBoard->drawPoint(-second.x+center.x, second.y+center.y);
    drawBoard->drawPoint(second.x+center.x, -second.y+center.y);
    drawBoard->drawPoint(-second.x+center.x, -second.y+center.y);
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


void Circle::fill(drawBoardBuffer* drawBoard){
//    fill4way(center.x, center.y, drawBoard);
    intPoint2D left(center.x, center.y);
    while(!drawBoard->isPointDrawn(left.x, left.y)){
        drawBoard->drawPoint(left.x, left.y);
        intPoint2D Up(left.x, left.y+1);
        intPoint2D Down(left.x, left.y-1);
        while(!drawBoard->isPointDrawn(Up.x, Up.y)){
            drawBoard->drawPoint(Up.x, Up.y);
            Up.y++;
        }
        while(!drawBoard->isPointDrawn(Down.x, Down.y)){
            drawBoard->drawPoint(Down.x, Down.y);
            Down.y--;
        }
        left.x--;
    }
    intPoint2D right(center.x+1, center.y);
    while(!drawBoard->isPointDrawn(right.x, right.y)){
        drawBoard->drawPoint(right.x, right.y);
        intPoint2D Up(right.x, right.y+1);
        intPoint2D Down(right.x, right.y-1);
        while(!drawBoard->isPointDrawn(Up.x, Up.y)){
            drawBoard->drawPoint(Up.x, Up.y);
            Up.y++;
        }
        while(!drawBoard->isPointDrawn(Down.x, Down.y)){
            drawBoard->drawPoint(Down.x, Down.y);
            Down.y--;
        }
        right.x++;
    }
}
