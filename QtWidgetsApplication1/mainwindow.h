#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "my_graphview.h"
#include "algraphobject.h"
#include "Button.h"

namespace Ui 
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);//初始化
    ~MainWindow();//析构

    AlgraphObject map;//地图结构
    void draw_map();//绘制地图
    void draw_lines();//绘制线
    MY_GRAPHVIEW* my_graphview ;
    QString account;

    void findway(int a, int b);
    void showname();

private slots:
    void on_comboBox_3_activated(int index);//出发地

    void on_comboBox_4_activated(int index);//目的地

    void on_pushButton_clicked();//按钮

    void on_pushButton_2_clicked();

    void on_actiontianjia_triggered();//添加

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;//绘图场景
    QString exepath;
};

#endif // MAINWINDOW_H
