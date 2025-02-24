#include "Button.h"

myButton::myButton(QWidget* parent) : QPushButton(parent)
{

}
myButton::~myButton()
{

}



void myButton::enterEvent(QEnterEvent* event)
{
    QPushButton::enterEvent(event);
    this->setMouseTracking(true); // 设置鼠标追踪
    QToolTip::showText(QCursor::pos(), info);
}
void myButton::leaveEvent(QEvent* event)
{
    QPushButton::leaveEvent(event);
    this->setMouseTracking(true); // 设置鼠标追踪
    QToolTip::showText(QCursor::pos(), info);
}

void myButton::hovorEvent(QEvent* )
{
    qDebug() << "000";
}
