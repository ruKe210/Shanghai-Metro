#include "addline.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Windows.h>
#include <QString>
#include <QApplication>
#include <QBrush>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    map.Initgraph();//地图初始
    draw_map();//绘制全景地图
    this->my_graphview=new MY_GRAPHVIEW(this);

    this->my_graphview->setScene(scene);

}

MainWindow::~MainWindow()
{
    delete ui;
}
//绘制点
void MainWindow::draw_map()
{
    QBrush grayBrush(Qt::gray);//填充
    QBrush whiteBrush(Qt::white);//填充
    //17种 颜色
    QColor color1(227,11,51),color2(140,194,34),color3(250,213,2),color4(71,30,132),color5(153,87,159);
    QColor color6(213,11,110),color7(236,116,10),color8(3,148,215),color9(135,201,236),color10(196,173,210);
    QColor color11(138,35,50),color12(9,124,101),color13(232,152,191), color14(98, 96, 32), color15(205, 186, 152),color16(152,208,191),color17(188,123,113),color18(192, 148, 83);
    QPen outlinePen;
    outlinePen.setColor(color1);
    outlinePen.setWidth(2);
    for (int i=2;i<=map.vexnum;i++){
        for (int j=1;j<i;j++){
            if (map.arcs[i][j]>0){ 
                switch(map.arcs[j][i]){//根据不同数字，编号不同颜色
                case 1:outlinePen.setColor(color1);break;
                case 2:outlinePen.setColor(color2);break;
                case 3:outlinePen.setColor(color3);break;
                case 4:outlinePen.setColor(color4);break;
                case 5:outlinePen.setColor(color5);break;
                case 6:outlinePen.setColor(color6);break;
                case 7:outlinePen.setColor(color7);break;
                case 8:outlinePen.setColor(color8);break;
                case 9:outlinePen.setColor(color9);break;
                case 10:outlinePen.setColor(color10);break;
                case 11:outlinePen.setColor(color11);break;
                case 12:outlinePen.setColor(color12);break;
                case 13:outlinePen.setColor(color13);break;
                case 14:outlinePen.setColor(color14); break;
                case 15:outlinePen.setColor(color15); break;
                case 16:outlinePen.setColor(color16);break;
                case 17:outlinePen.setColor(color17);break;
                case 18:outlinePen.setColor(color18); break;
                case 34:outlinePen.setColor(color3);
                        scene->addLine(map.node[i].x+1,map.node[i].y+1,map.node[j].x+1,map.node[j].y+1,outlinePen);
                        outlinePen.setColor(color4);
                        break;
                default:outlinePen.setColor(color2);
                        scene->addLine(map.node[i].x+1,map.node[i].y+1,map.node[j].x+1,map.node[j].y+1,outlinePen);
                        outlinePen.setColor(color10);
                        break;
                }
                scene->addLine(map.node[i].x+2.5,map.node[i].y+2.5,map.node[j].x+2.5,map.node[j].y+2.5,outlinePen);
            }
        }
    }
    outlinePen.setWidth(1);
    QGraphicsTextItem *text;
    for (int i=1;i<map.vexnum;i++) //绘制站点
    {
        QGraphicsEllipseItem *ellipseItem = new QGraphicsEllipseItem(QRectF(0,0,7,7));
        ellipseItem->setPos(map.node[i].x, map.node[i].y+1); // 设置圆的位置
        ellipseItem->setBrush(whiteBrush);
        scene->addItem(ellipseItem);
        myButton* mybutton = new myButton();
        scene->addWidget(mybutton);
        mybutton->show();
        mybutton->move(map.node[i].x-1, map.node[i].y-1);
        mybutton->setMinimumSize(1, 1); // 移除最小尺寸限制
        mybutton->resize(10,20);
        
        mybutton->setStyleSheet("QPushButton{font-size:150px;border-style:solid;border-radius:150px;}");
        mybutton->setStyleSheet("QPushButton { background-color: transparent; }");

        QString info;
        info.append(map.node[i].name.data());

        if (map.node[i].line[1] == -1)
        {
            info.append("\n无可换乘线路");
        }
        else if (map.node[i].line[2] == -1)
        {
            info.append("\n可换乘");
            info.append(std::to_string(map.node[i].line[1]));
            info.append("号线");
        }
        else if(map.node[i].line[3]==-1)
        {
            info.append("\n可换乘");
            info.append(std::to_string(map.node[i].line[1]));
            info.append("、");
            info.append(std::to_string(map.node[i].line[2]));
            info.append("号线");
        }
        else
        {
            info.append("\n可换乘");
            info.append(std::to_string(map.node[i].line[1]));
            info.append("、");
            info.append(std::to_string(map.node[i].line[2]));
            info.append("、");
            info.append(std::to_string(map.node[i].line[3]));
            info.append("号线");
        }

        mybutton->info = info;

        text=scene->addText(QString::fromUtf8(map.node[i].name.data()),QFont("宋体",6));
        text->setPos(map.node[i].x,map.node[i].y);
    }


    ui->comboBox_3->addItem(" -----");
    ui->comboBox_4->addItem(" -----");
    for (int i=0;i<20;i++)
        if (map.linenumber[i]>0){
            ui->comboBox_3->addItem(QString::number(map.linenumber[i])+"号线");
            ui->comboBox_4->addItem(QString::number(map.linenumber[i])+"号线");
        }
        else
            break;
}
//绘制线
void MainWindow::draw_lines(){

    delete scene;
    scene = new QGraphicsScene(this);

    this->my_graphview->setScene(scene);

    QBrush greenBrush(Qt::gray);
    QBrush whiteBrush(Qt::white);//填充
    QColor color1(227,11,51),color2(140,194,34),color3(250,213,2),color4(71,30,132),color5(153,87,159);
    QColor color6(213,11,110),color7(236,116,10),color8(3,148,215),color9(135,201,236),color10(196,173,210);
    QColor color11(138, 35, 50), color12(9, 124, 101), color13(232, 152, 191), color14(98, 96, 32), color15(205, 186, 152), color16(152, 208, 191), color17(188, 123, 113), color18(192, 148, 83);
    QPen outlinePen;
    outlinePen.setColor(color1);
    outlinePen.setWidth(2);
    int u,v;
    for (unsigned int i=0;i<map.finalstate.size()-1;i++){
        u=map.finalstate[i]>map.finalstate[i+1]?map.finalstate[i]:map.finalstate[i+1];
        v=map.finalstate[i]>map.finalstate[i+1]?map.finalstate[i+1]:map.finalstate[i];
            if (map.arcs[u][v]>0)
            {
                switch(map.arcs[v][u])
                {
                case 1:outlinePen.setColor(color1); break;
                case 2:outlinePen.setColor(color2); break;
                case 3:outlinePen.setColor(color3); break;
                case 4:outlinePen.setColor(color4); break;
                case 5:outlinePen.setColor(color5); break;
                case 6:outlinePen.setColor(color6); break;
                case 7:outlinePen.setColor(color7); break;
                case 8:outlinePen.setColor(color8); break;
                case 9:outlinePen.setColor(color9); break;
                case 10:outlinePen.setColor(color10); break;
                case 11:outlinePen.setColor(color11); break;
                case 12:outlinePen.setColor(color12); break;
                case 13:outlinePen.setColor(color13); break;
                case 14:outlinePen.setColor(color14); break;
                case 15:outlinePen.setColor(color15); break;
                case 16:outlinePen.setColor(color16); break;
                case 17:outlinePen.setColor(color17); break;
                case 18:outlinePen.setColor(color18); break;
                case 34:outlinePen.setColor(color3);
                        scene->addLine(map.node[u].x+1,map.node[u].y+1,map.node[v].x+1,map.node[v].y+1,outlinePen);
                        outlinePen.setColor(color4);
                        break;
                default:outlinePen.setColor(color2);
                        scene->addLine(map.node[u].x+1,map.node[u].y+1,map.node[v].x+1,map.node[v].y+1,outlinePen);
                        outlinePen.setColor(color10);
                        break;
                }
                // outlinePen.setColor(color1);
                scene->addLine(map.node[u].x+2.5,map.node[u].y+2.5,map.node[v].x+2.5,map.node[v].y+2.5,outlinePen);

            }
    }

    QGraphicsTextItem *text;
   for (unsigned int i=0;i<map.finalstate.size();i++){     //绘制站点
        //scene->addRect(map.node[map.finalstate[i]].x,map.node[map.finalstate[i]].y,5,5,outlinePen,greenBrush);
        //text=scene->addText(QString::fromUtf8(map.node[map.finalstate[i]].name.data()),QFont("宋体",8));
        //text->setPos(map.node[map.finalstate[i]].x,map.node[map.finalstate[i]].y);


        QGraphicsEllipseItem* ellipseItem = new QGraphicsEllipseItem(QRectF(0, 0, 7, 7));
        ellipseItem->setPos(map.node[map.finalstate[i]].x, map.node[map.finalstate[i]].y + 1); // 设置圆的位置
        ellipseItem->setBrush(whiteBrush);
        scene->addItem(ellipseItem);
        myButton* mybutton = new myButton();
        scene->addWidget(mybutton);
        mybutton->show();
        mybutton->move(map.node[map.finalstate[i]].x - 1, map.node[map.finalstate[i]].y - 1);
        mybutton->setMinimumSize(1, 1); // 移除最小尺寸限制
        mybutton->resize(10, 20);

        mybutton->setStyleSheet("QPushButton{font-size:150px;border-style:solid;border-radius:150px;}");
        mybutton->setStyleSheet("QPushButton { background-color: transparent; }");

        QString info;

        if (map.node[map.finalstate[i]].line[1] == -1)
        {
            info.append("\n无可换乘线路");
        }
        else if (map.node[map.finalstate[i]].line[2] == -1)
        {
            info.append("\n可换乘");
            info.append(std::to_string(map.node[map.finalstate[i]].line[1]));
            info.append("号线");
        }
        else if (map.node[map.finalstate[i]].line[3] == -1)
        {
            info.append("\n可换乘");
            info.append(std::to_string(map.node[map.finalstate[i]].line[1]));
            info.append("、");
            info.append(std::to_string(map.node[map.finalstate[i]].line[2]));
            info.append("号线");
        }
        else
        {
            info.append("\n可换乘");
            info.append(std::to_string(map.node[map.finalstate[i]].line[1]));
            info.append("、");
            info.append(std::to_string(map.node[map.finalstate[i]].line[2]));
            info.append("、");
            info.append(std::to_string(map.node[map.finalstate[i]].line[3]));
            info.append("号线");
        }

        mybutton->info = info;

        text = scene->addText(QString::fromUtf8(map.node[map.finalstate[i]].name.data()), QFont("宋体", 6));
        text->setPos(map.node[map.finalstate[i]].x, map.node[map.finalstate[i]].y);
    }
}

void MainWindow::on_comboBox_3_activated(int index)
{
    ui->comboBox->clear();
    int in;
    in=index;
    for (int i=1;i<=map.vexnum;i++){
        for (int j=0;j<map.node[i].num;j++)
            if (map.node[i].line[j]==in){
                ui->comboBox->addItem(QString::fromUtf8(map.node[i].name.data()));
            }
    }
}

void MainWindow::on_comboBox_4_activated(int index)
{
    ui->comboBox_2->clear();
    int in;
    in=index;
    for (int i=1;i<=map.vexnum;i++){
        for (int j=0;j<map.node[i].num;j++)
            if (map.node[i].line[j]==in)
                ui->comboBox_2->addItem(QString::fromUtf8(map.node[i].name.data()));
    }
}

void MainWindow::on_pushButton_clicked()
{
    int a,b,u,v;
    u=ui->comboBox_3->currentIndex();
    v=ui->comboBox_4->currentIndex();
    if(u==0||v==0)
    {
        ui->comboBox_3->clear();
        ui->comboBox_4->clear();
        this->scene->clear();
        map.Initgraph();//地图初始
        draw_map();//绘制全景地图
        return;
    }

    a=map.LocateVex(u,ui->comboBox->currentText());
    b=map.LocateVex(v,ui->comboBox_2->currentText());

    map.Findrute(a,b);
    ui->textBrowser->setText(QString::fromUtf8(map.allstate.data()));
    if (map.statechange.size()==0)
        ui->textBrowser_2->setText("--无需换乘--");
    else
        ui->textBrowser_2->setText(QString::fromUtf8(map.statechange.data()));
    this->scene->clear();
    draw_lines();
    
    QString insert;
    insert.append("insert into history values ( \"");
    insert += account;
    insert.append("\",\"");
    insert += std::to_string(a);
    insert.append("\",\"");
    insert += std::to_string(b);
    insert.append("\")");

    if (mysql_query(this->map.mysql, insert.toStdString().c_str()))
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("搜索失败!");
        msgBox.setIcon(QMessageBox::Critical);
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }


}


void MainWindow::findway(int a,int b)
{
    map.Findrute(a, b);
    ui->textBrowser->setText(QString::fromUtf8(map.allstate.data()));
    if (map.statechange.size() == 0)
        ui->textBrowser_2->setText("--无需换乘--");
    else
        ui->textBrowser_2->setText(QString::fromUtf8(map.statechange.data()));
    this->scene->clear();
    draw_lines();
}


void MainWindow::showname()
{
    QString txt;
    txt.append("用户：");
    txt.append(account.toStdString().c_str());

    ui->label_6->setText(txt.toStdString().c_str());
    
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->comboBox_3->clear();
    ui->comboBox_4->clear();
    this->scene->clear();
    map.Initgraph();//地图初始
    draw_map();//绘制全景地图
    return;
}

void MainWindow::on_actiontianjia_triggered()
{
    addline d;
    d.account = account;
    d.map = &this->map;
    d.mainwindow = this;
    d.create();
    d.exec();
}
