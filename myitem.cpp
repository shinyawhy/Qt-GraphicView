//myitem.cpp内容如下：
#include "myitem.h"
#include <QPainter>
MyItem::MyItem()
{
}
QRectF MyItem::boundingRect()const {
    qreal penwidth=1;
    return QRectF(-50-penwidth/2,-50-penwidth/2,100+penwidth,100+penwidth);
}
void MyItem::drawRectPath(QPainter *painter){
    QPainterPath rectPath;
    rectPath.moveTo(-50,-50);
    rectPath.lineTo(50,-50);
    rectPath.lineTo(50,50);
    rectPath.lineTo(-50,50);
    rectPath.closeSubpath();//返回绘图开始点

    painter->setPen(QPen(Qt::red,20,Qt::SolidLine,Qt::SquareCap,Qt::MiterJoin));//pen参数别设置错了，要不不好看出来
    painter->drawPath(rectPath);

    //在之前的绘图上我们绘制出QboundingRect的虚线方框
    painter->setPen(QPen(Qt::black,1,Qt::DotLine,Qt::SquareCap,Qt::MiterJoin));
    painter->drawRect(-50,-50,100,100);
}
void MyItem::paint(QPainter *painter
                   ,const QStyleOptionGraphicsItem *,QWidget *){
      drawRectPath(painter);
}
