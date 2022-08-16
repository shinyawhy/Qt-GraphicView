//myitem.h内容如下
#ifndef MYITEM_H
#define MYITEM_H
#include <QGraphicsItem>
class MyItem : public QGraphicsItem
{
public:
    MyItem();
    QRectF boundingRect()const override;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)override;
private:
   void drawRectPath(QPainter *painter);
};

#endif // MYITEM_H
