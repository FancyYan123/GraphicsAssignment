#include "drawboardbuffer.h"
//#include "myglwidget.h"
#include <GL/glu.h>
#include <assert.h>

drawBoardBuffer::drawBoardBuffer()
{
    count_isPointDrawn=0;
    board = new bool[WINDOWS_HEIGHT*WINDOWS_WIDTH];
    memset(board, 0, WINDOWS_HEIGHT*WINDOWS_WIDTH*sizeof(bool));
}

drawBoardBuffer::~drawBoardBuffer(){
    delete []board;
}

void drawBoardBuffer::getDevicePos(int x_in, int y_in, int &x_dev, int &y_dev){
    x_dev = x_in + WINDOWS_WIDTH/2;
    y_dev = WINDOWS_HEIGHT/2 - y_in;
}

void drawBoardBuffer::drawPoint(int x_in, int y_in){
    int x_dev=x_in+WINDOWS_WIDTH/2;
    int y_dev=WINDOWS_HEIGHT/2 - y_in;

    if(x_dev>=0 && x_dev<WINDOWS_WIDTH && y_dev>=0 && y_dev<WINDOWS_HEIGHT)
        board[y_dev*WINDOWS_WIDTH + x_dev]=true;
}

bool drawBoardBuffer::isPointDrawn(int x_in, int y_in){
//    count_isPointDrawn++;
    int x_dev = x_in + WINDOWS_WIDTH/2;
//    cout<<"pos1 "<<count_isPointDrawn<<endl;
    int y_dev = WINDOWS_HEIGHT/2 - y_in;
//    cout<<"pos2"<<endl;
//    getDevicePos(x_in, y_in, x_dev, y_dev);
//    cout<<x_dev<<" "<<y_dev<<endl;
    if(x_dev>=0 && x_dev<WINDOWS_WIDTH && y_dev>=0 && y_dev<WINDOWS_HEIGHT){
//        cout<<"pos3"<<endl;
        return board[y_dev*WINDOWS_WIDTH + x_dev];
    }
    //当越界时，默认时true
    else
        return true;
}

void drawBoardBuffer::draw(){
    int para1=WINDOWS_WIDTH/2;
    int para2=WINDOWS_HEIGHT/2;

    glBegin(GL_POINTS);
    for(int i=0; i<WINDOWS_HEIGHT; i++){
        for(int j=0; j<WINDOWS_WIDTH; j++){
            if(board[i*WINDOWS_WIDTH + j]){
                int x=j-para1;
                int y=para2-i;
                glVertex2i(x, y);
            }
        }
    }
    glEnd();
}

void drawBoardBuffer::clear(){
    memset(board, 0, WINDOWS_HEIGHT*WINDOWS_WIDTH*sizeof(bool));
}

void drawBoardBuffer::debug(){
    for(int i=0; i<WINDOWS_HEIGHT; i++){
        for(int j=0; j<WINDOWS_WIDTH; j++){
            if(board[i*WINDOWS_WIDTH+j])
                cout<<1;
            else
                cout<<0;
        }
        cout<<endl;
    }
}

void drawBoardBuffer::fill4way(int x, int y){
    if(x<0 || x>=WINDOWS_WIDTH || y<0 || y>=WINDOWS_HEIGHT)
        return;
    if(!board[y*WINDOWS_WIDTH+x]){
        board[y*WINDOWS_WIDTH+x]=true;
        //cout<<x<<" "<<y<<endl;
        //count_isPointDrawn++;
        fill4way(x-1, y);
        fill4way(x+1, y);
        fill4way(x, y-1);
        fill4way(x, y+1);
    }
//    assert(x!=0&&y!=0);
}

void drawBoardBuffer::fillBack(){
    fill4way(0, 0);
}
