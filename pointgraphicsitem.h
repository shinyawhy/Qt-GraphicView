#ifndef POINTGRAPHICSITEM_H
#define POINTGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QObject>
#include <QPointF>
#include <QList>
#include <QColor>
#include <math.h>
#include <QCursor>
enum STATE_FLAG{
    DEFAULT_FLAG=0,
    MOV_LEFT_LINE,//标记当前为用户按下矩形的左边界区域
    MOV_TOP_LINE,//标记当前为用户按下矩形的上边界区域
    MOV_RIGHT_LINE,//标记当前为用户按下矩形的右边界区域
    MOV_BOTTOM_LINE,//标记当前为用户按下矩形的下边界区域
    MOV_RIGHTBOTTOM_RECT,//标记当前为用户按下矩形的右下角
    MOV_RECT,//标记当前为鼠标拖动图片移动状态
    ROTATE//标记当前为旋转状态
};
class PointGraphicsItem: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
        PointGraphicsItem(QGraphicsItem* parent = nullptr);
        ~PointGraphicsItem() override;
        QRectF boundingRect() const override;

        void setRectSize(QRectF mrect, bool bResetRotateCenter = true);
        void setRotate(qreal RotateAngle, QPointF ptCenter=QPointF(-999,-999));
        QPointF getRotatePoint(QPointF ptCenter, QPointF ptIn, qreal angle);   // 获取旋转后的点
        QList<QPointF> getRotatePoints(QPointF ptCenter, QList<QPointF> ptIns, qreal angle); // 获取多个旋转后的点
        QPolygonF getRotatePolygonFromRect(QPointF ptCenter, QRectF rectIn, qreal angle); // 矩形旋转后返回多边形
        QRectF getCrtPosRectToSceen();
        QPointF getSmallRotateRectCenter(QPointF ptA, QPointF ptB); // 获取旋转式矩形旋转标记的矩形
        QRectF getSmallRotateRect(QPointF ptA, QPointF ptB);

protected:
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
private:
        QColor m_paint_color;
        const double Width = 100.0;
        const double Height = 100.0;
        
        QRectF m_SmallRotateRect; // 矩形顶部用来表示旋转标记的矩形
        QPolygonF m_SmallRotatePolygon; // 标记矩形旋转后形成的多边形
        bool m_bRotate;
        qreal m_RotateAngle;
        QPointF m_RotateCenter;
        
        QRectF m_oldRect;
        QPolygonF m_oldRectPolygon;
        QRect m_RotateAreaRect;
        bool m_bResize;
        QPolygonF m_insicedPolygon;
        QRectF m_insicedRectF;
        QPolygonF m_leftPolygon;
        QRectF m_leftRectF;
        QPolygonF m_topPolygon;
        QRectF m_topRectF;
        QPolygonF m_rightPolygon;
        QRectF m_rightRectF;
        QPolygonF m_bottomPolygon;
        QRectF m_bottomRectF;
        
        QPointF m_startPos;
        STATE_FLAG m_stateFlag;
        QPointF *pPointFofSmallRotateRect;
        
        
};


#endif // POINTGRAPHICSITEM_H
