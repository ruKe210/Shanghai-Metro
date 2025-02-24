#ifndef REGISTER_H
#define REGISTER_H

#include <QtWidgets/QDialog>
#include "ui_register.h"
#include "login.h"
#include "account.h"
#include <QString>
#include <QMessageBox>

#include "../include/mysql.h"
class Login;
class account;
class Register : public QDialog
{
    Q_OBJECT

public:
    Register(QWidget* parent = nullptr);
    ~Register();
    Login* log;

    MYSQL* mysql;
    MYSQL_RES* result;
    MYSQL_ROW  row;


public slots:
    void OK();
    void RETURN();
public:
    Ui::Form ui;
};
#endif // REGISTER_H