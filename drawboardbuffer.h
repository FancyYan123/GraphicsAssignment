#ifndef DRAWBOARDBUFFER_H
#define DRAWBOARDBUFFER_H
#include "Constant.h"
#include <iostream>
using namespace std;

class drawBoardBuffer
{
public:
    drawBoardBuffer();
    ~drawBoardBuffer();
    void drawPoint(int x_in, int y_in);
    bool isPointDrawn(int x_in, int y_in);
    void getDevicePos(int x_in, int y_in, int &x_out, int &y_out);
    void draw();
    void clear();
    void debug();
    void fillBack();

protected:
    void fill4way(int x, int y);
    bool *board;
    int count_isPointDrawn;
};

#endif // DRAWBOARDBUFFER_H
