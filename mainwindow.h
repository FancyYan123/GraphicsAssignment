#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include "myglwidget.h"
#include <QWidget>
#include <QMenu>
#include <QSlider>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    //Ui::MainWindow *ui;
//    QAction *modeAction;
//    QAction *colorAction;
    //centerWidget用于承载所有的界面组件，与界面布置器layout相关联。
    QWidget *centralWidget;

    MyGLWidget *glWidget;

    QMenu *Graph2DMenu;
    QMenu *MoveMenu;
    QMenu *ZoomMenu;
    QMenu *RotateMenu;
    QMenu *FillMenu;
    QMenu *ColorMenu;
    QMenu *SaveMenu;

//    QSlider *rSlider;
//    QSlider *gSlider;
//    QSlider *bSlider;

    QAction *moveMode;
    QAction *zoomMode;
    QAction *rotateMode;
    QAction *fillMode;

    QAction *colorDialog;
    QAction *saveDialog;

    QAction *lineMode;
    QAction *ovalMode;
    QAction *circleMode;
    QAction *rectMode;
    QAction *mypolygonMode;

private slots:
    void SlotMoveMode();
    void SlotLineMode();
    void SlotCircleMode();
    void SlotOvalMode();
    void SlotMypolygonMode();
    void SlotRectMode();
    void SlotZoomMode();
    void SlotRotateMode();
    void SlotFillMode();

    void SlotChooseColor();
    void SlotSaveFig();
};

#endif // MAINWINDOW_H
