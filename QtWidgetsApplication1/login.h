#ifndef LOGIN_H
#define LOGIN_H

#include <QtWidgets/QDialog>
#include "ui_login.h"
#include "register.h"
#include "../include/mysql.h"
#include "mainwindow.h"
class Register;

class Login : public QDialog
{
    Q_OBJECT

public:
    Login(QWidget* parent = nullptr);
    ~Login();
    Register* reg;
    MainWindow* mainwindow;

    MYSQL* mysql;
    MYSQL_RES* result;
    MYSQL_ROW  row;

public slots:
    void OK();
    void REG();
public:
    Ui::Dialog ui;
};

#endif // LOGIN_H