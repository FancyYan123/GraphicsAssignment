#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QWidget>
#include <QGLWidget>
#include <list>
#include "Graph2D.h"
#include "movegraph.h"
#include "zoomgraph.h"
#include "rotategraph.h"
#include "line.h"
#include "circle.h"
#include "oval.h"
#include "rect.h"
#include "mypolygon.h"

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent=0);
    ~MyGLWidget();
    void changeMode(MODE m){ mode = m; }
    void setColorRed(float r)   {this->r=r;}
    void setColorGreen(float g) {this->g=g;}
    void setColorBlue(float b)  {this->b=b;}

protected:
    list<Graph2D*> view;
    MODE mode;
    moveGraph* mover;
    zoomGraph* zoomer;
    rotateGraph* rotator;
    float r, g, b;

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
//    void updateGL();


    //转换坐标，将窗口坐标（左上角原点，向右x轴，向下y轴）转化成OpenGL坐标（中心为原点）
    void translate(int x, int y, int &x_out, int &y_out);

    void timerEvent(QTimerEvent* event);
//    void keyPressEvent(QKeyEvent *keyEvent);   //处理键盘事件，暂时用于模式切换
    void mousePressEvent(QMouseEvent *mouseEvent);   //新建直线，加入列表
    void mouseMoveEvent(QMouseEvent *mouseEvent);    //更新列表最末尾的终点坐标
    void mouseReleaseEvent(QMouseEvent *mouseEvent);     //用于移动物体

//private:
//    bool fullscreen;
};

#endif // MYGLWIDGET_H
