#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Constant.h"
#include "line.h"
using namespace std;

class Rect : public Graph2D
{
public:
    Rect(){
        leftUp.x = leftUp.y = rightDown.x = rightDown.y = 0;
        leftDown.x = leftDown.y = rightUp.x = rightUp.y = 0;
    }

    Rect(intPoint2D _leftUp, intPoint2D _rightDown){
        leftUp = _leftUp;
        rightDown = _rightDown;
        rightUp.x = rightDown.x;
        rightUp.y = leftUp.y;
        leftDown.x = leftUp.x;
        leftDown.y = rightDown.y;
    }

    void setStart(int x, int y){
        leftUp.x = x;
        leftUp.y = y;

    }

    void setEnd(int x, int y){
        rightDown.x = x;
        rightDown.y = y;
        rightUp.x = rightDown.x;
        rightUp.y = leftUp.y;
        leftDown.x = leftUp.x;
        leftDown.y = rightDown.y;
    }

    void Draw();

    void move(intPoint2D start, intPoint2D end);
    void zoom(intPoint2D origin, intPoint2D scale);

    void rotate(intPoint2D start, intPoint2D end);
    void fill();

    Graph2D* mouseSelect(intPoint2D click);

    MODE getType(){
        return RECTANGLE;
    }

protected:
    intPoint2D leftUp;
    intPoint2D rightUp;
    intPoint2D rightDown;
    intPoint2D leftDown;
};

#endif // RECTANGLE_H
