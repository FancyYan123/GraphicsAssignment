#ifndef ROTATEGRAPH_H
#define ROTATEGRAPH_H

#include "constant.h"
#include "Graph2D.h"
#include <iostream>
using namespace std;

class rotateGraph
{
public:
    rotateGraph(){
        start.x = start.y = end.x = end.y = 0;
        objectToRotate = NULL;
    }

    Graph2D* getObjectToRotate(){
        return objectToRotate;
    }

    Graph2D* setObjectToRotate(Graph2D* temp){
        objectToRotate = temp;
        return objectToRotate;
    }

    void setStart(int x, int y){
        start.x = x;
        start.y = y;
    }

    void setEnd(int x, int y){
        end.x = x;
        end.y = y;
    }

    void rotate();

protected:
    intPoint2D start;
    intPoint2D end;
    Graph2D* objectToRotate;
};

#endif // ROTATEGRAPH_H
