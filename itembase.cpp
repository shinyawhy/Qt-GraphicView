#include "itembase.h"

#pragma once

#include <QGraphicsItem>
#include <QPointF>
#include <QColor>
class PointGraphicsItem: public QGraphicsItem
{
    public:
        PointGraphicsItem(QGraphicsItem* parent = Q_NULLPTR);
        ~PointGraphicsItem() override;

        QRectF boundingRect() const override;
    protected:

        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    private:
        QColor m_paint_color;
        const double Width = 10.0;
        const double Height = 10.0;
};
