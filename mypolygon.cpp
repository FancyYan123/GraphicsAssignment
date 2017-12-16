#include "mypolygon.h"
#include <iostream>
#include <assert.h>
using namespace std;

void MyPolygon::Draw(drawBoardBuffer* drawBoard)
{
    if(PolyVertex.size()>1){
        list<intPoint2D*>::iterator first = PolyVertex.begin();
        list<intPoint2D*>::iterator second = ++PolyVertex.begin();
        while(second!=PolyVertex.end()){
            Line temp(*first, *second);
            temp.Draw(drawBoard);
            first++;
            second++;
        }
        Line temp(*first, *PolyVertex.begin());
        temp.Draw(drawBoard);
    }
}

void MyPolygon::move(intPoint2D start, intPoint2D end){
    int shiftX=end.x-start.x;
    int shiftY=end.y-start.y;

    for(list<intPoint2D*>::iterator index=PolyVertex.begin(); index!=PolyVertex.end(); index++){
        (*index)->x += shiftX;
        (*index)->y += shiftY;
    }
    if(innerPoint!=NULL){
        innerPoint->x+=shiftX;
        innerPoint->y+=shiftY;
    }
}

void MyPolygon::zoom(intPoint2D origin, intPoint2D scale){
    intPoint2D center((*PolyVertex.begin())->x, (*PolyVertex.begin())->y);
    double standard = sqrt((origin.x-center.x)*(origin.x-center.x)+(origin.y-center.y)*(origin.y-center.y));
    double scaled = sqrt((scale.x-center.x)*(scale.x-center.x)+(scale.y-center.y)*(scale.y-center.y));

    double s = scaled/standard;

    for(list<intPoint2D*>::iterator index=PolyVertex.begin(); index!=PolyVertex.end(); index++){
        (*index)->x = (*index)->x*s + center.x*(1-s);
        (*index)->y = (*index)->y*s + center.y*(1-s);
    }
    if(innerPoint!=NULL){
        innerPoint->x = innerPoint->x*s + center.x*(1-s);
        innerPoint->y = innerPoint->y*s + center.y*(1-s);
    }
}

void MyPolygon::rotate(intPoint2D start, intPoint2D end){
    //TODO: ADD CODE FOR ROTATING HERE!
    return;
}



void MyPolygon::fillVerticalLine(int x, drawBoardBuffer* drawBoard){
    list<intPoint2D*>::iterator first = PolyVertex.begin();
    list<intPoint2D*>::iterator second = ++PolyVertex.begin();
    list<int> intersections;

    while(first!=PolyVertex.end()){
        bool cond1=((*first)->x<=x) && (x<=(*second)->x);
        bool cond2=((*second)->x<=x) && (x<=(*first)->x);
        if(cond1||cond2){
            double slope = double((*second)->y-(*first)->y)/((*second)->x-(*first)->x);
            int y=slope*(x-(*first)->x) + (*first)->y;
            intersections.push_back(y);
        }
        first++;
        second++;
        if(second==PolyVertex.end())
            second=PolyVertex.begin();
    }
    intersections.sort();
    //sort(intersections.begin(), intersections.end());
    //当有奇数个交点的时候，一定有相同的点（对应图像的顶点）
    if(intersections.size()%2!=0){
        list<int>::iterator index1=intersections.begin();
        list<int>::iterator index2=++intersections.begin();
        while(index2!=intersections.end()){
            if(*index1==*index2){
                list<int>::iterator index_temp=index2;
                index2++;
                intersections.erase(index_temp);
            }
            else{
                index1++; index2++;
            }
        }
    }
    if(intersections.size()!=0){
        list<int>::iterator pos1=intersections.begin();
        list<int>::iterator pos2=++intersections.begin();
        while(pos2!=intersections.end()){
            for(int i=*pos1; i<*pos2; i++)
                drawBoard->drawPoint(x, i);
            if(++pos2!=intersections.end()){
                pos1++; pos1++;
                pos2++;
            }
        }
    }
}

void MyPolygon::fill(drawBoardBuffer* drawBoard){
    int max=-WINDOWS_WIDTH;
    int min=+WINDOWS_WIDTH;
    for(list<intPoint2D*>::iterator index = PolyVertex.begin(); index!=PolyVertex.end(); index++){
        if((*index)->x>max)
            max=(*index)->x;
        if((*index)->x<min)
            min=(*index)->x;
    }
    for(int i=min+1; i<max; i++)
        fillVerticalLine(i, drawBoard);
//    fill4way(center.x, center.y, drawBoard);
//    intPoint2D LeftToRight(min+1, -WINDOWS_HEIGHT/2);
//    while(LeftToRight.x < max){
//        drawBoard->drawPoint(LeftToRight.x, LeftToRight.y);
//        intPoint2D Up(LeftToRight.x, LeftToRight.y+1);

//        bool isOdd=false;
//        while(Up.y<WINDOWS_HEIGHT/2){
//            if(drawBoard->isPointDrawn(Up.x, Up.y)){
//                if(pointInGraph(Up))
//                    isOdd = !isOdd;
//            }
//            else if(isOdd){
//                drawBoard->drawPoint(Up.x, Up.y);
//            }
//            Up.y++;
//        }

//        LeftToRight.x++;
//        LeftToRight.y=-WINDOWS_HEIGHT/2;
//    }
}

bool MyPolygon::pointInGraph(intPoint2D click){
    list<intPoint2D*>::iterator first = PolyVertex.begin();
    list<intPoint2D*>::iterator second = ++PolyVertex.begin();
    int count=0;
    while(first!=PolyVertex.end()){
        double slope = double((*second)->y-(*first)->y)/((*second)->x-(*first)->x);
        bool cond1=((*first)->x<=click.x) && (click.x<=(*second)->x);
        bool cond2=((*second)->x<=click.x)&&(click.x<=(*first)->x);
        bool ClickBelowLine=(click.y<slope*(click.x-(*first)->x) + (*first)->y);

        if((cond1 || cond2) && ClickBelowLine)
            count++;

        first++;
        second++;
        if(second==PolyVertex.end())
            second=PolyVertex.begin();
    }
    if(count%2==0)
        return false;
    else
        return true;
}


Graph2D* MyPolygon::mouseSelect(intPoint2D click){
    if(PolyVertex.size()<3)
        return NULL;
    bool isPointInGraph = pointInGraph(click);
    if(isPointInGraph){
        if(innerPoint==NULL)
            innerPoint=new intPoint2D(click.x, click.y);
        else{
            delete innerPoint;
            innerPoint = new intPoint2D(click.x, click.y);
        }
        return this;
    }
    else
        return NULL;
}
