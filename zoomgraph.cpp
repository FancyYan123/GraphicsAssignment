#include "zoomgraph.h"

void zoomGraph::zoom()
{
    if(objectToZoom!=NULL)
        objectToZoom->zoom(start, end);
    else
        return;
}
