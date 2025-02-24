#ifndef MY_GRAPHVIEW_H
#define MY_GRAPHVIEW_H
#include <QWidget>
#include <QtGui>
#include <QPixmap>
#include <QPainter>
#include <QRectF>
#include <QMouseEvent>
#include <QPointF>
#include <QDragEnterEvent>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsItem>
#include <QGraphicsView>

    enum Enum_ZoomState{
        NO_STATE,
        RESET,
        ZOOM_IN,
        ZOOM_OUT
    };

class MY_GRAPHVIEW :public QGraphicsView
{
    //Q_OBJECT
public:
    MY_GRAPHVIEW(QWidget *parent = 0);
    QRectF  boundingRect() const;
    void    paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void    wheelEvent(QWheelEvent *event);
    void    ResetItemPos();
    qreal   getScaleValue() const;
    void    setQGraphicsViewWH(int nwidth,int nheight);


private:
    qreal       m_scaleValue;
    qreal       m_scaleDafault;
    QPixmap     m_pix;
    int         m_zoomState;
    bool        m_isMove;
    QPointF     m_startPos;
};

#endif // MY_GRAPHVIEW_H
