#include <QTextCodec>
#include "login.h"
#include "register.h"
#include "account.h"
#include <QtWidgets/QApplication>
#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <iostream>
#include <QDateTime>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MYSQL* mysql;
    MYSQL_RES* result;
    MYSQL_ROW  row;
    account account;
    Login login;
    Register regt;

    if ((mysql = mysql_init(NULL)) == NULL)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("数据库加载失败");
        msgBox.setIcon(QMessageBox::Critical);
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
        return a.exec();
    }
    if (mysql_real_connect(mysql, "localhost", "root", "su15906477192", "metro", 3306, NULL, 0) == NULL)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("数据库加载失败");
        msgBox.setIcon(QMessageBox::Critical);
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
        return a.exec();
    }
    mysql_set_character_set(mysql, "gbk");

    login.reg = &regt;
    login.mysql = mysql;
    regt.log = &login;
    regt.mysql = mysql;
    login.show();



    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    login.mainwindow = new MainWindow();




    return a.exec();
}
