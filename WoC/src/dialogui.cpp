#include "dialogui.h"

#include "board.h"
#include "network.h"

#include <QTimer>

DialogUI::DialogUI()
    : QDialog(), layout(new QVBoxLayout),
      start(new QPushButton("开始游戏")), exit(new QPushButton("退出游戏")),
      pending(new QLabel("请耐心等待，正在匹配玩家……"))
{
    layout->addWidget(start);
    layout->addWidget(exit);
    layout->addWidget(pending);
    setLayout(layout);
//    CommonHelper::onLoadFont();
    //Add your own code below
    //////////////////////////
    connect(start,SIGNAL(clicked()),this,SLOT(onStart()));
    connect(exit,SIGNAL(clicked()),this,SLOT(onExit()));
    connect(Network::getInstance(),SIGNAL(findOK(QString)),this,SLOT(onFind(QString)));
    connect(Board::getBoard(),&Board::win,this,&DialogUI::onWin);
    connect(Board::getBoard(),&Board::waitSide,this,&DialogUI::onWait);
    //////////////////////////
    pending->hide();
}

void DialogUI::onStart() {
    Network::getInstance()->findOpp();
    start->setParent(nullptr);
    layout->removeWidget(start);
    delete start;
    start = nullptr;
    exit->setParent(nullptr);
    layout->removeWidget(exit);
    delete exit;
    exit = nullptr;
    pending->show();
}
void DialogUI::onWait(){
    pending->setText(Board::getBoard()->isYourTurn()?QString("对方已出棋！\n现在是你的回合！"):QString("出棋成功！\n现在是对方的回合！"));
    show();
}

void DialogUI::onFind(const QString opp_name) {
    pending->setText(QString("您的对手是%1，%2执红先行。").arg(opp_name).arg(Board::getBoard()->side() ? "您" : opp_name));
    show();
}

void DialogUI::onWin(bool side) {
    pending->setText(QString("%1胜！").arg(side ? "红方" : "黑方"));
    show();
    QTimer::singleShot(5000, this, &DialogUI::onExit);
}
