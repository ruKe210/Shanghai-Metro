#include "addline.h"
#include "ui_addline.h"
#include <QApplication>
#include <fstream>
#include <ctype.h>
#include "myitem.h"
using namespace std;

ifstream fin;
ofstream fout;

addline::addline(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::addline)
{
    ui->setupUi(this);
    exepath = QApplication::applicationDirPath();
}

void addline::create()
{
    if ((mysql = mysql_init(NULL)) == NULL)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("数据库加载失败");
        msgBox.setIcon(QMessageBox::Critical);
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
    }
    if (mysql_real_connect(mysql, "localhost", "root", "su15906477192", "metro", 3306, NULL, 0) == NULL)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("数据库加载失败");
        msgBox.setIcon(QMessageBox::Critical);
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
    }
    mysql_set_character_set(mysql, "utf8");

    QString select;
    select.append("select * from history where account = \"");
    select += account;
    select.append("\"");
    if (mysql_query(mysql, select.toStdString().c_str()))
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("数据库加载失败");
        msgBox.setIcon(QMessageBox::Critical);
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    if ((result = mysql_store_result(mysql)) == NULL)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("数据库加载失败");
        msgBox.setIcon(QMessageBox::Critical);
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }


    while (row = mysql_fetch_row(result))
    {
        int a = atoi(row[1]);
        int b = atoi(row[2]);
        QListWidgetItem* item = new QListWidgetItem();
        myitem myitem;
        myitem.item = item;
        myitem.a = a;
        myitem.b = b;

        QString txt;
        txt.append(this->map->node[a].name.c_str());
        txt.append("->");
        txt.append(this->map->node[b].name.c_str());
        item->setText(txt.toStdString().c_str());

        ui->listWidget->addItem(item);

        itemlist.push_back(myitem);
    }

    mysql_free_result(result);
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(singleclicked(QListWidgetItem*)));
}

void addline::singleclicked(QListWidgetItem* item)
{
    int i = 0;
    for (i = 0; i < itemlist.size(); i++)
    {
        if (itemlist[i].item == item)
        {
            break;
        }
    }
    this->mainwindow->findway(itemlist[i].a, itemlist[i].b);
    this->hide();

}

addline::~addline()
{
    delete ui;
}
