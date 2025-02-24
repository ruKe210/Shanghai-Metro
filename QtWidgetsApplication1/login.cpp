#include "login.h"

Login::Login(QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    connect(ui.ok,SIGNAL(clicked()), SLOT(OK()));
    connect(ui.register_2, SIGNAL(clicked()), SLOT(REG()));
}

Login::~Login()
{}

void Login::OK()
{
    QString account = ui.account->text();
    QString password = ui.password->text();
    QString select;

    select.append("select * from user where account = \"");
    select += account;
    select.append("\" and password = \"");
    select += password;
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
    if (result->row_count == 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("没有此账号或密码输入错误!");
        msgBox.setIcon(QMessageBox::Critical);
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    mysql_free_result(result);


    this->hide();//隐藏登录界面
    this->mainwindow->account = account;//让主界面得到所登录账号
    this->mainwindow->showname();//让主界面显示账号名称
    this->mainwindow->show();


    return;
}

void Login::REG()
{
    this->reg->show();
    this->reg->ui.name->clear();
    this->reg->ui.account->clear();
    this->reg->ui.password->clear();
    this->reg->ui.confirmpwd->clear();
    this->hide();
}