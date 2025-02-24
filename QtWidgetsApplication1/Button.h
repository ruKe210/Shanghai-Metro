#ifndef BUTTON_H
#define BUTTON_H
#include <QPushButton>
#include <QMessageBox>
#include <QMenu>
#include <Qtimer>
#include <QToolTip>

class BiTNode;
class PaintTree;
class myButton : public QPushButton
{
    Q_OBJECT
public:
     myButton(QWidget* parent = 0);
    ~myButton();
    void enterEvent(QEnterEvent* event);
    void leaveEvent(QEvent* event);
    void hovorEvent(QEvent* event);
    QString info;

    //using QPushButton::QPushButton;

};
#endif
