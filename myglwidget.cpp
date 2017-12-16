#include "myglwidget.h"
#include <GL/glu.h>
#include <QKeyEvent>
//#include <QtOpenGL/glut.h>

MyGLWidget::MyGLWidget(QWidget *parent):
    QGLWidget(parent)
{
    QObject::startTimer(1/30);
    mover = new moveGraph();
    zoomer = new zoomGraph();
    rotator = new rotateGraph();
    drawBoard = new drawBoardBuffer();
    brush = new fillGraph();
    //默认模式是画直线
    mode = LINE;
    r = g = b = 0.0;
}

MyGLWidget::~MyGLWidget(){
    for (list<Graph2D*>::iterator index = view.begin(); index != view.end(); index++){
        delete *index;
    }
    delete mover;
    delete zoomer;
    delete rotator;
    delete brush;
    delete drawBoard;
}

void MyGLWidget::initializeGL()                         //此处开始对OpenGL进行所以设置
{
    glClearColor(CLEAR_COLOR_R, CLEAR_COLOR_G, CLEAR_COLOR_B, CLEAR_COLOR_ALPHA);  //白色背景
    glShadeModel(GL_SMOOTH);                            //启用阴影平滑

    glClearDepth(1.0);                                  //设置深度缓存
    glEnable(GL_DEPTH_TEST);                            //启用深度测试
    glDepthFunc(GL_LEQUAL);                             //所作深度测试的类型
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  //告诉系统对透视进行修正

}

void MyGLWidget::resizeGL(int w, int h)                 //重置OpenGL窗口的大小
{
    //暂时不用这里传入的w和h，会影响绘制
    glViewport(0, 0, (GLint)WINDOWS_WIDTH, (GLint)WINDOWS_HEIGHT);               //重置当前的视口
    glMatrixMode(GL_PROJECTION);                        //选择投影矩阵
    glLoadIdentity();
    gluOrtho2D(-WINDOWS_WIDTH/2, WINDOWS_WIDTH/2, -WINDOWS_HEIGHT/2, WINDOWS_HEIGHT/2);


    //设置视口的大小
    /*gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);                         //选择模型观察矩阵
    glLoadIdentity();   */                                //重置模型观察矩阵
}

void MyGLWidget::paintGL()                              //从这里开始进行所以的绘制
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除屏幕和深度缓存

    glColor3f(r, g, b);
    glPointSize(1.5);

    drawBoard->clear();
    for (list<Graph2D*>::iterator index = view.begin(); index != view.end(); index++){
         (*index)->Draw(drawBoard);
    }

    //用于填充：
    brush->fill(drawBoard);

//    cout<<"start filling."<<endl;
//    drawBoard->fillBack();
//    cout<<"stop filling."<<endl;
    drawBoard->draw();
}

//void MyGLWidget::updateGL(){
//    for (list<Graph2D*>::iterator index = view.begin(); index != view.end(); index++){
//         (*index)->Draw();
//    }
//    glFlush();
//}

void MyGLWidget::timerEvent(QTimerEvent *event){
    updateGL();
}

//void MyGLWidget::keyPressEvent(QKeyEvent *keyEvent)
//{
//    switch(keyEvent->key())
//    {
//    case Qt::Key_I: mode = LINE; break;
//    case Qt::Key_C: mode = CIRCLE; break;
//    case Qt::Key_O: mode = OVAL; break;
//    case Qt::Key_R: mode = RECTANGLE; break;
//    //TODO: 添加更多模式转换的代码
//    default: return;
//    }
//}

void MyGLWidget::translate(int x, int y, int &x_out, int &y_out){
    x_out = x - WINDOWS_WIDTH / 2;
    y_out = WINDOWS_HEIGHT - y - WINDOWS_HEIGHT / 2;
    //添加了菜单栏和toolbar，会占用50+50像素的高度
    y_out -= 50+50-10;

}

void MyGLWidget::mousePressEvent(QMouseEvent *mouseEvent){
    Qt::MouseButton button = mouseEvent->button();
    int x_real, y_real;
    translate(mouseEvent->x(), mouseEvent->y(), x_real, y_real);

    //TODO:to debug
    cout<<mouseEvent->x()<<" "<<mouseEvent->y()<<" "<<x_real<<" "<<y_real<<endl;

    if(button==Qt::LeftButton){

        Graph2D* temp=NULL;
        //针对左键按下的操作，一般为新建图像加入列表：
        switch(mode){
        case LINE:
        {
            Graph2D* temp = new Line();
            temp->setStart(x_real, y_real);
            temp->setEnd(x_real, y_real);
            view.push_back(temp);
            break;
        }
        case CIRCLE:
        {
            Graph2D* temp = new Circle();
            temp->setStart(x_real, y_real);
            temp->setEnd(x_real, y_real);
            view.push_back(temp);
            break;
        }
        case OVAL:
        {
            Graph2D* temp = new Oval();
            temp->setStart(x_real, y_real);
            temp->setEnd(x_real, y_real);
            view.push_back(temp);
            break;
        }
        case RECTANGLE:
        {
            Graph2D* temp = new Rect();
            temp->setStart(x_real, y_real);
            temp->setEnd(x_real, y_real);
            view.push_back(temp);
            break;
        }
        case MYPOLYGON:
        {
            //cout<<"enter mypolygon."<<endl;
            Graph2D* last = view.back();
            if(last==NULL || last->getType()!=MYPOLYGON){   //利用了短路求值，最好别这样写
                Graph2D* temp = new MyPolygon();
                temp->setStart(x_real, y_real);
                view.push_back(temp);
            }
            else{
                last->setStart(x_real, y_real);
            }
            break;
        }

        //以下代码处理缩放，平移，旋转等操作
        case MOVEGRAPH:
        {
            mover->setObjectToMove(NULL);
            intPoint2D temp(x_real, y_real);
            Graph2D* objectToMove = NULL;
            for (list<Graph2D*>::iterator index = view.begin(); index != view.end(); index++){
                objectToMove = (*index)->mouseSelect(temp);
                if(objectToMove!=NULL){
                    mover->setObjectToMove(objectToMove);
                    mover->setStart(x_real, y_real);
                    mover->setEnd(x_real, y_real);
                    break;
                }
            }
            break;
        }
        case ZOOMGRAPH:
        {
            zoomer->setObjectToZoom(NULL);
            intPoint2D temp(x_real, y_real);
            Graph2D* objectToZoom = NULL;
            for (list<Graph2D*>::iterator index = view.begin(); index != view.end(); index++){
                objectToZoom = (*index)->mouseSelect(temp);
                if(objectToZoom!=NULL){
                    zoomer->setObjectToZoom(objectToZoom);
                    zoomer->setStart(x_real, y_real);
                    zoomer->setEnd(x_real, y_real);
                    break;
                }
            }
            break;
        }
        case ROTATEGRAPH:
        {
            rotator->setObjectToRotate(NULL);
            intPoint2D temp(x_real, y_real);
            Graph2D* objectToRotate = NULL;
            for (list<Graph2D*>::iterator index = view.begin(); index != view.end(); index++){
                objectToRotate = (*index)->mouseSelect(temp);
                if(objectToRotate!=NULL){
                    rotator->setObjectToRotate(objectToRotate);
                    rotator->setStart(x_real, y_real);
                    rotator->setEnd(x_real, y_real);
                    break;
                }
            }
            break;
        }
        case FILLGRAPH:
        {
            intPoint2D temp(x_real, y_real);
            Graph2D* objectToFill = NULL;
            for(list<Graph2D*>::iterator index=view.begin(); index!=view.end(); index++){
                objectToFill = (*index)->mouseSelect(temp);
                if(objectToFill!=NULL){
                    brush->addObjectToFill(objectToFill);
                    break;
                }
            }

            break;
        }
        default: return;
        }


    }

    else if(button==Qt::RightButton){
        //右键清屏
        mover->setObjectToMove(NULL);
        zoomer->setObjectToZoom(NULL);
        rotator->setObjectToRotate(NULL);
        brush->clearAllGraph();

        while(view.size()!=0){
            Graph2D* temp=view.back();
            delete temp;
            view.pop_back();
        }
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
    }

    else
        return;
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *mouseEvent){
    int x_real, y_real;
    translate(mouseEvent->x(), mouseEvent->y(), x_real, y_real);

    if(mode==MOVEGRAPH){
        mover->setEnd(x_real, y_real);
    //    mover->move();
        return;
    }
    else if(mode==ZOOMGRAPH){
        zoomer->setEnd(x_real, y_real);
        return;
    }
    else if(mode==ROTATEGRAPH){
        rotator->setEnd(x_real, y_real);
        return;
    }
    else if (view.size() != 0){
        Graph2D* temp = view.back();
        temp->setEnd(x_real, y_real);
    }

//    switch (mode)
//    {
//    case  LINE:
//    {
//        if (view.size() != 0){
//            Graph2D* temp = view.back();
//            temp->setEnd(x_real, y_real);
//        }
//        break;
//    }
//    case CIRCLE:
//    {
//        if(view.size()!=0){
//            Graph2D* temp = view.back();
//            temp->setEnd(x_real, y_real);
//        }
//        break;
//    }
//    case OVAL:
//    {
//        if(view.size()!=0){
//            Graph2D* temp = view.back();
//            temp->setEnd(x_real, y_real);
//        }
//        break;
//    }
//    //TODO: 为绘制其他图形添加响应代码
//    default: return;
//    }
}

void MyGLWidget::mouseReleaseEvent(QMouseEvent *mouseEvent){
//    int x_real, y_real;
//    translate(mouseEvent->x(), mouseEvent->y(), x_real, y_real);
    if(mode==MOVEGRAPH)
        mover->move();
    else if(mode==ZOOMGRAPH)
        zoomer->zoom();
    else if(mode==ROTATEGRAPH)
        rotator->rotate();
}
