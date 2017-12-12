#include "mainwindow.h"
#include "myglwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

    //未添加界面之前的代码，仅包含一个myglwidget:
//    QApplication app(argc, argv);

//    MyGLWidget w;
//    w.resize(WINDOWS_WIDTH, WINDOWS_HEIGHT);
//    w.show();

//    return app.exec();


}
