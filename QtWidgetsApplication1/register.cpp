#include "register.h"

Register::Register(QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);


    connect(ui.register_2, SIGNAL(clicked()), SLOT(OK()));
    connect(ui.return_2, SIGNAL(clicked()), SLOT(RETURN()));
}

Register::~Register()
{}

void Register::OK()
{
    QString account = ui.account->text();
    QString name = ui.name->text();
    QString password = ui.password->text();
    QString confirmpwd = ui.confirmpwd->text();

    if (confirmpwd != password)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("两次输入密码不匹配!");
        msgBox.setIcon(QMessageBox::Critical);
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    /*
    * check if account exits in database 
    */
    QString select;

    select.append("select * from user where account = \"");
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
    if (result->row_count > 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("此账号已存在请登录!");
        msgBox.setIcon(QMessageBox::Critical);
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    mysql_free_result(result);


    QString insert;
    insert.append("insert into user values ( \"");
    insert += account;
    insert.append("\",\"");
    insert += password;
    insert.append("\",\"");
    insert += name;
    insert.append("\")");

    if (mysql_query(mysql, insert.toStdString().c_str()))
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("注册失败!");
        msgBox.setIcon(QMessageBox::Critical);
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    this->hide();
    this->log->ui.account->clear();
    this->log->ui.password->clear();
    this->log->show();
}

void Register::RETURN()
{
    this->hide();
    this->log->ui.account->clear();
    this->log->ui.password->clear();
    this->log->show();
}