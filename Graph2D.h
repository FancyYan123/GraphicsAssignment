#ifndef GRAPH2D_H
#define GRAPH2D_H

#include "constant.h"

class Graph2D
{
public:
    virtual ~Graph2D()  { return; }
    virtual void Draw() = 0;
    virtual MODE getType() = 0;
//	virtual void mouseClick(int button, int state, int x, int y) = 0;
//	virtual void mouseActiveMotion(int x, int y) = 0;

    //用于追踪鼠标动作的函数：
    virtual void setStart(int x, int y){return;}
    virtual void setEnd(int x, int y){return;}

    //用于平移的函数：
    virtual void move(intPoint2D start, intPoint2D end)=0;

    //用于缩放的函数：
    virtual void zoom(intPoint2D origin, intPoint2D scale)=0;

    //用于旋转：
    virtual void rotate(intPoint2D start, intPoint2D end)=0;

    //用于确定鼠标点击是否选中的函数:
    virtual Graph2D* mouseSelect(intPoint2D click)=0;
//	virtual void debug() = 0;
};

#endif // GRAPH2D_H
