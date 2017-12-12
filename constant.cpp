#include "constant.h"

double getAngleCos(intPoint2D orign, intPoint2D rotate, intPoint2D center){
    double startX = orign.x-center.x;
    double endX = rotate.x - center.x;
    double startY = orign.y-center.y;
    double endY = rotate.y - center.y;

    double member = startX*endX + startY*endY;
    double denominator = sqrt(pow(startX, 2.0)+pow(startY, 2.0))*sqrt(pow(endX, 2.0)+pow(endY, 2.0));

    return member/denominator;
}

double getAngleSin(intPoint2D orign, intPoint2D rotate, intPoint2D center){
    //用叉乘确定夹角的范围是否在0~phi
    double startX = orign.x-center.x;
    double endX = rotate.x - center.x;
    double startY = orign.y-center.y;
    double endY = rotate.y - center.y;

    double rtn = sqrt(1-pow(getAngleCos(orign, rotate, center), 2.0));
    double is = startX*endY-endX*startY;
    if(is>0)
        return  rtn;
    else
        return -rtn;
}
