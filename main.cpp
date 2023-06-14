//组件库头文件
#include "widget.h"
#include <QApplication>
#include <QSplashScreen>
#include <QThread>
#include <QtWidgets/QApplication>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(resources);
    //---------------开始界面-----------------------//
    QSplashScreen *startScreen = new QSplashScreen();
    startScreen->setPixmap(QPixmap(":/startscreen/startscreen_highres.png"));//开始界面图片
    startScreen->show();
    //Qt::Alignment bottomLeft = Qt::AlignRight | Qt::AlignBottom;
    //QFont splashFont;
    //splashFont.setFamily("Consolas");
    //splashFont.setPointSize(18);
    //splashFont.setBold(true);
    //startScreen->setFont(splashFont);
    //startScreen->showMessage(QString("Loading..."),Qt::AlignRight | Qt::AlignBottom,Qt::white);
    QThread::sleep(2);
    delete startScreen;
    //---------------结束开始界面--------------------//
    Widget w;
    w.show();
    return a.exec();
}
