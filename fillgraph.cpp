#include "fillgraph.h"

void fillGraph::addObjectToFill(Graph2D* temp){
    if(temp==NULL)
        return;
    for(list<Graph2D*>::iterator index=objectsToFill.begin(); index!=objectsToFill.end(); index++){
        if((*index)==temp)
            return;
    }

    objectsToFill.push_back(temp);
}

void fillGraph::fill(){
    for(list<Graph2D*>::iterator index=objectsToFill.begin(); index!=objectsToFill.end(); index++){
        (*index)->fill();
    }
}

void fillGraph::clearAllGraph(){
    objectsToFill.clear();
}
