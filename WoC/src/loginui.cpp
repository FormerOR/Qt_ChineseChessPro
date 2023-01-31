#include "loginui.h"
#include "dialogui.h"
#include "network.h"
#include "mainui.h"
#include "algorithms.h"

#include <QDir>
#include <QMessageBox>

LoginUI::LoginUI()
    : layout(new QFormLayout), buttonLayout(new QHBoxLayout),
      user(new QLabel("用户名")), passwd(new QLabel("密码")),
      userTxt(new QLineEdit), passwdTxt(new QLineEdit),
      login(new QPushButton("登录")), signup(new QPushButton("注册"))
{
    setAttribute(Qt::WA_DeleteOnClose);
    setLayout(layout);
    layout->addRow(user, userTxt);
    layout->addRow(passwd, passwdTxt);
    buttonLayout->addWidget(login);
    buttonLayout->addWidget(signup);
    layout->addRow(buttonLayout);

    userTxt->setMaxLength(20);
    passwdTxt->setEchoMode(QLineEdit::Password);

    try {
    //Add your own code here:
    /////////////////////////
    connect(signup,SIGNAL(clicked()),this,SLOT(onSignup()));
    connect(login,SIGNAL(clicked()),this,SLOT(onLogin()));
    connect(Network::getInstance(),SIGNAL(failure(QString)),this,SLOT(onFailure(QString)));
    connect(Network::getInstance(),SIGNAL(signupOK()),this,SLOT(signupSuccess()));
    connect(Network::getInstance(),SIGNAL(loginOK()),this,SLOT(loginSuccess()));
    /////////////////////////
    } catch(Exception e) {
        e.process();
    }
}

void LoginUI::onLogin() {
    Network::getInstance()->login(userTxt->text(), passwdTxt->text());
}

void LoginUI::onSignup() {
    Network::getInstance()->signup(userTxt->text(), passwdTxt->text());
}

void LoginUI::loginSuccess() {
    this->disconnect();
    hide();
    MainUI* ui = new MainUI;
    ui->show();
    auto popup = new DialogUI;
    popup->show();
    close();
}

void LoginUI::signupSuccess() {
    QMessageBox* nov = new QMessageBox;
    nov->setText(tr("注册成功！"));
    nov->show();
}

void LoginUI::onFailure(const QString message) {
    QMessageBox* nov = new QMessageBox;
    nov->setText(message);
    nov->show();
}

