#ifndef ADDLINE_H
#define ADDLINE_H

#include <QDialog>
#include "algraphobject.h"
#include <QString>
#include <vector>
#include <QtWidgets>
#include "myitem.h"
#include "mainwindow.h"

class myitem;

namespace Ui 
{
class addline;
}

class addline : public QDialog
{
    Q_OBJECT
    typedef struct Node
    {
        int no;    //序号
        std::string name;   //站点名称
        int x,y;    //站点坐标
        int line[4];     //线路信息，站点在几号线上，最多在四条线上
        int num;
    }Node;
public:

    MainWindow* mainwindow;

    MYSQL* mysql;
    MYSQL_RES* result;
    MYSQL_ROW  row;

    QString account;
    AlgraphObject* map;

    std::vector <myitem> itemlist;


    Node node[MAX_VERTEX_NUM];
    int vexnum;
    int linenumber[20];

    explicit addline(QWidget *parent = 0);
    void create();

    ~addline();
    //void Init();

private slots:


    void singleclicked(QListWidgetItem* item);

private:
    Ui::addline *ui;
    QString exepath;
};

#endif // ADDLINE_H
