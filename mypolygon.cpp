#include "mypolygon.h"
#include <iostream>
using namespace std;

void MyPolygon::Draw()
{
    if(PolyVertex.size()>1){
        list<intPoint2D*>::iterator first = PolyVertex.begin();
        list<intPoint2D*>::iterator second = ++PolyVertex.begin();
        while(second!=PolyVertex.end()){
            Line temp(*first, *second);
            temp.Draw();
            first++;
            second++;
        }
        Line temp(*first, *PolyVertex.begin());
        temp.Draw();
    }
}

void MyPolygon::move(intPoint2D start, intPoint2D end){
    int shiftX=end.x-start.x;
    int shiftY=end.y-start.y;

    for(list<intPoint2D*>::iterator index=PolyVertex.begin(); index!=PolyVertex.end(); index++){
        (*index)->x += shiftX;
        (*index)->y += shiftY;
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

}

void MyPolygon::rotate(intPoint2D start, intPoint2D end){
    //TODO: ADD CODE FOR ROTATING HERE!
    return;
}

void MyPolygon::fill(){

}

Graph2D* MyPolygon::mouseSelect(intPoint2D click){
    if(PolyVertex.size()<3)
        return NULL;
    list<intPoint2D*>::iterator first = PolyVertex.begin();
    list<intPoint2D*>::iterator second = ++PolyVertex.begin();
    int count=0;
    while(first!=PolyVertex.end()){
        double slope = double((*second)->y-(*first)->y)/((*second)->x-(*first)->x);
        bool cond1=((*first)->x<=click.x) && (click.x<(*second)->x);
        bool cond2=((*second)->x<=click.x)&&(click.x<(*first)->x);
        bool ClickBelowLine=(click.y<=slope*(click.x-(*first)->x) + (*first)->y);

        if((cond1 || cond2) && ClickBelowLine)
            count++;

        first++;
        second++;
        if(second==PolyVertex.end())
            second=PolyVertex.begin();
    }
    if(count%2==0)
        return NULL;
    else
        return this;
}
