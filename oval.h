#ifndef OVAL_H
#define OVAL_H

#include<iostream>
#include <GL/glu.h>
#include "Graph2D.h"
#include "Constant.h"
#include "drawboardbuffer.h"
using namespace std;

class Oval:public Graph2D
{
public:
    Oval(){ center.x=0; center.y=0; shortHalf=longHalf=0; horizontalFocus=true;}

    void setStart(int x, int y);
    void setEnd(int x, int y);
    void Draw(drawBoardBuffer* drawBoard);
    MODE getType() {return OVAL;}
    void move(intPoint2D start, intPoint2D end);
    void zoom(intPoint2D origin, intPoint2D scale);
    void rotate(intPoint2D start, intPoint2D end);
    void fill(drawBoardBuffer* drawBoard);
    Graph2D* mouseSelect(intPoint2D click);

private:
    //用于追踪鼠标变化
    intPoint2D start;
    intPoint2D end;

    intPoint2D center;
    double shortHalf;
    double longHalf;
    //用于判断焦点是否水平：
    bool horizontalFocus;
    //void fill4way(int x, int y, drawBoardBuffer* drawBoard);
    void drawSymPoint(intPoint2D first, drawBoardBuffer* drawBoard);
};

#endif // OVAL_H
