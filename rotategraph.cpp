#include "rotategraph.h"

void rotateGraph::rotate()
{
    if(objectToRotate!=NULL)
        objectToRotate->rotate(start, end);
    else
        return;
}
