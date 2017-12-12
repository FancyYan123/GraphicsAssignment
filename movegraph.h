#ifndef MOVEGRAPH_H
#define MOVEGRAPH_H

#include "Graph2D.h"
#include "Constant.h"
#include <iostream>
using namespace std;

class moveGraph
{
public:
    moveGraph(){
        objectToMove = NULL;
        start.x = start.y = end.x = end.y = 0;
    }
    intPoint2D getStart(){ return start; }
    intPoint2D getEnd(){ return end; }

    Graph2D* getObjectToMove(){ return objectToMove;}
    void setObjectToMove(Graph2D* temp){
        objectToMove = temp;
    }

    //响应鼠标中断
    void setStart(int x, int y){
        start.x = x;
        start.y = y;
    }
    void setEnd(int x, int y){
        end.x = x;
        end.y = y;
    }

    void move();

protected:
    intPoint2D start;
    intPoint2D end;
    Graph2D* objectToMove;
};

#endif // MOVEGRAPH_H
