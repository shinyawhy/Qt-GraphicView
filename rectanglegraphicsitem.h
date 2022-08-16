#ifndef RECTANGLEGRAPHICSITEM_H
#define RECTANGLEGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QtWidgets/QApplication>

class PointGraphicsItem;
class RectangleGraphicsItem : public QGraphicsItem
{
    enum class DragType
    {
        //没有进行拖拽
        Release,

        //五个点的定义
        LeftTop,
        RightTop,
        LeftBottom,
        RightBottom,
        Center,
    };
public:
    RectangleGraphicsItem(QGraphicsItem* parent = nullptr);
    ~RectangleGraphicsItem() override = default;

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
private:
        //拖动点
    QSharedPointer<PointGraphicsItem> m_left_top_item;
    QSharedPointer<PointGraphicsItem> m_left_bottom_item;
    QSharedPointer<PointGraphicsItem> m_right_top_item;
    QSharedPointer<PointGraphicsItem> m_right_bottom_item;
    QSharedPointer<PointGraphicsItem> m_center_item;
    //拖动起始位置
    QPointF m_startPos;
    //当前拖拽的点
    DragType m_drag_type;
    //画笔颜色
    QColor m_line_color;
};

#endif // RECTANGLEGRAPHICSITEM_H
