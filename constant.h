#ifndef CONSTANT_H
#define CONSTANT_H

const int WINDOWS_WIDTH = 800;
const int WINDOWS_HEIGHT = 800;

const float CLEAR_COLOR_R = 1.0;
const float CLEAR_COLOR_G = 1.0;
const float CLEAR_COLOR_B = 1.0;
const float CLEAR_COLOR_ALPHA = 1.0;

#include <math.h>

enum MODE{
    LINE, CIRCLE, SQUARE, RECTANGLE, OVAL, MYPOLYGON, CUBIC, MOVEGRAPH, ZOOMGRAPH, ROTATEGRAPH
};

struct intPoint2D{
    int x;
    int y;
    intPoint2D(){
        x=0; y=0;
    }
    intPoint2D(int _x, int _y){
        x = _x;
        y = _y;
    }
};

double getAngleCos(intPoint2D orign, intPoint2D rotate, intPoint2D center);

double getAngleSin(intPoint2D orign, intPoint2D rotate, intPoint2D center);

#endif // CONSTANT_H
