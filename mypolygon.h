#ifndef POLYGON_H
#define POLYGON_H

#include "Constant.h"
#include "line.h"
#include<iostream>
#include<list>

class MyPolygon:public Graph2D
{
public:
    MyPolygon(){    innerPoint=NULL;  }

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

    void Draw(drawBoardBuffer* drawBoard);
    void move(intPoint2D start, intPoint2D end);
    void zoom(intPoint2D origin, intPoint2D scale);
    void rotate(intPoint2D start, intPoint2D end);
    void fill(drawBoardBuffer* drawBoard);

    Graph2D* mouseSelect(intPoint2D click);


    MODE getType(){
        return MYPOLYGON;
    }

protected:
    list<intPoint2D*> PolyVertex;
    intPoint2D* innerPoint;
    bool pointInGraph(intPoint2D click);
    void fillVerticalLine(int x, drawBoardBuffer* drawBoard);
    //    void fill4way(int x, int y, drawBoardBuffer* drawBoard);
};

#endif // POLYGON_H
