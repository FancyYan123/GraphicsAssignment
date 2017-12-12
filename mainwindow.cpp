#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constant.h"
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) ,ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    setWindowTitle(tr("myDrawBoard"));
//    MyGLWidget *board = new MyGLWidget(this);

//    modeAction = new QAction(tr("Mode"), this);
//    colorAction = new QAction(tr("Color"), this);

//    QMenu *changeMode=menuBar()->addMenu(tr("Mode"));
//    QMenu *LineMode = changeMode->addMenu(tr("Line"));
//    QMenu *RountMode = changeMode->addMenu(tr("Round"));
//    QMenu *OralMode = changeMode->addMenu(tr("Oral"));

    centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    glWidget = new MyGLWidget;

    //rSlider = createSlider(SIGNAL(redColor(float)), SLOT(glWidget->setColorRed(float)));


    //创建actions
    lineMode = new QAction(tr("&直线"), this);
    lineMode->setShortcut(tr("Ctrl+l"));
    //connect(lineMode, SIGNAL(triggered(bool)), this, [&](){glWidget->changeMode(LINE);});
    connect(lineMode, SIGNAL(triggered(bool)), this, SLOT(SlotLineMode()));

    circleMode = new QAction(tr("&圆形"), this);
    circleMode->setShortcut(tr("Ctrl+c"));
    //connect(circleMode, SIGNAL(triggered(bool)), this, [&](){glWidget->changeMode(CIRCLE);});
    connect(circleMode, SIGNAL(triggered(bool)), this, SLOT(SlotCircleMode()));

    ovalMode = new QAction(tr("&椭圆"), this);
    ovalMode->setShortcut(tr("Ctrl+o"));
    //connect(ovalMode, SIGNAL(triggered(bool)), this, [&](){glWidget->changeMode(OVAL);});
    connect(ovalMode, SIGNAL(triggered(bool)), this, SLOT(SlotOvalMode()));

    rectMode = new QAction(tr("&矩形"), this);
    rectMode->setShortcut(tr("Ctrl+r"));
    //connect(ovalMode, SIGNAL(triggered(bool)), this, [&](){glWidget->changeMode(OVAL);});
    connect(rectMode, SIGNAL(triggered(bool)), this, SLOT(SlotRectMode()));

    moveMode = new QAction(tr("&平移"), this);
    moveMode->setShortcut(tr("Ctrl+m"));
    connect(moveMode, SIGNAL(triggered(bool)), this, SLOT(SlotMoveMode()));

    zoomMode = new QAction(tr("&缩放"), this);
    zoomMode->setShortcut(tr("Ctrl+z"));
    connect(zoomMode, SIGNAL(triggered(bool)), this, SLOT(SlotZoomMode()));

    rotateMode = new QAction(tr("&旋转"), this);
    rotateMode->setShortcut(tr("Ctrl+x"));
    connect(rotateMode, SIGNAL(triggered(bool)), this, SLOT(SlotRotateMode()));

    //创建菜单栏
    Graph2DMenu = menuBar()->addMenu(tr("&绘制"));
    Graph2DMenu->addAction(lineMode);
    Graph2DMenu->addAction(circleMode);
    Graph2DMenu->addAction(ovalMode);
    Graph2DMenu->addAction(rectMode);

    MoveMenu = menuBar()->addMenu(tr("&平移"));
    MoveMenu->addAction(moveMode);

    ZoomMenu = menuBar()->addMenu(tr("&缩放"));
    ZoomMenu->addAction(zoomMode);

    RotateMenu = menuBar()->addMenu(tr("&旋转"));
    RotateMenu->addAction(rotateMode);

    //布局管理器：
    QVBoxLayout *currentLayout = new QVBoxLayout;
    currentLayout->addWidget(glWidget);
    centralWidget->setLayout(currentLayout);

    setWindowTitle("DrawBoard");
    resize(WINDOWS_WIDTH, WINDOWS_HEIGHT);
}

MainWindow::~MainWindow()
{
    delete ui;
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
