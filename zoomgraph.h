#ifndef ZOOMGRAPH_H
#define ZOOMGRAPH_H

#include "constant.h"
#include "Graph2D.h"
#include <iostream>
using namespace std;

class zoomGraph
{
public:
    zoomGraph(){
        objectToZoom = NULL;
        start.x = start.y = end.x = end.y = 0;
    }

    Graph2D* getObjectToZoom(){
        return objectToZoom;
    }

    void setObjectToZoom(Graph2D* temp){
        objectToZoom = temp;
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

    void zoom();

protected:
    intPoint2D start;
    intPoint2D end;
    Graph2D* objectToZoom;
};

#endif // ZOOMGRAPH_H
