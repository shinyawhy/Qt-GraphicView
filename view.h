#ifndef VIEW_H
#define VIEW_H

#include <QFrame>
#include <QGraphicsView>
#include    <QSlider>
#include <QToolButton>
#include <QScrollBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qmath.h>
#include <QWheelEvent>
#include <QStyle>

QT_BEGIN_NAMESPACE
class QLabel;
class QSlider;
class QToolButton;
QT_END_NAMESPACE

class View;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(View *v) : QGraphicsView(), view(v) { }

protected:

    void wheelEvent(QWheelEvent *) override;


private:
    View *view;
};

class View : public QFrame
{
    Q_OBJECT
public:
    explicit View(const QString &name, QWidget *parent = 0);

    QGraphicsView *view() const;

public slots:
    void zoomIn(int level = 1);
    void zoomOut(int level = 1);


private slots:
    void setupMatrix();
    void resetView();
    void setResetButtonEnabled();

private:
    GraphicsView *graphicsView;
        QToolButton *resetButton;
            QSlider *zoomSlider;
};

#endif // VIEW_H
