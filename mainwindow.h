#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QSplitter>
#include "view.h"
#include "myview.h"
#include "myitem.h"
#include "pointgraphicsitem.h"
#include "rectanglegraphicsitem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QGraphicsScene;
class QSplitter;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:
    Ui::MainWindow *ui;
    void populateScene();

    QGraphicsScene *scene;
    QSplitter *h1Splitter;
};
#endif // MAINWINDOW_H
