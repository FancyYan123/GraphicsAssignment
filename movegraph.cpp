#include "movegraph.h"
#include<iostream>
using namespace std;

void moveGraph::move(){
    if(objectToMove==NULL)
        return;
    else
        objectToMove->move(start, end);
}
