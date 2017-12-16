#ifndef CIRCLE_H
#define CIRCLE_H

#include<iostream>
#include <GL/glu.h>
#include "Graph2D.h"
#include "Constant.h"
#include "drawboardbuffer.h"
using namespace std;

class Circle:public Graph2D
{
public:
    Circle(){center.x=0; center.y=0; r=0.0;}

    Circle(int x, int y, double r){
        center.x = x;
        center.y = y;
        this->r = r;
    }

    void setStart(int x, int y);
    void setEnd(int x, int y);
    void Draw(drawBoardBuffer* drawBoard);
    void move(intPoint2D start, intPoint2D end);
    void zoom(intPoint2D origin, intPoint2D scale);
    void rotate(intPoint2D start, intPoint2D end);
    //扫描线填充
    void fill(drawBoardBuffer* drawBoard);

    Graph2D* mouseSelect(intPoint2D click);

    MODE getType(){
        return CIRCLE;
    }

protected:
    intPoint2D center;

    //start和end点用于追踪鼠标动作：
    intPoint2D start;
    intPoint2D end;

    double r;

    //利用对称性，由一个点生成其他七个点
    void drawSymPoints(intPoint2D first, drawBoardBuffer* drawBoard);

    //判断点是否在图元内部：
    bool pointInGraph(intPoint2D click);

    //四联通方法填充图元：
    //void fill4way(int x, int y, drawBoardBuffer* drawBoard);
};

#endif // CIRCLE_H
