#ifndef POLYGON_H
#define POLYGON_H

#include "Constant.h"
#include "line.h"
#include<iostream>
#include<list>

class MyPolygon:public Graph2D
{
public:
    MyPolygon(){}
    ~MyPolygon(){
        for (list<intPoint2D*>::iterator index = PolyVertex.begin(); index != PolyVertex.end(); index++){
            delete *index;
        }
    }

    void setStart(int x, int y){
        intPoint2D* temp = new intPoint2D(x, y);
        PolyVertex.push_back(temp);
    }
    void setEnd(int x, int y){
        intPoint2D* temp = PolyVertex.back();
        if(temp!=NULL){
            temp->x=x;
            temp->y=y;
        }
    }

    void Draw();
    void move(intPoint2D start, intPoint2D end);
    void zoom(intPoint2D origin, intPoint2D scale);
    void rotate(intPoint2D start, intPoint2D end);
    void fill();

    Graph2D* mouseSelect(intPoint2D click);

    MODE getType(){
        return MYPOLYGON;
    }

protected:
    list<intPoint2D*> PolyVertex;
};

#endif // POLYGON_H
