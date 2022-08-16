#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(QRectF(0,0,800,800));
    PointGraphicsItem *item = new PointGraphicsItem();
    //PointGraphicsItem *item2 = new PointGraphicsItem();
    item->setPos(150,150);
    //item2->setPos(100,100);
    scene->addItem(item);
    //scene->addItem(item2);

    View *view = new View("name");
    view->view()->setScene(scene);

    ui->tabWidget->addTab(view,"name");
}

MainWindow::~MainWindow()
{
    delete ui;
}

