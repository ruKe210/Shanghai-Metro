#include "my_graphview.h"

//MY_GRAPHVIEW::MY_GRAPHVIEW() {}
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QGraphicsSceneDragDropEvent>
#include <QDrag>
#include <math.h>

MY_GRAPHVIEW::MY_GRAPHVIEW(QWidget *parent) : QGraphicsView(parent)
{
    setAcceptDrops(true);
    m_scaleValue = 1;
    m_scaleDafault = 0;
    m_isMove = false;
    move(25,25);
    resize(631,661);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setMouseTracking(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->show();


}
QRectF MY_GRAPHVIEW::boundingRect() const
{
    return QRectF(-m_pix.width() / 2, -m_pix.height() / 2,
                  m_pix.width(), m_pix.height());
}

void MY_GRAPHVIEW::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                       QWidget *)
{
    painter->drawPixmap(-m_pix.width() / 2, -m_pix.height() / 2, m_pix);
}

void MY_GRAPHVIEW::wheelEvent(QWheelEvent *event)//鼠标滚轮事件
{
    int numDegrees = event->angleDelta().y() / 8;
    int numSteps = numDegrees / 15;

    if((numSteps > 0)&&(m_scaleValue >= 50))//最大放大到原始图像的50倍
        return;
    else if((numSteps < 0)&&(m_scaleValue <= m_scaleDafault))//图像缩小到自适应大小之后就不继续缩小
        ResetItemPos();//重置图片大小和位置，使之自适应控件窗口大小
    else
    {
        if(numSteps > 0)//鼠标滚轮向前滚动
            m_scaleValue*=1.2;//每次放大20%
        else
            m_scaleValue*=0.8;//每次缩小20%
        QTransform transform;
        transform.scale(m_scaleValue, m_scaleValue);
        this->setTransform(transform);
    }
}

void MY_GRAPHVIEW::setQGraphicsViewWH(int nwidth, int nheight)//将主界面的控件QGraphicsView的width和height传进本类中，并根据图像的长宽和控件的长宽的比例来使图片缩放到适合控件的大小
{
    int nImgWidth = m_pix.width();
    int nImgHeight = m_pix.height();
    qreal temp1 = nwidth*1.0/nImgWidth;
    qreal temp2 = nheight*1.0/nImgHeight;
    if(temp1>temp2)
    {
        m_scaleDafault = temp2;
    }
    else
    {
        m_scaleDafault = temp1;
    }
    QTransform transform;
    transform.scale(1, 1); // 设置缩放因子，scaleX 和 scaleY 分别是水平和垂直方向的缩放比例
    this->setTransform(transform);

    m_scaleValue = m_scaleDafault;
}

void MY_GRAPHVIEW::ResetItemPos()//重置图片位置
{
    m_scaleValue = m_scaleDafault;//缩放比例回到一开始的自适应比例
    QTransform transform;
    transform.scale(1, 1); // 设置缩放因子，scaleX 和 scaleY 分别是水平和垂直方向的缩放比例
    this->setTransform(transform);

    move(0,0);
}

qreal MY_GRAPHVIEW::getScaleValue() const
{
    return m_scaleValue;
}
