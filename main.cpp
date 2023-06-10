//组件库头文件
#include "widget.h"
#include <QApplication>
#include <QSplashScreen>
#include <QThread>
#include <QtWidgets/QApplication>
//算法头文件
//#include "./hzc/upload/picture.h"
//#include "./hzc/upload/BigHeader.h"


int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(resources);
    //---------------开始界面-----------------------//
    QSplashScreen *startScreen = new QSplashScreen();
    startScreen->setPixmap(QPixmap("D:/Pictures/Screenshots/bar.png"));//开始界面图片，得ps一个
    startScreen->show();
    Qt::Alignment bottomLeft = Qt::AlignRight | Qt::AlignBottom;
    QFont splashFont;
    splashFont.setFamily("Consolas");
    splashFont.setPointSize(18);
    splashFont.setBold(true);
    startScreen->setFont(splashFont);
    startScreen->showMessage(QString("Loading..."),bottomLeft,Qt::white);
    QThread::sleep(1);
    delete startScreen;
    //---------------结束开始界面--------------------//

    Widget w;
    //w.setWindowFlag(Qt::FramelessWindowHint);
    //w.setAttribute(Qt::WA_TranslucentBackground);
    //w.setFixedSize(1280,800);
    w.show();
    return a.exec();
}
