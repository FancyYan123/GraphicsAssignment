#ifndef LINE_H
#define LINE_H

#include<iostream>
#include <GL/glu.h>
#include "Graph2D.h"
#include "Constant.h"
using namespace std;

class Line:public Graph2D
{
protected:
    intPoint2D startPos;
    intPoint2D endPos;
    GLfloat width;

private:
    void bresenhamk1(double k);
    void bresenhamk2(double k);

public:
    Line(){ startPos.x = startPos.y = endPos.x = endPos.y = 0; }

    Line(intPoint2D s, intPoint2D e){ startPos.x = s.x; startPos.y = s.y; endPos.x = e.x; endPos.y = e.y; }

    Line(int start_x, int start_y, int end_x, int end_y){
        startPos.x = start_x; startPos.y = start_y;
        endPos.x = end_x; endPos.y = end_y;
    }

    void setStart(int x, int y) { startPos.x = x; startPos.y = y; }

    void setEnd(int x, int y) { endPos.x = x; endPos.y = y; }

    void debug() { cout << startPos.x << " " << startPos.y << " " << endPos.x << " " << endPos.y << endl; }

    void Draw();

    void move(intPoint2D start, intPoint2D end);

    void zoom(intPoint2D origin, intPoint2D scale);

    void rotate(intPoint2D start, intPoint2D end);

    //判断点(x, y)是否在直线的下方，如果直线垂直，判断是不是在左边
    bool onLeftDown(int x, int y);

    Graph2D* mouseSelect(intPoint2D click);

    MODE getType(){
        return LINE;
    }
//	void mouseClick(int button, int state, int x, int y);
//	void mouseActiveMotion(int x, int y);

};

#endif // LINE_H
