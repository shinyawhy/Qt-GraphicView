#include "rectanglegraphicsitem.h"

#include "RectangleGraphicsItem.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
//#include "GlobalConfig.h"
#include "PointGraphicsItem.h"
RectangleGraphicsItem::RectangleGraphicsItem(QGraphicsItem* parent)
    : QGraphicsItem(parent),
    m_left_top_item(new PointGraphicsItem),
    m_left_bottom_item(new PointGraphicsItem),
    m_right_top_item(new PointGraphicsItem),
    m_right_bottom_item(new PointGraphicsItem),
    m_center_item(new PointGraphicsItem),
    m_drag_type(DragType::Release)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptDrops(true);
    setAcceptHoverEvents(true);

    m_line_color = Qt::blue;

    m_left_top_item->setPos({ 10.0,10.0 });
    m_left_bottom_item->setPos({ 10.0,210.0 });
    m_right_top_item->setPos({ 210.0,10.0 });
    m_right_bottom_item->setPos({ 210.0,210.0 });
    m_center_item->setPos({ 110,110 });
    qDebug() << "left top,     x:" << m_left_top_item->pos().x() << " y:" << m_left_top_item->pos().y();
    qDebug() << "left bottom,  x:" << m_left_bottom_item->pos().x() << " y:" << m_left_bottom_item->pos().y();
    qDebug() << "right top,    x:" << m_right_top_item->pos().x() << " y:" << m_right_top_item->pos().y();
    qDebug() << "right bottom, x:" << m_right_bottom_item->pos().x() << " y:" << m_right_bottom_item->pos().y();
    qDebug() << "--------------------------------------------------------------------------------------------";
}

QRectF RectangleGraphicsItem::boundingRect() const
{
    const QPointF point(20.0, 20.0);
    const QPointF startPoint(m_left_top_item->pos());
    const QPointF endPoint(m_right_bottom_item->pos() + point);
    qDebug() << "boundingRect, location:" << endPoint - startPoint;
    return { startPoint, endPoint };
}

void RectangleGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->save();

    painter->setPen(QPen(m_line_color));
    painter->setBrush(m_line_color);
    const QLineF line1(m_left_top_item->boundingRect().x() + 5, m_left_top_item->boundingRect().y() + 5,
        m_right_top_item->boundingRect().x() + 5, m_right_top_item->boundingRect().y() + 5);
    painter->drawLine(line1);

    const QLineF line2(m_left_top_item->boundingRect().x() + 5, m_left_top_item->boundingRect().y() + 5,
        m_left_bottom_item->boundingRect().x() + 5, m_left_bottom_item->boundingRect().y() + 5);
    painter->drawLine(line2);

    const QLineF line3(m_left_bottom_item->boundingRect().x() + 5, m_left_bottom_item->boundingRect().y() + 5,
        m_right_bottom_item->boundingRect().x() + 5, m_right_bottom_item->boundingRect().y() + 5);
    painter->drawLine(line3);

    const QLineF line4(m_right_bottom_item->boundingRect().x() + 5, m_right_bottom_item->boundingRect().y() + 5,
        m_right_top_item->boundingRect().x() + 5, m_right_top_item->boundingRect().y() + 5.0);
    painter->drawLine(line4);
    painter->restore();

    painter->save();
    painter->setPen(QPen(Qt::black));
    painter->setBrush(Qt::yellow);
    painter->drawRect(m_left_top_item->boundingRect());
    painter->drawRect(m_left_bottom_item->boundingRect());
    painter->drawRect(m_right_top_item->boundingRect());
    painter->drawRect(m_right_bottom_item->boundingRect());
    painter->restore();

    painter->save();
    painter->setPen(QPen(Qt::black));
    painter->setBrush(Qt::red);
    painter->drawRect(m_center_item->boundingRect());
    painter->restore();

    painter->save();
    painter->setPen(QPen(Qt::black));
    const qreal width = m_right_bottom_item->pos().x() - m_left_bottom_item->pos().x() + 10;
    const qreal height = m_right_bottom_item->pos().y() - m_right_top_item->pos().y() + 10;

    const QPointF textPos(m_left_bottom_item->pos().x(), m_left_bottom_item->y() + 20);
    painter->drawText(textPos, QStringLiteral("宽度：%1,高度：%2").arg(width).arg(height));
    painter->restore();
}

void RectangleGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_startPos = event->pos();//鼠标左击时，获取当前鼠标在图片中的坐标，
        qDebug() << "pressed pos  x:" << m_startPos.x() << "   y:" << m_startPos.y();
        if (m_left_top_item->boundingRect().contains(m_startPos))
        {
            setCursor(Qt::PointingHandCursor);
            m_drag_type = DragType::LeftTop;
        }
        else if (m_left_bottom_item->boundingRect().contains(m_startPos))
        {
            setCursor(Qt::PointingHandCursor);
            m_drag_type = DragType::LeftBottom;
        }
        else if (m_right_top_item->boundingRect().contains(m_startPos))
        {
            setCursor(Qt::PointingHandCursor);
            m_drag_type = DragType::RightTop;
        }
        else if (m_right_bottom_item->boundingRect().contains(m_startPos))
        {
            setCursor(Qt::PointingHandCursor);
            m_drag_type = DragType::RightBottom;
        }
        else if (m_center_item->boundingRect().contains(m_startPos))
        {
            setCursor(Qt::PointingHandCursor);
            m_drag_type = DragType::Center;
        }
    }

    return QGraphicsItem::mousePressEvent(event);
}

void RectangleGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    const QPointF point = (event->pos() - m_startPos);

    switch (m_drag_type)
    {
    case DragType::Release:
        break;
    case DragType::LeftTop:
    {
        m_left_top_item->moveBy(point.x(), point.y());
        m_left_bottom_item->moveBy(point.x(), 0);
        m_right_top_item->moveBy(0, point.y());
        m_right_bottom_item->moveBy(0, 0);
        m_center_item->moveBy(point.x() / 2.0, point.y() / 2.0);
        //增加限制条件
        break;
    }

    case DragType::RightTop:
    {
        m_left_top_item->moveBy(0, point.y());
        m_left_bottom_item->moveBy(0, 0);
        m_right_top_item->moveBy(point.x(), point.y());
        m_right_bottom_item->moveBy(point.x(), 0);
        m_center_item->moveBy(point.x() / 2.0, point.y() / 2.0);
        break;
    }

    case DragType::LeftBottom:
    {
        m_left_top_item->moveBy(point.x(), 0);
        m_left_bottom_item->moveBy(point.x(), point.y());
        m_right_top_item->moveBy(0, 0);
        m_right_bottom_item->moveBy(0, point.y());
        m_center_item->moveBy(point.x() / 2.0, point.y() / 2.0);
        break;
    }

    case DragType::RightBottom:
    {
        m_left_top_item->moveBy(0, 0);
        m_left_bottom_item->moveBy(0, point.y());
        m_right_top_item->moveBy(point.x(), 0);
        m_right_bottom_item->moveBy(point.x(), point.y());
        m_center_item->moveBy(point.x() / 2.0, point.y() / 2.0);
        break;
    }
    case DragType::Center:
    {
        m_left_top_item->moveBy(point.x(), point.y());
        m_left_bottom_item->moveBy(point.x(), point.y());
        m_right_top_item->moveBy(point.x(), point.y());
        m_right_bottom_item->moveBy(point.x(), point.y());
        m_center_item->moveBy(point.x(), point.y());
        break;
    }
    }
    qDebug() << "left top,     x:" << m_left_top_item->pos().x() << " y:" << m_left_top_item->pos().y();
    qDebug() << "left bottom,  x:" << m_left_bottom_item->pos().x() << " y:" << m_left_bottom_item->pos().y();
    qDebug() << "right top,    x:" << m_right_top_item->pos().x() << " y:" << m_right_top_item->pos().y();
    qDebug() << "right bottom, x:" << m_right_bottom_item->pos().x() << " y:" << m_right_bottom_item->pos().y();
    qDebug() << "--------------------------------------------------------------------------------------------";
    m_startPos = event->pos();
    scene()->update();
    return QGraphicsItem::mouseMoveEvent(event);
}

void RectangleGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    setCursor(Qt::CrossCursor);
    m_drag_type = DragType::Release;
    //m_line_color = Qt::blue;
}

void RectangleGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    m_line_color = Qt::yellow;
    qDebug() << "hoverEnterEvent";
}

void RectangleGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    m_line_color = Qt::blue;
    qDebug() << "hoverLeaveEvent";
}
