#ifndef FILLGRAPH_H
#define FILLGRAPH_H
#include "Constant.h"
#include <iostream>
#include <list>
#include <iterator>
#include "Graph2D.h"
using namespace std;

class fillGraph
{
public:
    fillGraph(){}
    ~fillGraph(){}
    //当按下右键时，清空列表中所有指针，因为图元已经消失：
    void clearAllGraph();

    //向列表中添加图元：
    void addObjectToFill(Graph2D* temp);

    //填充操作：
    void fill();

protected:
    list<Graph2D*> objectsToFill;
};

#endif // FILLGRAPH_H
