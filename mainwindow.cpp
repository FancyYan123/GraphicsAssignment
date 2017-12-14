#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constant.h"
#include <QGridLayout>
#include <QColor>
#include <QColorDialog>
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) //,ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
//    setWindowTitle(tr("myDrawBoard"));
//    MyGLWidget *board = new MyGLWidget(this);

//    modeAction = new QAction(tr("Mode"), this);
//    colorAction = new QAction(tr("Color"), this);

//    QMenu *changeMode=menuBar()->addMenu(tr("Mode"));
//    QMenu *LineMode = changeMode->addMenu(tr("Line"));
//    QMenu *RountMode = changeMode->addMenu(tr("Round"));
//    QMenu *OralMode = changeMode->addMenu(tr("Oral"));

    /*以下代码，直到结尾处均被注释，用于测试ui文件，失败时可返回重置。*/
    centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    glWidget = new MyGLWidget;

    //rSlider = createSlider(SIGNAL(redColor(float)), SLOT(glWidget->setColorRed(float)));


    //创建actions
    //lineMode = new QAction(QIcon("C:\\Qt\\projects\\myPhotoShop\\icon\\line.png"), tr("&直线"), this);
    lineMode = new QAction(QIcon(":\\graphicIcon\\icon\\直线.png"), tr("&直线"), this);
    lineMode->setShortcut(tr("Ctrl+l"));
    //connect(lineMode, SIGNAL(triggered(bool)), this, [&](){glWidget->changeMode(LINE);});
    connect(lineMode, SIGNAL(triggered(bool)), this, SLOT(SlotLineMode()));

    circleMode = new QAction(QIcon(":\\graphicIcon\\icon\\圆.png"), tr("&圆形"), this);
    circleMode->setShortcut(tr("Ctrl+c"));
    //connect(circleMode, SIGNAL(triggered(bool)), this, [&](){glWidget->changeMode(CIRCLE);});
    connect(circleMode, SIGNAL(triggered(bool)), this, SLOT(SlotCircleMode()));

    ovalMode = new QAction(QIcon(":\\graphicIcon\\icon\\椭圆.png"), tr("&椭圆"), this);
    ovalMode->setShortcut(tr("Ctrl+o"));
    //connect(ovalMode, SIGNAL(triggered(bool)), this, [&](){glWidget->changeMode(OVAL);});
    connect(ovalMode, SIGNAL(triggered(bool)), this, SLOT(SlotOvalMode()));

    rectMode = new QAction(QIcon(":\\graphicIcon\\icon\\矩形.png"), tr("&矩形"), this);
    rectMode->setShortcut(tr("Ctrl+r"));
    //connect(ovalMode, SIGNAL(triggered(bool)), this, [&](){glWidget->changeMode(OVAL);});
    connect(rectMode, SIGNAL(triggered(bool)), this, SLOT(SlotRectMode()));

    mypolygonMode = new QAction(QIcon(":\\graphicIcon\\icon\\多边形.png"), tr("&多边形"), this);
    mypolygonMode->setShortcut(tr("Ctrl+p"));
    connect(mypolygonMode, SIGNAL(triggered(bool)), this, SLOT(SlotMypolygonMode()));

    moveMode = new QAction(QIcon(":\\controlIcon\\icon\\平移.png"), tr("&平移"), this);
    moveMode->setShortcut(tr("Ctrl+m"));
    connect(moveMode, SIGNAL(triggered(bool)), this, SLOT(SlotMoveMode()));

    zoomMode = new QAction(QIcon(":\\controlIcon\\icon\\缩放.png"), tr("&缩放"), this);
    zoomMode->setShortcut(tr("Ctrl+z"));
    connect(zoomMode, SIGNAL(triggered(bool)), this, SLOT(SlotZoomMode()));

    rotateMode = new QAction(QIcon(":\\controlIcon\\icon\\旋转.png"), tr("&旋转"), this);
    rotateMode->setShortcut(tr("Ctrl+x"));
    connect(rotateMode, SIGNAL(triggered(bool)), this, SLOT(SlotRotateMode()));

    colorDialog = new QAction(QIcon(":\\controlIcon\\icon\\调色板.png"), tr("&调色板"), this);
    connect(colorDialog, SIGNAL(triggered(bool)), this, SLOT(SlotChooseColor()));

    //创建菜单栏
    Graph2DMenu = menuBar()->addMenu(tr("&绘制"));
    Graph2DMenu->addAction(lineMode);
    Graph2DMenu->addAction(circleMode);
    Graph2DMenu->addAction(ovalMode);
    Graph2DMenu->addAction(rectMode);
    Graph2DMenu->addAction(mypolygonMode);

    MoveMenu = menuBar()->addMenu(tr("&平移"));
    MoveMenu->addAction(moveMode);

    ZoomMenu = menuBar()->addMenu(tr("&缩放"));
    ZoomMenu->addAction(zoomMode);

    RotateMenu = menuBar()->addMenu(tr("&旋转"));
    RotateMenu->addAction(rotateMode);

    ColorMenu = menuBar()->addMenu(tr("&颜色"));
    ColorMenu->addAction(colorDialog);

    //创建工具栏
    QToolBar *tools=addToolBar(tr("&选择操作"));
    tools->addAction(lineMode);
    tools->addAction(ovalMode);
    tools->addAction(rectMode);
    tools->addAction(circleMode);
    tools->addAction(mypolygonMode);

    tools->addAction(moveMode);
    tools->addAction(zoomMode);
    tools->addAction(rotateMode);
    tools->addAction(colorDialog);

    //布局管理器：
    QVBoxLayout *currentLayout = new QVBoxLayout;
    currentLayout->addWidget(glWidget);
    centralWidget->setLayout(currentLayout);

    setWindowTitle("DrawBoard");
    resize(WINDOWS_WIDTH, WINDOWS_HEIGHT);
}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::SlotLineMode(){
    if(glWidget!=NULL){
        glWidget->changeMode(LINE);
    }
}

void MainWindow::SlotCircleMode(){
    if(glWidget!=NULL){
        glWidget->changeMode(CIRCLE);
    }
}

void MainWindow::SlotOvalMode(){
    if(glWidget!=NULL){
        glWidget->changeMode(OVAL);
    }
}

void MainWindow::SlotRectMode(){
    if(glWidget!=NULL){
        glWidget->changeMode(RECTANGLE);
    }
}

void MainWindow::SlotMoveMode(){
    if(glWidget!=NULL){
        glWidget->changeMode(MOVEGRAPH);
    }
}

void MainWindow::SlotMypolygonMode(){
    if(glWidget!=NULL){
        glWidget->changeMode(MYPOLYGON);
    }
}

void MainWindow::SlotZoomMode(){
    if(glWidget!=NULL){
        glWidget->changeMode(ZOOMGRAPH);
    }
}

void MainWindow::SlotRotateMode(){
    if(glWidget!=NULL){
        glWidget->changeMode(ROTATEGRAPH);
    }
}

void MainWindow::SlotChooseColor(){

    QColor color = QColorDialog::getColor(Qt::white, this);
    cout<<"finish"<<endl;
    if(color.isValid()){
        glWidget->setColorRed(color.redF());
        glWidget->setColorBlue(color.blueF());
        glWidget->setColorGreen(color.greenF());
    }
}
